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

// Decomposing sequence

#ifndef OGONEK_DETAIL_DECOMPOSE_HPP
#define OGONEK_DETAIL_DECOMPOSE_HPP

#include <ogonek/types.h++>
#include <ogonek/character/ucd.h++>
#include <ogonek/detail/container/small_vector.h++>

#include <taussig/algorithms/flat_map.h++>

#include <utility>

namespace ogonek {
    namespace detail {
        enum class decomposition : bool {
            canonical = false,
            compatibility = true,
        };

        template <decomposition>
        struct decompose_one;
        template <>
        struct decompose_one<decomposition::compatibility> {
            small_vector<code_point, 4> operator()(code_point u) const {
                return ucd::get_compatibility_decomposition_mapping(u);
            }
        };
        template <>
        struct decompose_one<decomposition::canonical> {
            small_vector<code_point, 4> operator()(code_point u) const {
                if(ucd::get_decomposition_type(u) == ucd::decomposition_type::can) {
                    return ucd::get_canonical_decomposition_mapping(u);
                } else {
                    return { u };
                }
            }
        };

        namespace result_of {
            template <decomposition D, typename Seq>
            using decompose = seq::result_of::flat_map<decompose_one<D>, Seq>;
        } // namespace result_of

        template <decomposition D, typename Seq>
        result_of::decompose<D, Seq> decompose(Seq&& s) {
            return seq::flat_map(decompose_one<D>{}, std::forward<Seq>(s));
        }
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_DETAIL_DECOMPOSE_HPP
