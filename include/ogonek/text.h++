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

// Unicode text class

#ifndef OGONEK_TEXT_HPP
#define OGONEK_TEXT_HPP

namespace ogonek {
    using byte = char;
    using codepoint = char32_t;

    class text {
    private:
        std::vector<codepoint> codepoints;

    public:
        class iterator;
        class const_iterator;

        text();
        text(text const&);
        text(text&&);
        ~text();
        text& operator=(text const&);
        text& operator=(text&&);
    };
} // namespace ogonek

#endif // OGONEK_TEXT_HPP

