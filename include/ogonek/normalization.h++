// Ogonek
//
// Written in 2012-2013 by Martinho Fernandes <martinho.fernandes@gmail.com>
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
#include <ogonek/detail/small_vector.h++>
#include <ogonek/detail/ranges.h++>

#include <boost/functional/hash.hpp>

#include <functional>
#include <cstddef>

// hack for char32_t and char16_t hashing
namespace boost {
    namespace hash_detail {
        template <> struct basic_numbers<char16_t>
        : boost::hash_detail::enable_hash_value {};
        template <> struct basic_numbers<char32_t>
        : boost::hash_detail::enable_hash_value {};
    } // namespace hash_detail
} // namespace boost

namespace ogonek {
    namespace detail {
        template <typename T, std::size_t N>
        using vector_type = detail::small_vector<T, N>; 

        template <typename Iterator, bool Compatibility = false>
        struct ordered_decomposing_iterator;

        template <typename Iterator, bool Compatibility = false>
        struct decomposing_iterator
        : boost::iterator_facade<
            decomposing_iterator<Iterator, Compatibility>,
            code_point,
            std::input_iterator_tag, // TODO
            code_point
          > {
        public:
            decomposing_iterator(Iterator first, Iterator last)
            : first(std::move(first)), last(std::move(last)) {
                if(this->first != this->last) {
                    increment();
                }
            }

            code_point dereference() const {
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
                if(Compatibility) {
                    current = ucd::get_compatibility_decomposition_mapping(u);
                } else if(ucd::get_decomposition_type(u) == ucd::decomposition_type::can) {
                    current = ucd::get_canonical_decomposition_mapping(u);
                } else {
                    current = { u };
                }
                position = 0;
            }

        private:
            friend class ordered_decomposing_iterator<Iterator, Compatibility>;

            static constexpr int depleted = -1;

            bool exhausted() const {
                return position == depleted;
            }

            Iterator first, last;
            int position = depleted;
            vector_type<code_point, 4> current;
        };

        template <typename Iterator, bool Compatibility = false>
        struct composing_iterator;

        template <typename Iterator, bool Compatibility>
        struct ordered_decomposing_iterator
        : boost::iterator_facade<
            ordered_decomposing_iterator<Iterator, Compatibility>,
            code_point,
            std::input_iterator_tag, // TODO
            code_point
          > {
        public:
            ordered_decomposing_iterator(Iterator first, Iterator last)
            : it(std::move(first), std::move(last)) {
                if(!it.exhausted()) {
                    increment();
                }
            }

            code_point dereference() const {
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

                current.clear();
                if(ucd::get_combining_class(*it) == 0) {
                    current = it.current;
                    std::advance(it, current.size());
                }
                while(!it.exhausted() && ucd::get_combining_class(*it) != 0) {
                    current.push_back(*it++);
                }
                struct by_combining_class {
                    bool operator()(code_point a, code_point b) const {
                        return ucd::get_combining_class(a) < ucd::get_combining_class(b);
                    }
                };
                auto l = current.begin();
                for(auto r = l; r != current.end(); l = r) {
                    r = std::find_if(r+1, current.end(), [](code_point u) { return ucd::get_combining_class(u) == 0; });
                    std::sort(l, r, by_combining_class());
                }
                position = 0;
            }

        private:
            friend class composing_iterator<Iterator, Compatibility>;

            static constexpr int depleted = -1;

            bool exhausted() const {
                return position == depleted;
            }

            decomposing_iterator<Iterator, Compatibility> it;
            int position = depleted;
            vector_type<code_point, 4> current;
        };
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
        template <typename Iterator, bool Compatibility>
        struct composing_iterator
        : boost::iterator_facade<
            composing_iterator<Iterator, Compatibility>,
            code_point,
            std::input_iterator_tag, // TODO
            code_point
          > {
            composing_iterator(Iterator first, Iterator last)
            : it(std::move(first), std::move(last)), exhausted(it.exhausted()) {
                if(!exhausted) {
                    increment();
                }
            }

            code_point dereference() const {
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

                if(it.position == 0) {
                    compose(it.current);
                }
                current = *it++;
            }

        private:
            static void compose(vector_type<code_point, 4>& sequence) {
                auto is_blocked = [](code_point u, int last_ccc) {
                    return last_ccc != -1 && (last_ccc == 0 || last_ccc >= ucd::get_combining_class(u));
                };
                for(auto l = sequence.begin(); l != sequence.end(); ++l) {
                    if(ucd::is_excluded_from_composition(*l) || !ucd::can_compose(*l)) continue;
                    auto last_ccc = -1;
                    for(auto r = std::next(l); r != sequence.end();) {
                        if(!is_blocked(*r, last_ccc) && ucd::can_compose(*l, *r)) {
                            *l = ucd::compose(*l, *r);
                            r = sequence.erase(r);
                        } else {
                            last_ccc = ucd::get_combining_class(*r);
                            ++r;
                        }
                    }
                }
            }
            
            ordered_decomposing_iterator<Iterator, Compatibility> it;
            bool exhausted;
            code_point current;
        };
    } // namespace detail

