// Ogonek
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

#include "types.h++"

#include <cstddef>
#include <vector>

namespace ogonek {
    class text {
    private:
        std::vector<codepoint> codepoints; // TODO: allocators

    public:
        using iterator = std::vector<codepoint>::const_iterator;
        using const_iterator = std::vector<codepoint>::const_iterator;

        text();
        text(text const&);
        text(text&&);
        ~text();
        text& operator=(text const&);
        text& operator=(text&&);

        const_iterator begin() const;
        const_iterator end() const;

        codepoint const* data() const;

        codepoint operator[](std::ptrdiff_t i) const;
    };
} // namespace ogonek

#endif // OGONEK_TEXT_HPP

