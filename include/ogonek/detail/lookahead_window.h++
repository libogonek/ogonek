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

// Window of lookaheads

#ifndef OGONEK_DETAIL_LOOKAHEAD_WINDOW_HPP
#define OGONEK_DETAIL_LOOKAHEAD_WINDOW_HPP

#include <algorithm>
#include <array>
#include <type_traits>

#include <cstddef>

namespace ogonek {
    namespace detail {
        template <typename Iterator, int Before, int After>
        struct lookahead_window {
            using value_type = typename std::iterator_traits<Iterator>::value_type;
            static_assert(std::is_pod<value_type>::value, "T must be POD");
        public:
            lookahead_window(Iterator first, Iterator last)
            : head(first), next_head(first), reader(first), last(last) {
                std::fill(data.begin(), data.end(), -1);
                for(auto i = 0; i <= After; ++i) {
                    scroll();
                    read_next();
                }
                advance();
            }

            void advance(int limit = -Before) {
                scroll(limit);
                read_next();
                if(limit <= 0) advance_head();
                if(limit == 1) ++next_head;
            }
            bool exhausted() const {
                return head == last;
            }

            value_type operator[](int n) const {
                return data[Before + n];
            }

            Iterator position() const {
                return head;
            }

        private:
            void scroll(int limit = -Before) {
                for(auto i = limit; i < After; ++i) {
                    data[Before + i] = data[Before + i + 1];
                }
            }

            void advance_head() {
                if(head != next_head) head = ++next_head;
                else next_head = ++head;
            }

            void read_next() {
                if(reader == last) {
                    if(ahead_ > 0) --ahead_;
                    data.back() = -1;
                } else {
                    if(ahead_ < After) ++ahead_;
                    data.back() = *reader++;
                }
            }

            int ahead_ = 0;
            std::array<value_type, Before + 1 + After> data;
            Iterator head, next_head, reader, last;
        };
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_DETAIL_LOOKAHEAD_WINDOW_HPP