    struct nfc {
        static boost::tribool quick_check(code_point u) {
            return ucd::is_nfc_quick_check(u);
        }
    };
    struct nfd {
        static bool quick_check(code_point u) {
            return ucd::is_nfd_quick_check(u);
        }
    };
    struct nfkc {
        static boost::tribool quick_check(code_point u) {
            return ucd::is_nfkc_quick_check(u);
        }
    };
    struct nfkd {
        static bool quick_check(code_point u) {
            return ucd::is_nfkd_quick_check(u);
        }
    };

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

        template <typename Iterator>
        struct normalizing_iterator_impl<nfkd, Iterator> {
            using type = ordered_decomposing_iterator<Iterator, true>;
        };

        template <typename Iterator>
        struct normalizing_iterator_impl<nfkc, Iterator> {
            using type = composing_iterator<Iterator, true>;
        };

        template <typename NormalizationForm, typename Iterator>
        using normalizing_iterator = typename normalizing_iterator_impl<NormalizationForm, Iterator>::type;
    } // namespace detail

    template <typename NormalizationForm,
              typename UnicodeSequence,
              typename Iterator = detail::UnicodeSequenceIterator<UnicodeSequence, assume_valid_t>,
              typename NormalizingIterator = detail::normalizing_iterator<NormalizationForm, Iterator>>
    boost::iterator_range<NormalizingIterator> normalize(UnicodeSequence const& sequence) {
        return detail::wrap_range<NormalizingIterator>(detail::as_code_point_range(sequence, assume_valid));
    }

    struct canonical_equivalence {
        template <typename UnicodeSequence1, typename UnicodeSequence2>
        bool operator()(UnicodeSequence1 const& sequence1, UnicodeSequence2 const& sequence2) const {
            return boost::equal(normalize<nfd>(sequence1), normalize<nfd>(sequence2));
        }
    };

    template <typename UnicodeSequence1, typename UnicodeSequence2>
    bool canonically_equivalent(UnicodeSequence1 const& sequence1, UnicodeSequence2 const& sequence2) {
        return canonical_equivalence{}(sequence1, sequence2);
    }
    
    struct canonical_hash {
    public:
        template <typename UnicodeSequence>
        std::size_t operator()(UnicodeSequence const& sequence) const {
            return hash_normalized(normalize<nfd>(sequence));
        }
    private:
        template <typename NormalizedSequence>
        std::size_t hash_normalized(NormalizedSequence const& sequence) const {
            return boost::hash_range(boost::begin(sequence), boost::end(sequence));
        }
    };

    struct compatibility_equivalence {
        template <typename UnicodeSequence1, typename UnicodeSequence2>
        bool operator()(UnicodeSequence1 const& sequence1, UnicodeSequence2 const& sequence2) const {
            return boost::equal(normalize<nfkd>(sequence1), normalize<nfkd>(sequence2));
        }
    };

    template <typename UnicodeSequence1, typename UnicodeSequence2>
    bool compatibility_equivalent(UnicodeSequence1 const& sequence1, UnicodeSequence2 const& sequence2) {
        return compatibility_equivalence{}(sequence1, sequence2);
    }

    struct compatibility_hash {
    public:
        template <typename UnicodeSequence>
        std::size_t operator()(UnicodeSequence const& sequence) const {
            return hash_normalized(normalize<nfkd>(sequence));
        }
    private:
        template <typename NormalizedSequence>
        std::size_t hash_normalized(NormalizedSequence const& sequence) const {
            return boost::hash_range(boost::begin(sequence), boost::end(sequence));
        }
    };

    template <typename NormalForm, typename UnicodeSequence,
              typename Result = decltype(NormalForm::quick_check(0))>
    Result is_normalized_quick(UnicodeSequence const& sequence) {
        for(auto u : detail::as_code_point_range(sequence, assume_valid)) {
            auto quick_check = NormalForm::quick_check(u);
            if(quick_check) continue; // this looks weird, but consider boost::indeterminate
            else return quick_check;
        }
        return true;
    }
    namespace detail{} // namespace detail
    // TODO unify with UnicodeSequence concept
    template <typename NormalForm, typename UnicodeSequence>
    bool is_normalized(UnicodeSequence const& sequence) {
        auto&& range = detail::as_code_point_range(sequence, assume_valid);
        auto last_starter = boost::begin(range);
        for(auto it = boost::begin(range); it != boost::end(range); ++it) {
            auto quick_check = NormalForm::quick_check(*it);
            if(!quick_check) return false;
            if(boost::indeterminate(quick_check)) {
                auto indeterminate_range = boost::make_iterator_range(last_starter, std::next(it));
                if(!boost::equal(indeterminate_range, normalize<NormalForm>(indeterminate_range))) {
                    return false;
                }
            }
            if(ucd::get_combining_class(*it) == 0) {
                last_starter = it;
            }
        }
        return true;
    }
} // namespace ogonek

#endif // OGONEK_NORMALIZATION_HPP
