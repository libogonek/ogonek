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

// Composing sequence

#ifndef OGONEK_NORMALIZATION_DETAIL_COMPOSE_HPP
#define OGONEK_NORMALIZATION_DETAIL_COMPOSE_HPP

#include <ogonek/types.h++>
#include <ogonek/character/ucd.h++>
#include <ogonek/normalization/detail/decompose_ordered.h++>

#include <wheels/meta/enable_if.h++>
#include <wheels/meta/is_related.h++>

#include <utility> // forward

namespace ogonek {
    namespace detail {
        struct composer {
            template <typename Seq>
            vector_type<code_point, 4> operator()(Seq&& s) const {
                auto is_blocked = [](code_point u, int last_ccc) {
                    return last_ccc != -1 && (last_ccc == 0 || last_ccc >= ucd::get_combining_class(u));
                };

                vector_type<code_point, 4> v = seq::materialize(std::forward<Seq>(s));
                for(auto l = v.begin(); l != v.end(); ++l) {
                    if(ucd::is_excluded_from_composition(*l) || !ucd::can_compose(*l)) continue;
                    auto last_ccc = -1;
                    for(auto r = std::next(l); r != v.end();) {
                        if(!is_blocked(*r, last_ccc) && ucd::can_compose(*l, *r)) {
                            *l = ucd::compose(*l, *r);
                            r = v.erase(r);
                        } else {
                            last_ccc = ucd::get_combining_class(*r);
                            ++r;
                        }
                    }
                }
                return v;
            }
        };

        namespace result_of {
            template <decomposition D, typename Seq>
            using compose = seq::result_of::flat_map<composer, grouped_marks<D, Seq>>;
        } // namespace result_of

        template <decomposition D, typename Seq>
        result_of::compose<D, Seq> compose(Seq&& s) {
            return seq::flat_map(composer{}, grouped_marks<D>(std::forward<Seq>(s)));
        }
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_NORMALIZATION_DETAIL_COMPOSE_HPP

