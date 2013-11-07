// Ogonek
//
// Written in 2013 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// This file was automatically generated on 2013-11-14T13:59:12.462338Z

// ISO-8859-7 encoding form

#ifndef OGONEK_ISO8859_7_HPP
#define OGONEK_ISO8859_7_HPP

#include <ogonek/types.h++>
#include <ogonek/encoding/codepage_encoding.h++>

namespace ogonek {
    struct iso8859_7_codepage {
        static code_point to_unicode[256];
        static codepage_entry from_unicode[253];
    };

    using iso8859_7 = codepage_encoding<iso8859_7_codepage>;
} // namespace ogonek

#endif // OGONEK_ISO8859_7_HPP
