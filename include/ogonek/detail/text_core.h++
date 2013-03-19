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

// Unicode text string - core without normalization dependencies

#ifndef OGONEK_DETAIL_TEXT_CORE_HPP
#define OGONEK_DETAIL_TEXT_CORE_HPP

#include <ogonek/detail/ranges.h++>
#include <ogonek/encoding/iterator.h++>
#include <ogonek/traits.h++>
#include <ogonek/types.h++>
#include <ogonek/error.h++>
#include <ogonek/encoding/utf16.h++>
#include <ogonek/encoding/utf32.h++>

#include <wheels/smart_ptr/unique_ptr.h++>

#include <boost/range/sub_range.hpp>
#include <boost/range/value_type.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/any_range.hpp>

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
        static_assert(std::is_convertible<CodeUnit<EncodingForm>, detail::ValueType<Container>>::value,
                      "The encoding form code units should be convertible to the container's value type");
        static_assert(std::is_convertible<detail::ValueType<Container>, CodeUnit<EncodingForm>>::value,
                      "The container's value type should be convertible to the encoding form code units");

        struct direct {};

    public:
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
        : text(direct{}, EncodingForm::encode(EncodingForm::decode(storage, ErrorHandler{}), skip_validation)) {}

        //! Construct directly from a container, moving
        explicit text(Container&& storage) : text(std::move(storage), default_error_handler) {}
        
        //! Construct directly from a container, with throwing validation, moving
        text(Container&& storage, throw_error_t)
        : detail::validated<EncodingForm>(storage, throw_error), storage_(std::move(storage)) {}

        //! Construct directly from a container, without validation, moving
        text(Container&& storage, skip_validation_t)
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
        using iterator = decoding_iterator<EncodingForm, detail::Iterator<Container>, skip_validation_t>;
        using const_iterator = decoding_iterator<EncodingForm, detail::ConstIterator<Container>, skip_validation_t>;

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

    class utf8;
    class utf16;
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

    class any_text {
    public:
        using iterator = boost::any_range<code_point, boost::single_pass_traversal_tag, code_point, std::ptrdiff_t>::iterator;
        using const_iterator = iterator;

    private:
        class placeholder;
        using handle_type = std::unique_ptr<placeholder>;

        class placeholder {
        public:
            placeholder() = default;
            virtual ~placeholder() = default;

            virtual handle_type clone() = 0;

            virtual iterator begin() = 0;
            virtual const_iterator end() = 0;
            virtual iterator begin() const = 0;
            virtual const_iterator end() const = 0;

            virtual void* get() = 0;
            virtual void const* get() const = 0;

            virtual bool empty() const = 0;
            
        protected:
            placeholder(placeholder const&) = default;
            placeholder(placeholder&&) = default;
        };

        template <typename EncodingForm, typename Container>
        class holder : public placeholder {
        public:
            using text_type = text<EncodingForm, Container>;

            holder(text_type const& t) : t(t) {}
            holder(text_type&& t) : t(std::move(t)) {}

            handle_type clone() override {
                return handle_type { new holder(*this) }; // :( private ctor
            }

            iterator begin() override { return iterator { t.begin() }; }
            iterator end() override { return iterator { t.end() }; }
            const_iterator begin() const override { return const_iterator { t.begin() }; }
            const_iterator end() const override { return const_iterator { t.end() }; }

            void* get() override { return &t; }
            void const* get() const override { return &t; }
            
            bool empty() const override { return t.empty(); }

        private:
            holder(holder const&) = default;
            holder(holder&&) = default;

            text_type t;
        };

    public:
        //** Constructors **
        any_text(any_text const& that)
        : handle { that.handle->clone() } {}
        any_text(any_text&&) = default;
        any_text& operator=(any_text const& that) {
            handle = handle_type { that.handle->clone() };
            return *this;
        }
        any_text& operator=(any_text&&) = default;

        template <typename EncodingForm, typename Container>
        any_text(text<EncodingForm, Container> const& text)
        : handle { wheels::make_unique<holder<EncodingForm, Container>>(text) } {}
        template <typename EncodingForm, typename Container>
        any_text(text<EncodingForm, Container>&& text)
        : handle { wheels::make_unique<holder<EncodingForm, Container>>(std::move(text)) } {}

        template <typename EncodingForm, typename Container>
        any_text& operator=(text<EncodingForm, Container> const& text) {
            handle = wheels::make_unique<holder<EncodingForm, Container>>(text);
            return *this;
        }
        template <typename EncodingForm, typename Container>
        any_text& operator=(text<EncodingForm, Container>&& text) {
            handle = wheels::make_unique<holder<EncodingForm, Container>>(std::move(text));
            return *this;
        }

        iterator begin() { return handle->begin(); }
        iterator end() { return handle->end(); }
        const_iterator begin() const { return handle->begin(); }
        const_iterator end() const { return handle->end(); }

        template <typename Text>
        Text& get() { return *static_cast<Text*>(handle->get()); }
        template <typename Text>
        Text const& get() const { return *static_cast<Text const*>(handle->get()); }
        
        bool empty() const { return handle->empty(); }

    private:
        handle_type handle;
    };
    
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

#endif // OGONEK_DETAIL_TEXT_CORE_HPP