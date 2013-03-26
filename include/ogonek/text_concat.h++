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

// Text concatenation

#ifndef OGONEK_TEXT_CONCAT_HPP
#define OGONEK_TEXT_CONCAT_HPP

#include <ogonek/text_core.h++>

#include <wheels/meta.h++>

#include <type_traits>
#include <utility>

namespace ogonek {
    namespace detail {
        template <typename... T> struct list;
        
        template <typename Acc, typename... T>
        struct same_encoding_impl : wheels::Not<std::is_void<Acc>> {
            using encoding_type = Acc;
        };
        
        template <typename Acc, typename Head, typename... Tail>
        struct same_encoding_impl<Acc, Head, Tail...>
        : same_encoding_impl<Acc, Tail...> {};

        template <typename Acc, typename Container, typename... Tail>
        struct same_encoding_impl<void, text<Acc, Container>, Tail...>
        : same_encoding_impl<Acc, Tail...> {};
        
        template <typename Acc, typename Container, typename... Tail>
        struct same_encoding_impl<Acc, text<Acc, Container>, Tail...>
        : same_encoding_impl<Acc, Tail...> {};
        
        template <typename Acc, typename EncodingForm, typename Container, typename... Tail>
        struct same_encoding_impl<Acc, text<EncodingForm, Container>, Tail...>
        : std::false_type {
            using container_type = void;
        };

        template <typename T>
        struct same_encoding;
        template <typename... T>
        struct same_encoding<list<T...>> : same_encoding_impl<void, wheels::Unqualified<T>...> {};
        template <typename... T>
        using SameEncoding = typename same_encoding<T...>::encoding_type;

        template <typename Acc, typename... T>
        struct same_container_impl : wheels::Not<std::is_void<Acc>> {
            using container_type = Acc;
        };
        
        template <typename Acc, typename Head, typename... Tail>
        struct same_container_impl<Acc, Head, Tail...>
        : same_container_impl<Acc, Tail...> {};

        template <typename Acc, typename EncodingForm, typename... Tail>
        struct same_container_impl<void, text<EncodingForm, Acc>, Tail...>
        : same_container_impl<Acc, Tail...> {};
        
        template <typename Acc, typename EncodingForm, typename... Tail>
        struct same_container_impl<Acc, text<EncodingForm, Acc>, Tail...>
        : same_container_impl<Acc, Tail...> {};
        
        template <typename Acc, typename EncodingForm, typename Container, typename... Tail>
        struct same_container_impl<Acc, text<EncodingForm, Container>, Tail...>
        : std::false_type {
            using container_type = void;
        };

        template <typename T>
        struct same_container;
        template <typename... T>
        struct same_container<list<T...>> : same_container_impl<void, wheels::Unqualified<T>...> {};
        template <typename... T>
        using SameContainer = typename same_container<T...>::container_type;
        
        template <typename Result, typename ErrorHandler>
        Result concat_impl() { return Result{}; }
        template <typename Result, typename ErrorHandler>
        void concat_acc(Result&) {}
        template <typename Result, typename ErrorHandler, typename Head, typename... Tail>
        void concat_acc(Result& acc, Head&& head, Tail&&... tail) {
            acc.append(std::forward<Head>(head), ErrorHandler{});
            concat_acc<Result, ErrorHandler>(acc, std::forward<Tail>(tail)...);
        }
        template <typename Result, typename ErrorHandler, typename Head, typename... Tail>
        Result concat_impl(Head&& head, Tail&&... tail) {
            Result result { std::forward<Head>(head) };
            concat_acc<Result, ErrorHandler>(result, std::forward<Tail>(tail)...);
            return result;
        }

        template <typename EncodingForm, typename Container,
                  typename UnicodeSequences,
                  bool = wheels::is_deduced<EncodingForm>{},
                  bool = wheels::is_deduced<Container>{},
                  bool = detail::same_encoding<UnicodeSequences>{}
                      && detail::same_container<UnicodeSequences>{}>
        struct common_text {};

        template <typename EncodingForm, typename Container,
                  typename UnicodeSequences, bool Ignored>
        struct common_text<EncodingForm, Container, UnicodeSequences, false, false, Ignored>
        : wheels::identity<text<EncodingForm, Container>> {};
        
        template <typename EncodingForm, typename UnicodeSequences>
        struct deduce_container
        : std::conditional<
            detail::same_container<UnicodeSequences>{},
            detail::SameContainer<UnicodeSequences>,
            DefaultContainer<EncodingForm>> {};
        template <typename EncodingForm, typename... UnicodeSequences>
        using DeduceContainer = wheels::Invoke<deduce_container<EncodingForm, list<UnicodeSequences...>>>;
        
        template <typename EncodingForm, typename Container,
                  typename UnicodeSequences,
                  bool Ignored>
        struct common_text<EncodingForm, Container, UnicodeSequences, false, true, Ignored>
        : wheels::identity<text<EncodingForm, DeduceContainer<EncodingForm, UnicodeSequences>>> {};

        template <typename EncodingForm, typename Container, typename UnicodeSequences>
        struct common_text<EncodingForm, Container, UnicodeSequences, true, true, true>
        : wheels::identity<text<SameEncoding<UnicodeSequences>, SameContainer<UnicodeSequences>>> {};

        template <typename EncodingForm, typename Container, typename... UnicodeSequences>
        using CommonText = wheels::Invoke<common_text<EncodingForm, Container, list<UnicodeSequences...>>>;
    } // namespace detail

    // Concatenation
    template <typename EncodingForm = wheels::deduced, typename Container = wheels::deduced,
              typename ErrorHandler, typename... UnicodeSequences,
              wheels::EnableIf<is_error_handler<wheels::Unqualified<ErrorHandler>>>...,
              typename Text = detail::CommonText<EncodingForm, Container, UnicodeSequences...>>
    Text concat(ErrorHandler&&, UnicodeSequences&&... sequences) {
        return detail::concat_impl<Text, wheels::Unqualified<ErrorHandler>>(std::forward<UnicodeSequences>(sequences)...);
    }
    
    template <typename EncodingForm, typename Container>
    text<EncodingForm, Container> concat() { return {}; }
    
    template <typename EncodingForm = wheels::deduced, typename Container = wheels::deduced,
              typename Head, typename... Tail,
              wheels::DisableIf<is_error_handler<wheels::Unqualified<Head>>>...,
              typename Text = detail::CommonText<EncodingForm, Container, Head, Tail...>>
    Text concat(Head&& head, Tail&&... tail) {
        return concat<EncodingForm, Container>(default_error_handler, std::forward<Head>(head), std::forward<Tail>(tail)...);
    }
} // namespace ogonek

#endif // OGONEK_TEXT_CONCAT_HPP
