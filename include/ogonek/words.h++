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

// Word segmentation

#ifndef OGONEK_WORDS_HPP
#define OGONEK_WORDS_HPP

#include <ogonek/types.h++>
#include <ogonek/ucd.h++>
#include <ogonek/detail/lookahead_window.h++>
#include <ogonek/detail/ranges.h++>

#include <wheels/enums.h++>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/iterator_range.hpp>

#include <algorithm>
#include <iterator>
#include <type_traits>

namespace ogonek {
    namespace detail {
        using wb = ucd::word_break;
        struct word_rule {
            wb before1;
            wb before0;
            bool is_break;
            wb after0;
            wb after1;

            bool matches(code_point before1, code_point before0, code_point after0, code_point after1) const;
        };
    } // namespace detail
} // namespace ogonek

namespace wheels {
    template <>
    struct is_flags<ogonek::detail::wb> : std::true_type {};
} // namespace wheels

namespace ogonek {
    namespace detail {
        constexpr wb wb_any = static_cast<wb>(0xFFFFFFFFu);
        struct wb_seq {
            wb first;
            wb second;
        };
        constexpr wb_seq operator+(wb l, wb r) { return { l, r }; }
        constexpr word_rule operator*(wb l, wb r) { return { wb_any, l, false, r, wb_any }; }
        constexpr word_rule operator*(wb_seq l, wb r) { return { l.first, l.second, false, r, wb_any }; }
        constexpr word_rule operator*(wb l, wb_seq r) { return { wb_any, l, false, r.first, r.second }; }
        constexpr word_rule operator/(wb l, wb r) { return { wb_any, l, true,  r, wb_any }; }

        // TODO: switch to a pair table instead
        constexpr word_rule word_rules[] = {
            // Break at the start and end of text.
            // * Handled specially
            // Do not break within CRLF.
            /* WB3. */                                wb::CR * wb::LF,
            /* WB3a. */           (wb::NL | wb::CR | wb::LF) / wb_any,
            /* WB3b. */                               wb_any / (wb::NL | wb::CR | wb::LF),
            // Ignore Format and Extend characters, except when they appear at the beginning of a region of text.
            /* WB4. */           ~(wb::NL | wb::CR | wb::LF) * (wb::Extend | wb::FO),
            // Do not break between most letters.
            /* WB5. */                                wb::LE * wb::LE,
            // Do not break letters across certain punctuation.
            /* WB6. */                                wb::LE * ((wb::ML | wb::MB) + wb::LE),
            /* WB7. */          (wb::LE + (wb::ML | wb::MB)) * wb::LE,
            // Do not break within sequences of digits, or digits adjacent to letters ("3a", or "A3").
            /* WB8. */                                wb::NU * wb::NU,
            /* WB9. */                                wb::LE * wb::NU,
            /* WB10. */                               wb::NU * wb::LE,
            // Do not break within sequences, such as "3.2" or "3,456.789".
            /* WB11. */         (wb::NU + (wb::MN | wb::MB)) * wb::NU,
            /* WB12. */                               wb::NU * ((wb::MN | wb::MB) + wb::NU),
            // Do not break between Katakana.
            /* WB13. */                               wb::KA * wb::KA,
            // Do not break from extenders.
            /* WB13a. */ (wb::LE | wb::NU | wb::KA | wb::EX) * wb::EX,
            /* WB13b. */                              wb::EX * (wb::LE | wb::NU | wb::KA | wb::EX),
            // Do not break between regional indicator symbols.
            /* WB13c. */                              wb::RI * wb::RI,
            // Otherwise, break everywhere (including around ideographs).
            /* WB14. */                               wb_any / wb_any,
        };
        inline bool word_rule::matches(code_point before1, code_point before0, code_point after0, code_point after1) const {
            const wb none = static_cast<wb>(0);
            return (this->before1 == wb_any || (before1 != -1u && (ucd::get_word_break(before1) & this->before1) != none))
                && (ucd::get_word_break(before0) & this->before0) != none
                && (ucd::get_word_break(after0) & this->after0) != none
                && (this->after1 == wb_any || (after1 != -1u && (ucd::get_word_break(after1) & this->after1) != none));
        }
        inline bool is_word_boundary(code_point before1, code_point before0, code_point after0, code_point after1) {
            return std::find_if(std::begin(word_rules), std::end(word_rules),
                                [before1, before0, after0, after1](word_rule const& rule) {
                                    return rule.matches(before1, before0, after0, after1);
                                })
                   ->is_break;
        }
        inline bool should_skip_in_word(code_point before, code_point after) {
            return before != -1u && after != -1u &&
                word_rules[3].matches(-1, before, after, -1);
                //|| word_rules[3].matches(-1, after, before, -1));
        }

        template <typename CodePointIterator>
        struct word_iterator
        : boost::iterator_facade<
            word_iterator<CodePointIterator>,
            boost::iterator_range<CodePointIterator>,
            std::input_iterator_tag, // TODO
            boost::iterator_range<CodePointIterator>>
        {
        public:
            word_iterator(CodePointIterator first, CodePointIterator last)
            : first(first), last(last) {}

        private:
            friend class boost::iterator_core_access;

            boost::iterator_range<CodePointIterator> dereference() const {
                detail::lookahead_window<CodePointIterator, 2, 2> window(first, last);

                do {
                    while(detail::should_skip_in_word(window[-1], window[0])) {
                        window.skip(0);
                    }
                    while(detail::should_skip_in_word(window[0], window[1])) {
                        window.skip(1);
                    }
                    while(detail::should_skip_in_word(window[1], window[2])) {
                        window.skip(2);
                    }
                    if(detail::is_word_boundary(window[-2], window[-1], window[0], window[1])) break;
                    window.advance();
                } while(true);
                return boost::iterator_range<CodePointIterator> { first, window.position() };
            }
            void increment() {
                first = dereference().end();
            }
            bool equal(word_iterator const& that) const {
                return first == that.first;
            }

            CodePointIterator first;
            CodePointIterator last;
        };
    } // namespace detail
    
    template <typename UnicodeSequence, // TODO use UnicodeSequenceIterator
              typename Iterator = detail::word_iterator<detail::RangeConstIterator<UnicodeSequence>>>
    boost::iterator_range<Iterator> words(UnicodeSequence const& sequence) {
        return detail::wrap_range<Iterator>(detail::as_code_point_range(sequence, assume_valid));
    }
} // namespace ogonek

#endif // OGONEK_WORDS_HPP
