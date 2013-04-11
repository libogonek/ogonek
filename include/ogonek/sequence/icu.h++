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

// ICU interoperation

#ifndef OGONEK_SEQUENCE_ICU_HPP
#define OGONEK_SEQUENCE_ICU_HPP

#include <ogonek/sequence/as_sequence.h++>

#include <unicode/unistr.h>

namespace ogonek {
    namespace detail {
        template <>
        struct as_sequence_impl<icu::UnicodeString, false, false, false> {
            struct result : native_sequence {
            public:
                result(icu::UnicodeString const& u) : u(&u) {}

                using value_type = char16_t;
                using reference = value_type;

                bool empty() const { return i == u->length(); }
                reference front() const { return u->charAt(i); }
                void pop_front() { ++i; }
                result save() const { return *this; }

            private:
                int32_t i = 0;
                icu::UnicodeString const* u;
            };
            static result forward(icu::UnicodeString const& u) { return std::forward<result>(u); }
        };
        template <>
        struct as_sequence_impl<icu::UnicodeString const&, false, false, false> : as_sequence_impl<icu::UnicodeString> {};
        template <>
        struct as_sequence_impl<icu::UnicodeString&, false, false, false> : as_sequence_impl<icu::UnicodeString> {};
    } // namespace ogonek
} // namespace ogonek

#endif // OGONEK_SEQUENCE_ICU_HPP
