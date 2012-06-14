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

// Unicode encoder/decoder

// # Codec concept
// Assume C is a Codec type, codec is an instance of C, u is a codepoint, b is
// a byte, [bb, be) is a range of input iterators on bytes, [cb, ce) is a range
// of input iterators on codepoints, bo is an output iterator on bytes, and co
// is an output iterator on codepoints.
//    C::is_fixed_width        | constexpr bool        | true iff is fixed width
//    C::max_width             | constexpr size_t      | maximum width
//    C::is_reusable           | constexpr bool        | true iff is the codec can be reused
//    C::is_stateless          | constexpr bool        | true iff is each codepoint can be encoded individually
//    C codec;                 | C                     | creates a new codec
//    C()                      | C                     | creates a new codec
//    codec.encode(cb, ce, bo) | output iterator       | encodes codepoints
//    codec.decode(bb, be, co) | output iterator       | decodes codepoints
//    codec.encode_one(c, bo)  | void                  | encodes one codepoint (only available if is_stateless)
//    codec.decode_one(bb, be) | codepoint             | decodes one codepoint (only available if is_stateless)
//TODO: bytes vs code units?

#ifndef OGONEK_CODEC_HPP
#define OGONEK_CODEC_HPP

#include "codec/utf8.h++"
#include "codec/utf16.h++"
#include "codec/utf32.h++"
#include "codec/utf7.h++"

#endif // OGONEK_CODEC_HPP

