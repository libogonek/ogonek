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

// Unicode text string core

#ifndef OGONEK_TEXT_CORE_HPP
#define OGONEK_TEXT_CORE_HPP

#include <ogonek/detail/ranges.h++>
#include <ogonek/types.h++>
#include <ogonek/traits.h++>
#include <ogonek/error_handler.h++>
#include <ogonek/assume_valid.h++>
#include <ogonek/throw_error.h++>
#include <ogonek/encoding/iterator.h++>
#include <ogonek/encoding/utf16.h++>
#include <ogonek/encoding/utf32.h++>

#include <wheels/meta.h++>

#include <boost/range/iterator_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <initializer_list>
#include <string>
#include <type_traits>
#include <utility>

namespace ogonek {
    template <typename EncodingForm, typename Container>
    class text;
    
    namespace detail {
        template <typename EncodingForm>
        struct validated {
            validated() = default;
            template <typename Range>
            validated(Range const& range) : validated(range, default_error_handler) {}
            template <typename Range, typename ErrorHandler>
            validated(Range const& range, ErrorHandler) {
                for(auto&& _ : EncodingForm::decode(range, ErrorHandler{})) {
                    (void)_; // do nothing, just consume the input
                }
            }
        };
        
        class decoding_iterator_access {
            template <typename EncodingForm, typename Iterator, typename ErrorHandler>
            static Iterator first(decoding_iterator<EncodingForm, Iterator, ErrorHandler> const& it) { return it.first; }
            
            template <typename EncodingForm, typename Container>
            friend class ::ogonek::text;
        };
    } // namespace detail

    template <typename EncodingForm>
    using DefaultContainer = std::basic_string<CodeUnit<EncodingForm>>;

    template <typename EncodingForm, typename Container = DefaultContainer<EncodingForm>>
    struct text : private detail::validated<EncodingForm> {
    private:
        static_assert(std::is_convertible<CodeUnit<EncodingForm>, detail::ValueType<Container>>(),
                      "The encoding form code units should be convertible to the container's value type");
        static_assert(std::is_convertible<detail::ValueType<Container>, CodeUnit<EncodingForm>>(),
                      "The container's value type should be convertible to the encoding form code units");

        struct direct {};

    public:
        static constexpr bool validated = true;

        //** Constructors **
        // -- basic
        //! Empty string
        text() = default;

        text(text const&) = default;
        text(text&&) = default;

        // -- safe implicit conversions
        //! Construct from a different text
        template <typename EncodingForm1, typename Container1>
        text(text<EncodingForm1, Container1> const& that)
        : text(that, default_error_handler) {}
        
        //! Construct from a different text, same encoding, ignore validation
        template <typename Container1, typename ErrorHandler,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...>
        text(text<EncodingForm, Container1> const& that, ErrorHandler)
        : storage_(that.storage_.begin(), that.storage_.end()) {}
        
        //! Construct from a different text, different encoding, with validation
        template <typename EncodingForm1, typename Container1, typename ErrorHandler,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...>
        text(text<EncodingForm1, Container1> const& that, ErrorHandler)
        : text(direct{}, EncodingForm::encode(that, ErrorHandler{})) {}
        
        // -- ranges
        //! Construct from an initializer list
        explicit text(std::initializer_list<code_point> list)
        : text(list, default_error_handler) {}
        //! Construct from an initializer list, with validation strategy
        template <typename ErrorHandler,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...>
        explicit text(std::initializer_list<code_point> list, ErrorHandler)
        : text(direct{}, EncodingForm::encode(list, ErrorHandler{})) {}
        //! Construct from a code point sequence
        template <typename UnicodeSequence,
                  wheels::EnableIf<detail::is_unicode_sequence<UnicodeSequence const&>>...>
        explicit text(UnicodeSequence const& sequence)
        : text(sequence, default_error_handler) {}

