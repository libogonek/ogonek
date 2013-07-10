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

// Ordered decomposing sequence

#ifndef OGONEK_DETAIL_DECOMPOSE_ORDERED_HPP
#define OGONEK_DETAIL_DECOMPOSE_ORDERED_HPP

#include <ogonek/character/ucd.h++>
#include <ogonek/types.h++>
#include <ogonek/normalization/detail/decompose.h++>

#include <taussig/algorithms/flat_map.h++>
#include <taussig/algorithms/generate.h++>

#include <algorithm>
#include <iterator>
#include <utility>

namespace ogonek {
    namespace detail {
        inline bool is_starter(code_point u) {
            return ucd::get_combining_class(u) == 0;
        }
        struct combining_class_order {
            template <typename Seq>
            small_vector<code_point, 4> operator()(Seq&& s) const {
                small_vector<code_point, 4> v = seq::materialize(std::forward<Seq>(s));
                auto by_combining_class = [](code_point a, code_point b) {
                    return ucd::get_combining_class(a) < ucd::get_combining_class(b);
                };
                auto l = v.begin();
                for(auto r = l; r != v.end(); l = r) {
                    r = std::find_if(r+1, v.end(), is_starter);
                    std::sort(l, r, by_combining_class);
                }
                return v;
            }
        };

        template <typename Seq>
        struct collect_before_starter {
        private:
            using sequence_type = wheels::meta::Decay<Seq>;

        public:
            template <typename SeqF,
                      wheels::meta::DisableIfRelated<SeqF, collect_before_starter<Seq>>...>
            collect_before_starter(SeqF&& s) : s(std::forward<SeqF>(s)) {}

            struct until_next_starter : seq::true_sequence {
            public:
                until_next_starter(sequence_type& s) : s(&s) {}

                using value_type = code_point;
                using reference = value_type;

                bool empty() const {
                    return seq::empty(*s) || (seen_first && is_starter(seq::front(*s)));
                }
                reference front() const {
                    return seq::front(*s);
                }
                void pop_front() {
                    seq::pop_front(*s);
                    seen_first = true;
                }

            private:
                bool seen_first = false;
                sequence_type* s;
            };
            wheels::optional<until_next_starter> operator()() {
                return seq::empty(s)? wheels::none : wheels::some(until_next_starter(s));
            }

        private:
            sequence_type s;
        };

        namespace result_of {
            template <decomposition D, typename Seq>
            using decompose_ordered = seq::result_of::flat_map<combining_class_order, seq::result_of::generate<collect_before_starter<Seq>>>;
        } // namespace result_of

        template <decomposition D, typename Seq>
        result_of::decompose_ordered<D, Seq> decompose_ordered(Seq&& s) {
            return seq::flat_map(combining_class_order{}, seq::generate(collect_before_starter<Seq>(std::forward<Seq>(s))));
        }
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_DETAIL_DECOMPOSE_ORDERED_HPP

