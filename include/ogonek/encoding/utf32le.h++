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

// UTF-32LE encoding scheme

#ifndef OGONEK_ENCODING_UTF32LE_HPP
#define OGONEK_ENCODING_UTF32LE_HPP

#include <ogonek/encoding/encoding_scheme.h++>
#include <ogonek/encoding/utf32.h++>
#include <ogonek/little_endian.h++>

namespace ogonek {
    using utf32le = encoding_scheme<utf32, little_endian>;
} // namespace ogonek

#endif // OGONEK_ENCODING_UTF32LE_HPP