        //! Construct from a code point sequence, with validation policy
        template <typename UnicodeSequence, typename ErrorHandler,
                  wheels::EnableIf<detail::is_unicode_sequence<UnicodeSequence>>...,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...>
        text(UnicodeSequence const& sequence, ErrorHandler)
        : text(direct{}, EncodingForm::encode(detail::as_code_point_range(sequence, ErrorHandler{}), ErrorHandler{})) {}

        // -- storage
        //! Construct directly from a container
        explicit text(Container const& storage) : text(storage, default_error_handler) {}

        //! Construct directly from a container, with validation
        template <typename ErrorHandler,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...>
        text(Container const& storage, ErrorHandler)
        : text(direct{}, EncodingForm::encode(EncodingForm::decode(storage, ErrorHandler{}), assume_valid)) {}

        //! Construct directly from a container, moving
        explicit text(Container&& storage) : text(std::move(storage), default_error_handler) {}
        
        //! Construct directly from a container, with throwing validation, moving
        text(Container&& storage, throw_error_t)
        : detail::validated<EncodingForm>(storage, throw_error), storage_(std::move(storage)) {}

        //! Construct directly from a container, without validation, moving
        text(Container&& storage, assume_valid_t)
        : storage_(std::move(storage)) {}

        //! Construct directly from a container, with validation, (not) moving
        template <typename ErrorHandler,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...>
        text(Container&& storage, ErrorHandler)
        : text(storage, ErrorHandler{}) {}
        
        //** Assignments **
        // Copies and moves
        text& operator=(text const&) = default;
        text& operator=(text&&) = default;
        template <typename Container1>
        text& operator=(text<EncodingForm, Container1> const& that) {
            storage_.assign(that.storage_.begin(), that.storage_.end());
            return *this;
        }
        template <typename EncodingForm1, typename Container1>
        text& operator=(text<EncodingForm1, Container1> const& that) {
            assign(that, default_error_handler);
            return *this;
        }

        void assign(std::initializer_list<code_point> list) {
            assign(list, default_error_handler);
        }
        template <typename ErrorHandler,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...>
        void assign(std::initializer_list<code_point> list, ErrorHandler) {
            assign<std::initializer_list<code_point>>(list, ErrorHandler{});
        }
        
        void assign(text const& that) { operator=(that); }
        template <typename ErrorHandler,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...>
        void assign(text const& that, ErrorHandler) { operator=(that); }

        void assign(text&& that) { operator=(std::move(that)); }
        template <typename ErrorHandler,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...>
        void assign(text&& that, ErrorHandler) { operator=(std::move(that)); }
        
        template <typename Container1, typename ErrorHandler,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...>
        void assign(text<EncodingForm, Container1> const& that, ErrorHandler) {
            storage_.assign(that.storage_.begin(), that.storage_.end());
        }
        
        void assign(char32_t const* literal) {
            assign(literal, default_error_handler);
        }
        template <typename ErrorHandler,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...>
        void assign(char32_t const* literal, ErrorHandler) {
            assign(utf32::decode(make_range(literal), ErrorHandler{}), ErrorHandler{});
        }

        // fishy
        void assign(char16_t const* literal) {
            assign(literal, default_error_handler);
        }
        template <typename ErrorHandler,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...>
        void assign(char16_t const* literal, ErrorHandler) {
            assign(utf16::decode(make_range(literal), ErrorHandler{}), ErrorHandler{});
        }
        
        template <typename UnicodeSequence,
                  wheels::EnableIf<detail::is_unicode_sequence<UnicodeSequence>>...,
                  wheels::DisableIf<wheels::is_related<UnicodeSequence, text<EncodingForm, Container>>>...>
        void assign(UnicodeSequence const& that) {
            assign(that, default_error_handler);
        }
        template <typename UnicodeSequence, typename ErrorHandler,
                  wheels::EnableIf<detail::is_unicode_sequence<UnicodeSequence>>...,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...,
                  wheels::DisableIf<wheels::is_related<UnicodeSequence, text<EncodingForm, Container>>>...>
        void assign(UnicodeSequence const& that, ErrorHandler) {
            insert_code_units(storage_.end(), EncodingForm::encode(detail::as_code_point_range(that, ErrorHandler{}), ErrorHandler{}));
        }

