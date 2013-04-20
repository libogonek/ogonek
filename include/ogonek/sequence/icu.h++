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

#include <ogonek/sequence/properties.h++>

#include <taussig/primitives/as_sequence.h++>

#include <unicode/unistr.h>

namespace seq {
    template <>
    struct sequence_source<icu::UnicodeString> {
        struct result : ogonek::detail::ogonek_sequence<> {
        public:
            result(icu::UnicodeString const& u)
            : u(&u), l(0), r(u.length()) {}

            using value_type = char16_t;
            using reference = value_type;

            bool empty() const { return l == r; }
            reference front() const { return u->charAt(l); }
            void pop_front() { ++l; }
            result save() const { return *this; }
            result before(result const& that) const { return { u, l, that.l }; }

        private:
            result(icu::UnicodeString const* u, int32_t l, int32_t r) : u(u), l(l), r(r) {}

            icu::UnicodeString const* u;
            int32_t l, r;
        };
        static_assert(is_true_sequence<result>(), "result is a true sequence");
        static result forward(icu::UnicodeString const& u) { return std::forward<result>(u); }
    };
    template <>
    struct sequence_source<icu::UnicodeString const&> : sequence_source<icu::UnicodeString> {};
    template <>
    struct sequence_source<icu::UnicodeString&> : sequence_source<icu::UnicodeString> {};
    template <>
    struct sequence_source<icu::UnicodeString&&> : sequence_source<icu::UnicodeString> {};
} // namespace seq

#endif // OGONEK_SEQUENCE_ICU_HPP
