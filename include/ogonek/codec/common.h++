// Wheels - various C++ utilities
//
// Written in 2012 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Common stuff for codecs

#ifndef OGONEK_CODEC_COMMON_HPP
#define OGONEK_CODEC_COMMON_HPP

namespace ogonek {
    enum class byte_order {
        big_endian,
        little_endian
    };

    namespace codec {
        namespace detail {
            template <typename Derived>
            struct codec_base {
                template <typename InputIterator, typename OutputIterator>
                OutputIterator encode(InputIterator first, InputIterator last, OutputIterator out) {
                    for(; first != last; ++first) {
                        static_cast<Derived*>(this)->encode_one(*first, out);
                    }
                    return out;
                }
                template <typename InputIterator, typename OutputIterator>
                OutputIterator decode(InputIterator first, InputIterator last, OutputIterator out) {
                    while(first != last) {
                        *out++ = static_cast<Derived*>(this)->decode_one(first, last);
                    }
                    return out;
                }
            };
        } // namespace detail
    } // namespace codec
} // namespace ogonek

#endif // OGONEK_CODEC_HPP