        //** Range **
        // TODO iterator convertible to const_iterator
        using iterator = decoding_iterator<EncodingForm, detail::Iterator<Container>, assume_valid_t>;
        using const_iterator = decoding_iterator<EncodingForm, detail::ConstIterator<Container>, assume_valid_t>;

        iterator begin() { return iterator { storage_.begin(), storage_.end() }; }
        iterator end() { return iterator { storage_.end(), storage_.end() }; }
        const_iterator begin() const { return const_iterator { storage_.begin(), storage_.end() }; }
        const_iterator end() const { return const_iterator { storage_.end(), storage_.end() }; }

        //** Interoperation **
        //! Move the underlying storage out
        Container extract_storage() {
            return std::move(storage_);
        }
        //! View the underlying storage
        Container const& storage() const {
            return storage_;
        }

        //** Operations **
        // -- empty
        bool empty() const { return storage_.empty(); }

        // -- appending
        void append(text const& that) {
            insert_code_units(storage_.end(), that.storage_);
        }
        template <typename ErrorHandler,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...>
        void append(text const& that, ErrorHandler) {
            append(that);
        }
        void append(std::initializer_list<code_point> list) {
            append(list, default_error_handler);
        }
        template <typename ErrorHandler,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...>
        void append(std::initializer_list<code_point> list, ErrorHandler) {
            append<std::initializer_list<code_point>>(list, ErrorHandler{});
        }
        template <typename UnicodeSequence,
                  wheels::EnableIf<detail::is_unicode_sequence<UnicodeSequence>>...,
                  wheels::DisableIf<wheels::is_related<UnicodeSequence, text<EncodingForm, Container>>>...>
        void append(UnicodeSequence const& sequence) {
            append(sequence, default_error_handler);
        }
        template <typename UnicodeSequence, typename ErrorHandler,
                  wheels::EnableIf<detail::is_unicode_sequence<UnicodeSequence>>...,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...,
                  wheels::DisableIf<wheels::is_related<UnicodeSequence, text<EncodingForm, Container>>>...>
        void append(UnicodeSequence const& sequence, ErrorHandler) {
            insert_code_units(storage_.end(), EncodingForm::encode(detail::as_code_point_range(sequence, ErrorHandler{}), ErrorHandler{}));
        }
        
        // -- erasure
        template <typename Range>
        iterator erase(Range const& range) {
            return erase(boost::begin(range), boost::end(range));
        }
        iterator erase(iterator from, iterator to) {
            return {
                storage_.erase(detail::decoding_iterator_access::first(from), detail::decoding_iterator_access::first(to)),
                storage_.end()
            };
        }

        // -- inserting
        void insert(iterator at, text const& that) {
            insert_code_units(detail::decoding_iterator_access::first(at), that.storage_);
        }
        template <typename ErrorHandler,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...>
        void insert(iterator at, text const& that, ErrorHandler) {
            insert(at, that);
        }
        void insert(iterator at, std::initializer_list<code_point> list) {
            insert(at, list, default_error_handler);
        }
        template <typename ErrorHandler,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...>
        void insert(iterator at, std::initializer_list<code_point> list, ErrorHandler) {
            insert<std::initializer_list<code_point>>(at, list, ErrorHandler{});
        }
        template <typename UnicodeSequence,
                  wheels::EnableIf<detail::is_unicode_sequence<UnicodeSequence>>...,
                  wheels::DisableIf<wheels::is_related<UnicodeSequence, text<EncodingForm, Container>>>...>
        void insert(iterator at, UnicodeSequence const& sequence) {
            insert(at, sequence, default_error_handler);
        }
        template <typename UnicodeSequence, typename ErrorHandler,
                  wheels::EnableIf<detail::is_unicode_sequence<UnicodeSequence>>...,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...,
                  wheels::DisableIf<wheels::is_related<UnicodeSequence, text<EncodingForm, Container>>>...>
        void insert(iterator at, UnicodeSequence const& sequence, ErrorHandler) {
            insert_code_units(detail::decoding_iterator_access::first(at),
                              EncodingForm::encode(detail::as_code_point_range(sequence, ErrorHandler{}), ErrorHandler{}));
        }
        
