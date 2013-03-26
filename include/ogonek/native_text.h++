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

// Native text

#ifndef OGONEK_NATIVE_TEXT_HPP
#define OGONEK_NATIVE_TEXT_HPP

#include <ogonek/text.h++>
#include <ogonek/encoding/utf8.h++>
#include <ogonek/encoding/utf8.h++>
//#include <ogonek/encoding/narrow.h++>
//#include <ogonek/encoding/wide.h++>

#include <string>

namespace ogonek {
    using posix_text = text<utf8, std::string>;
    using windows_text = text<utf16, std::wstring>;
#if defined(OGONEK_WINDOWS)
    using native_text = windows_text;
#elif defined(OGONEK_POSIX)
    using native_text = posix_text;
#endif

    class narrow;
    class wide;
    using narrow_text = text<narrow, std::string>;
    using wide_text = text<wide, std::wstring>;
} // namespace ogonek

#endif // OGONEK_NATIVE_TEXT_HPP
