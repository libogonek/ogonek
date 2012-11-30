// Ogonek
//
// Written in 2012 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Unicode normalization (UAX #15)

#ifndef OGONEK_NORMALIZATION_HPP
#define OGONEK_NORMALIZATION_HPP

#include <ogonek/ucd.h++>

namespace ogonek {
    namespace detail {
        template <typename Iterator>
        struct ordered_decomposing_iterator;

        template <typename Iterator>
        struct decomposing_iterator
        : boost::iterator_facade<
            decomposing_iterator<Iterator>,
            codepoint,
            std::input_iterator_tag, // TODO
            codepoint
          > {
        public:
            decomposing_iterator(Iterator first, Iterator last)
            : first(std::move(first)), last(std::move(last)) {
                if(this->first != this->last) {
                    increment();
                }
            }

            codepoint dereference() const {
                return current[position];
            }
            bool equal(decomposing_iterator const& that) const {
                return (first == that.first && position == that.position)
                    || (exhausted() && that.exhausted());
            }
            void increment() {
                ++position;
                if(static_cast<unsigned>(position) < current.size()) return;

                if(first == last) {
                    current = {};
                    position = depleted;
                    return;
                }
                auto u = *first++;
                auto type = ucd::get_decomposition_type(u);
                if(type == ucd::decomposition_type::can) {
                    current = ucd::get_decomposition_mapping(u);
                } else {
                    current = { u };
                }
                position = 0;
            }

        private:
            friend class ordered_decomposing_iterator<Iterator>;

            static constexpr int depleted = -1;

            bool exhausted() const {
                return position == depleted;
            }

            Iterator first, last;
            int position = depleted;
            std::vector<codepoint> current;
        };

        template <typename Iterator>
        struct composing_iterator;

        template <typename Iterator>
        struct ordered_decomposing_iterator
        : boost::iterator_facade<
            ordered_decomposing_iterator<Iterator>,
            codepoint,
            std::input_iterator_tag, // TODO
            codepoint
          > {
        public:
            ordered_decomposing_iterator(Iterator first, Iterator last)
            : it(std::move(first), std::move(last)) {
                if(!it.exhausted()) {
                    increment();
                }
            }

            codepoint dereference() const {
                return current[position];
            }
            bool equal(ordered_decomposing_iterator const& that) const {
                return it.equal(that.it) && position == that.position;
            }
            void increment() {
                ++position;
                if(static_cast<unsigned>(position) < current.size()) return;
                if(it.exhausted()) {
                    current = {};
                    position = depleted;
                    return;
                }

                if(ucd::get_combining_class(*it) == 0) {
                    current = { *it++ };
                } else {
                    current.clear();
                    while(!it.exhausted() && ucd::get_combining_class(*it) != 0) {
                        current.push_back(*it++);
                    }
                    std::sort(current.begin(), current.end(),
                              [](codepoint a, codepoint b) {
                                  return ucd::get_combining_class(a) < ucd::get_combining_class(b);
                              });
                }
                position = 0;
            }

        private:
            friend class composing_iterator<Iterator>;

            static constexpr int depleted = -1;

            bool exhausted() const {
                return position == depleted;
            }

            decomposing_iterator<Iterator> it;
            int position = depleted;
            std::vector<codepoint> current;
        };

        template <typename Iterator>
        class composing_iterator;
    } // namespace detail

    template <typename SinglePassRange,
              typename Iterator = typename boost::range_const_iterator<SinglePassRange>::type,
              typename DecomposingIterator = detail::decomposing_iterator<Iterator>>
    boost::iterator_range<DecomposingIterator> decompose(SinglePassRange const& r) {
        return boost::make_iterator_range(
                DecomposingIterator { boost::begin(r), boost::end(r) },
                DecomposingIterator { boost::end(r), boost::end(r) });
    }

    template <typename SinglePassRange,
              typename Iterator = typename boost::range_const_iterator<SinglePassRange>::type,
              typename OrderedDecomposingIterator = detail::ordered_decomposing_iterator<Iterator>>
    boost::iterator_range<OrderedDecomposingIterator> decompose_ordered(SinglePassRange const& r) {
        return boost::make_iterator_range(
                OrderedDecomposingIterator { boost::begin(r), boost::end(r) },
                OrderedDecomposingIterator { boost::end(r), boost::end(r) });
    }

    namespace detail {
        template <typename Iterator>
        struct composing_iterator
        : boost::iterator_facade<
            composing_iterator<Iterator>,
            codepoint,
            std::input_iterator_tag, // TODO
            codepoint
          > {
            composing_iterator(Iterator first, Iterator last)
            : it(std::move(first), std::move(last)), exhausted(it.exhausted()) {
                if(!exhausted) {
                    increment();
                }
            }

            codepoint dereference() const {
                return current;
            }
            bool equal(composing_iterator const& that) const {
                return it.equal(that.it) && exhausted == that.exhausted;
            }
            void increment() {
                if(it.exhausted()) {
                    exhausted = true;
                    return;
                }

                current = *it++;
                while(!ucd::is_excluded_from_composition(current)
                      && !it.exhausted()
                      && ucd::can_compose(current)
                      && ucd::can_compose(current, *it)) {
                    current = ucd::compose(current, *it++);
                }
            }

        private:
            ordered_decomposing_iterator<Iterator> it;
            bool exhausted;
            codepoint current;
        };
    } // namespace detail

    class nfc {};
    class nfd {};

    namespace detail {
        template <typename NormalizationForm, typename Iterator>
        class normalizing_iterator_impl;

        template <typename Iterator>
        struct normalizing_iterator_impl<nfd, Iterator> {
            using type = ordered_decomposing_iterator<Iterator>;
        };

        template <typename Iterator>
        struct normalizing_iterator_impl<nfc, Iterator> {
            using type = composing_iterator<Iterator>;
        };

        template <typename NormalizationForm, typename Iterator>
        using normalizing_iterator = typename normalizing_iterator_impl<NormalizationForm, Iterator>::type;
    } // namespace detail

    template <typename NormalizationForm,
              typename SinglePassRange,
              typename Iterator = typename boost::range_const_iterator<SinglePassRange>::type,
              typename NormalizingIterator = detail::normalizing_iterator<NormalizationForm, Iterator>>
    boost::iterator_range<NormalizingIterator> normalize(SinglePassRange const& r) {
        return boost::make_iterator_range(
                NormalizingIterator { boost::begin(r), boost::end(r) },
                NormalizingIterator { boost::end(r), boost::end(r) });
    }

    struct canonical_equivalence {
        template <typename SinglePassRange1, typename SinglePassRange2>
        bool operator()(SinglePassRange1 const& r1, SinglePassRange2 const& r2) const {
            return boost::equal(normalize<nfd>(r1), normalize<nfd>(r2));
        }
    };

    template <typename SinglePassRange1, typename SinglePassRange2>
    bool canonically_equivalent(SinglePassRange1 const& r1, SinglePassRange2 const& r2) {
        return canonical_equivalence{}(r1, r2);
    }
} // namespace ogonek

#endif // OGONEK_NORMALIZATION_HPP