        // -- replacing
        template <typename Range, typename UnicodeSequence>
        void replace(Range const& range, UnicodeSequence const& sequence) {
            replace(range, std::forward<UnicodeSequence>(sequence), default_error_handler);
        }
        template <typename Range, typename UnicodeSequence, typename ErrorHandler>
        void replace(Range const& range, UnicodeSequence const& sequence, ErrorHandler) {
            replace(boost::begin(range), boost::end(range), sequence, ErrorHandler{});
        }
        template <typename Range>
        void replace(Range const& range, std::initializer_list<code_point> list) {
            replace(range, list, default_error_handler);
        }
        template <typename Range, typename ErrorHandler>
        void replace(Range const& range, std::initializer_list<code_point> list, ErrorHandler) {
            replace(boost::begin(range), boost::end(range), list, ErrorHandler{});
        }
        
        void replace(iterator from, iterator to, text const& that) {
            auto it = erase(from, to);
            insert_code_units(detail::decoding_iterator_access::first(it), that.storage_);
        }
        template <typename ErrorHandler,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...>
        void replace(iterator from, iterator to, text const& that, ErrorHandler) {
            replace(from, to, that);
        }
        void replace(iterator from, iterator to, std::initializer_list<code_point> list) {
            replace(from, to, list, default_error_handler);
        }
        template <typename ErrorHandler,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...>
        void replace(iterator from, iterator to, std::initializer_list<code_point> list, ErrorHandler) {
            replace<std::initializer_list<code_point>>(from, to, list, ErrorHandler{});
        }
        template <typename UnicodeSequence,
                  wheels::EnableIf<detail::is_unicode_sequence<UnicodeSequence>>...,
                  wheels::DisableIf<wheels::is_related<UnicodeSequence, text<EncodingForm, Container>>>...>
        void replace(iterator from, iterator to, UnicodeSequence const& sequence) {
            replace(from, to, sequence, default_error_handler);
        }
        template <typename UnicodeSequence, typename ErrorHandler,
                  wheels::EnableIf<detail::is_unicode_sequence<UnicodeSequence>>...,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...,
                  wheels::DisableIf<wheels::is_related<UnicodeSequence, text<EncodingForm, Container>>>...>
        void replace(iterator from, iterator to, UnicodeSequence const& sequence, ErrorHandler) {
            auto it = erase(from, to);
            insert_code_units(detail::decoding_iterator_access::first(it),
                              EncodingForm::encode(detail::as_code_point_range(sequence, ErrorHandler{}), ErrorHandler{}));
        }
    private:
        boost::iterator_range<char32_t const*> make_range(char32_t const* literal) {
            return boost::make_iterator_range(literal, literal + std::char_traits<char32_t>::length(literal));
        }
        boost::iterator_range<char16_t const*> make_range(char16_t const* literal) {
            return boost::make_iterator_range(literal, literal + std::char_traits<char16_t>::length(literal));
        }
        
        template <typename CodeUnitRange>
        text(direct, CodeUnitRange&& range)
        : storage_(boost::begin(range), boost::end(range)) {}
        
        template <typename CodeUnitRange>
        void insert_code_units(detail::Iterator<Container> it, CodeUnitRange const& range) {
            static_assert(is_stateless<EncodingForm>(), "inserting with stateful encodings is not supported");
            storage_.insert(it, boost::begin(range), boost::end(range));
        }

        template <typename, typename>
        friend class text;
        
        Container storage_;
    };
} // namespace ogonek

#endif // OGONEK_TEXT_CORE_HPP
