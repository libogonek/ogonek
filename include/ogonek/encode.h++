// Ogonek
//
// Written in 2016 by Martinho Fernandes <ogonek@rmf.io>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Encode ranges

#ifndef OGONEK_ENCODING_ENCODE_HPP
#define OGONEK_ENCODING_ENCODE_HPP

#include <range/v3/view_adaptor.hpp>

#include <vector>
#include <iostream>

#include <cstddef>

namespace ogonek {
    template <typename Encoding, typename Rng>
    struct encoded_view
    : ranges::view_adaptor<
        encoded_view<Encoding, Rng>,
        Rng,
        ranges::is_finite<Rng>::value? ranges::finite : ranges::range_cardinality<Rng>::value> {
    private:
        using base_type = ranges::view_adaptor<
            encoded_view<Encoding, Rng>,
            Rng,
            ranges::is_finite<Rng>::value? ranges::finite : ranges::range_cardinality<Rng>::value>;

        friend ranges::range_access;

        struct adaptor : public ranges::adaptor_base {
        public:
            typename Encoding::code_unit get(ranges::range_iterator_t<Rng> it) const {
                if(position < 0) {
                    encoded = Encoding::encode_one(*it);
                    position = 0;
                }
                return encoded[position];
            }
            void next(ranges::range_iterator_t<Rng>& it) {
                ++position;
                if(position == static_cast<ptrdiff_t>(encoded.size())) {
                    ++it;
                    position = -1;
                }
            }
            bool equal(ranges::range_iterator_t<Rng> it0, ranges::range_iterator_t<Rng> it1, adaptor const & other) const {
                return it0 == it1 && position == other.position;
            }

        private:
            mutable std::vector<typename Encoding::code_unit> encoded;
            mutable std::ptrdiff_t position = -1;
        };

        adaptor begin_adaptor() const {
            return {};
        }

    public:
        encoded_view() = default;
        explicit encoded_view(Rng rng)
        : base_type(std::move(rng))
        {}
    };

    template <typename Encoding, typename Rng>
    encoded_view<Encoding, Rng> encode(Rng rng) {
        return encoded_view<Encoding, Rng>(std::move(rng));
    }
} // namespace ogonek


#endif // OGONEK_ENCODING_ENCODE_HPP

