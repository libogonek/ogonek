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

// Unicode text string

#ifndef OGONEK_TEXT_HPP
#define OGONEK_TEXT_HPP

#include <ogonek/encoding/iterator.h++>
#include <ogonek/traits.h++>
#include <ogonek/types.h++>
#include <ogonek/validation.h++>
#include <ogonek/encoding/utf16.h++>

#include <wheels/smart_ptr/unique_ptr.h++>

#include <boost/range/sub_range.hpp>
#include <boost/range/value_type.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/any_range.hpp>

#include <type_traits>
#include <string>
#include <memory>
#include <iterator>

namespace ogonek {
    template <typename EncodingForm, typename Container>
    class text;
    
    namespace detail {
        template <typename EncodingForm>
        struct validated {
            validated() = default;
            template <typename Range>
            validated(Range const& range) : validated(range, default_validation) {}
            template <typename Range, typename Validation>
            validated(Range const& range, Validation) {
                for(auto&& _ : EncodingForm::decode(range, Validation{})) {
                    (void)_; // do nothing, just consume the input
                }
            }
        };

        template <typename Container>
        using Iterator = typename Container::iterator;
        template <typename Container>
        using ConstIterator = typename Container::const_iterator;
        template <typename Container>
        using ValueType = typename Container::value_type;
        template <typename Iterator>
        using IteratorValue = typename std::iterator_traits<Iterator>::value_type;

        template <typename T>
        struct range_iterator
        : wheels::Conditional<std::is_const<T>,
                              boost::range_const_iterator<wheels::RemoveConst<T>>,
                              boost::range_mutable_iterator<T>> {};
        
        template <typename Range>
        using RangeIterator = typename range_iterator<Range>::type;
        struct range_value_tester {
            template <typename T, typename = IteratorValue<RangeIterator<T>>>
            std::true_type static test(int);
            template <typename>
            std::false_type static test(...);
        };
        template <typename Range>
        using has_range_value = wheels::TraitOf<range_value_tester, Range>;
        template <typename Range>
        using RangeValue = IteratorValue<RangeIterator<Range>>;

        template <typename Range, typename Value, bool = has_range_value<Range>()>
        struct is_range_of : std::is_same<RangeValue<Range>, Value> {};
        template <typename Range, typename Value>
        struct is_range_of<Range, Value, false> : std::false_type {};
        
        template <typename T>
        struct is_code_point_sequence : is_range_of<T, code_point> {};
        template <>
        struct is_code_point_sequence<char32_t const*> : std::true_type {};
        
        class decoding_iterator_access {
            template <typename EncodingForm, typename Iterator, typename Validation>
            static Iterator first(decoding_iterator<EncodingForm, Iterator, Validation> const& it) { return it.first; }
            
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

        // -- literals
        //! Construct from a null-terminated char32_t string (intended for UTF-32 literals)
        explicit text(char32_t const* literal)
        : text(literal, default_validation) {}

        //! Construct from a null-terminated char32_t string, with validation callback
        template <typename Validation,
                  wheels::EnableIf<detail::is_validation_strategy<Validation>>...>
        text(char32_t const* literal, Validation)
        : text(make_range(literal), Validation{}) {}

        //! Construct from a null-terminated char16_t string (intended for UTF-16 literals)
        explicit text(char16_t const* literal)
        : text(literal, default_validation) {}

        //! Construct from a null-terminated char16_t string, with validation callback
        template <typename Validation,
                  wheels::EnableIf<detail::is_validation_strategy<Validation>>...>
        text(char16_t const* literal, Validation)
        : text(utf16::decode(make_range(literal), Validation{}), skip_validation) {}

        // -- safe implicit conversions
        //! Construct from a different text
        template <typename EncodingForm1, typename Container1>
        text(text<EncodingForm1, Container1> const& that)
        : text(that, default_validation) {}
        
        //! Construct from a different text, same encoding, ignore validation
        template <typename Container1, typename Validation,
                  wheels::EnableIf<detail::is_validation_strategy<Validation>>...>
        text(text<EncodingForm, Container1> const& that, Validation)
        : storage_(that.storage_.begin(), that.storage_.end()) {}
        
        //! Construct from a different text, different encoding, with validation
        template <typename EncodingForm1, typename Container1, typename Validation,
                  wheels::EnableIf<detail::is_validation_strategy<Validation>>...>
        text(text<EncodingForm1, Container1> const& that, Validation)
        : text(direct{}, EncodingForm::encode(that, Validation{})) {}
        
        // -- ranges
        //! Construct from a codepoint sequence
        template <typename CodePointSequence,
                  wheels::EnableIf<detail::is_code_point_sequence<wheels::Unqualified<CodePointSequence>>>...,
                  wheels::DisableIf<wheels::is_related<CodePointSequence, text<EncodingForm, Container>>>...>
        explicit text(CodePointSequence const& sequence)
        : text(sequence, default_validation) {}

        //! Construct from a codepoint sequence, with validation policy
        template <typename CodePointSequence, typename Validation,
                  wheels::EnableIf<detail::is_code_point_sequence<wheels::Unqualified<CodePointSequence>>>...,
                  wheels::EnableIf<detail::is_validation_strategy<Validation>>...,
                  wheels::DisableIf<wheels::is_related<CodePointSequence, text<EncodingForm, Container>>>...>
        text(CodePointSequence const& sequence, Validation)
        : text(direct{}, EncodingForm::encode(sequence, Validation{})) {}

        // -- storage
        //! Construct directly from a container
        explicit text(Container const& storage) : text(storage, default_validation) {}

        //! Construct directly from a container, with validation
        template <typename Validation,
                  wheels::EnableIf<detail::is_validation_strategy<Validation>>...>
        text(Container const& storage, Validation)
        : text(direct{}, EncodingForm::encode(EncodingForm::decode(storage, Validation{}), skip_validation)) {}

        //! Construct directly from a container, moving
        explicit text(Container&& storage) : text(std::move(storage), default_validation) {}
        
        //! Construct directly from a container, with throwing validation, moving
        text(Container&& storage, throw_validation_error_t)
        : detail::validated<EncodingForm>(storage, throw_validation_error), storage_(std::move(storage)) {}

        //! Construct directly from a container, without validation, moving
        text(Container&& storage, skip_validation_t)
        : storage_(std::move(storage)) {}

        //! Construct directly from a container, with validation, (not) moving
        template <typename Validation,
                  wheels::EnableIf<detail::is_validation_strategy<Validation>>...>
        text(Container&& storage, Validation)
        : text(storage, Validation{}) {}
        
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
            assign(that, default_validation);
            return *this;
        }
        
        void assign(text const& that) { operator=(that); }
        template <typename Validation,
                  wheels::EnableIf<detail::is_validation_strategy<Validation>>...>
        void assign(text const& that, Validation) { operator=(that); }

        void assign(text&& that) { operator=(std::move(that)); }
        template <typename Validation,
                  wheels::EnableIf<detail::is_validation_strategy<Validation>>...>
        void assign(text&& that, Validation) { operator=(std::move(that)); }
        
        template <typename Container1, typename Validation,
                  wheels::EnableIf<detail::is_validation_strategy<Validation>>...>
        void assign(text<EncodingForm, Container1> const& that, Validation) {
            storage_.assign(that.storage_.begin(), that.storage_.end());
        }
        
        void assign(char32_t const* literal) {
            assign(literal, default_validation);
        }
        template <typename Validation,
                  wheels::EnableIf<detail::is_validation_strategy<Validation>>...>
        void assign(char32_t const* literal, Validation) {
            assign(make_range(literal), Validation{});
        }

        void assign(char16_t const* literal) {
            assign(literal, default_validation);
        }
        template <typename Validation,
                  wheels::EnableIf<detail::is_validation_strategy<Validation>>...>
        void assign(char16_t const* literal, Validation) {
            assign(utf16::decode(make_range(literal), Validation{}), skip_validation);
        }
        
        template <typename CodePointSequence,
                  wheels::EnableIf<detail::is_code_point_sequence<wheels::Unqualified<CodePointSequence>>>...,
                  wheels::DisableIf<wheels::is_related<CodePointSequence, text<EncodingForm, Container>>>...>
        void assign(CodePointSequence const& that) {
            assign(that, default_validation);
        }
        template <typename CodePointSequence, typename Validation,
                  wheels::EnableIf<detail::is_code_point_sequence<wheels::Unqualified<CodePointSequence>>>...,
                  wheels::EnableIf<detail::is_validation_strategy<Validation>>...,
                  wheels::DisableIf<wheels::is_related<CodePointSequence, text<EncodingForm, Container>>>...>
        void assign(CodePointSequence const& that, Validation) {
            insert_code_units(storage_.end(), EncodingForm::encode(that, Validation{}));
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
        template <typename Validation,
                  wheels::EnableIf<detail::is_validation_strategy<Validation>>...>
        void append(text const& that, Validation) {
            append(that);
        }
        void append(char32_t const* literal) {
            append(literal, default_validation);
        }
        template <typename Validation,
                  wheels::EnableIf<detail::is_validation_strategy<Validation>>...>
        void append(char32_t const* literal, Validation) {
            append(make_range(literal), Validation{});
        }
        void append(char16_t const* literal) {
            append(literal, default_validation);
        }
        template <typename Validation,
                  wheels::EnableIf<detail::is_validation_strategy<Validation>>...>
        void append(char16_t const* literal, Validation) {
            append(utf16::decode(make_range(literal), Validation{}), skip_validation);
        }
        template <typename CodePointSequence,
                  wheels::EnableIf<detail::is_code_point_sequence<wheels::Unqualified<CodePointSequence>>>...,
                  wheels::DisableIf<wheels::is_related<CodePointSequence, text<EncodingForm, Container>>>...>
        void append(CodePointSequence const& sequence) {
            append(sequence, default_validation);
        }
        template <typename CodePointSequence, typename Validation,
                  wheels::EnableIf<detail::is_code_point_sequence<wheels::Unqualified<CodePointSequence>>>...,
                  wheels::EnableIf<detail::is_validation_strategy<Validation>>...,
                  wheels::DisableIf<wheels::is_related<CodePointSequence, text<EncodingForm, Container>>>...>
        void append(CodePointSequence const& sequence, Validation) {
            insert_code_units(storage_.end(), EncodingForm::encode(sequence, Validation{}));
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
        template <typename Validation,
                  wheels::EnableIf<detail::is_validation_strategy<Validation>>...>
        void insert(iterator at, text const& that, Validation) {
            insert(at, that);
        }
        void insert(iterator at, char32_t const* literal) {
            insert(at, literal, default_validation);
        }
        template <typename Validation,
                  wheels::EnableIf<detail::is_validation_strategy<Validation>>...>
        void insert(iterator at, char32_t const* literal, Validation) {
            insert(at, make_range(literal), Validation{});
        }
        void insert(iterator at, char16_t const* literal) {
            insert(at, literal, default_validation);
        }
        template <typename Validation,
                  wheels::EnableIf<detail::is_validation_strategy<Validation>>...>
        void insert(iterator at, char16_t const* literal, Validation) {
            insert(at, utf16::decode(make_range(literal), Validation{}), skip_validation);
        }
        template <typename CodePointSequence,
                  wheels::EnableIf<detail::is_code_point_sequence<wheels::Unqualified<CodePointSequence>>>...,
                  wheels::DisableIf<wheels::is_related<CodePointSequence, text<EncodingForm, Container>>>...>
        void insert(iterator at, CodePointSequence const& sequence) {
            insert(at, sequence, default_validation);
        }
        template <typename CodePointSequence, typename Validation,
                  wheels::EnableIf<detail::is_code_point_sequence<wheels::Unqualified<CodePointSequence>>>...,
                  wheels::EnableIf<detail::is_validation_strategy<Validation>>...,
                  wheels::DisableIf<wheels::is_related<CodePointSequence, text<EncodingForm, Container>>>...>
        void insert(iterator at, CodePointSequence const& sequence, Validation) {
            insert_code_units(detail::decoding_iterator_access::first(at), EncodingForm::encode(sequence, Validation{}));
        }
        
        // -- replacing
        template <typename Range, typename CodePointSequence>
        void replace(Range const& range, CodePointSequence&& sequence) {
            replace(range, std::forward<CodePointSequence>(sequence), default_validation);
        }
        template <typename Range, typename CodePointSequence, typename Validation>
        void replace(Range const& range, CodePointSequence&& sequence, Validation) {
            replace(boost::begin(range), boost::end(range), sequence, Validation{});
        }

        void replace(iterator from, iterator to, text const& that) {
            auto it = erase(from, to);
            insert_code_units(detail::decoding_iterator_access::first(it), that.storage_);
        }
        template <typename Validation,
                  wheels::EnableIf<detail::is_validation_strategy<Validation>>...>
        void replace(iterator from, iterator to, text const& that, Validation) {
            replace(from, to, that);
        }
        void replace(iterator from, iterator to, char32_t const* literal) {
            replace(from, to, literal, default_validation);
        }
        template <typename Validation,
                  wheels::EnableIf<detail::is_validation_strategy<Validation>>...>
        void replace(iterator from, iterator to, char32_t const* literal, Validation) {
            replace(from, to, make_range(literal), Validation{});
        }
        void replace(iterator from, iterator to, char16_t const* literal) {
            replace(from, to, literal, default_validation);
        }
        template <typename Validation,
                  wheels::EnableIf<detail::is_validation_strategy<Validation>>...>
        void replace(iterator from, iterator to, char16_t const* literal, Validation) {
            replace(from, to, utf16::decode(make_range(literal), Validation{}), skip_validation);
        }
        template <typename CodePointSequence,
                  wheels::EnableIf<detail::is_code_point_sequence<wheels::Unqualified<CodePointSequence>>>...,
                  wheels::DisableIf<wheels::is_related<CodePointSequence, text<EncodingForm, Container>>>...>
        void replace(iterator from, iterator to, CodePointSequence const& sequence) {
            replace(from, to, sequence, default_validation);
        }
        template <typename CodePointSequence, typename Validation,
                  wheels::EnableIf<detail::is_code_point_sequence<wheels::Unqualified<CodePointSequence>>>...,
                  wheels::EnableIf<detail::is_validation_strategy<Validation>>...,
                  wheels::DisableIf<wheels::is_related<CodePointSequence, text<EncodingForm, Container>>>...>
        void replace(iterator from, iterator to, CodePointSequence const& sequence, Validation) {
            auto it = erase(from, to);
            insert_code_units(detail::decoding_iterator_access::first(it), EncodingForm::encode(sequence, Validation{}));
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
} // namespace ogonek

#include <ogonek/normalization.h++>

namespace ogonek {
    template <typename SinglePassRange1, typename SinglePassRange2>
    bool canonically_equivalent(SinglePassRange1 const& lhs, SinglePassRange2 const& rhs);
        
    template <typename Encoding1, typename Container1, typename Encoding2, typename Container2>
    bool operator==(text<Encoding1, Container1> const& lhs, text<Encoding2, Container2> const& rhs) {
        return canonically_equivalent(lhs, rhs);
    }
    template <typename Encoding1, typename Container1, typename Encoding2, typename Container2>
    bool operator!=(text<Encoding1, Container1> const& lhs, text<Encoding2, Container2> const& rhs) {
        return !(lhs == rhs);
    }
    template <typename Encoding, typename Container>
    bool operator==(any_text const& lhs, text<Encoding, Container> const& rhs) {
        return canonically_equivalent(lhs, rhs);
    }
    template <typename Encoding, typename Container>
    bool operator!=(any_text const& lhs, text<Encoding, Container> const& rhs) {
        return !(lhs == rhs);
    }
    template <typename Encoding, typename Container>
    bool operator==(text<Encoding, Container> const& lhs, any_text const& rhs) {
        return canonically_equivalent(lhs, rhs);
    }
    template <typename Encoding, typename Container>
    bool operator!=(text<Encoding, Container> const& lhs, any_text const& rhs) {
        return !(lhs == rhs);
    }
    inline bool operator==(any_text const& lhs, any_text const& rhs) {
        return canonically_equivalent<any_text, any_text>(lhs, rhs);
    }
    inline bool operator!=(any_text const& lhs, any_text const& rhs) {
        return !(lhs == rhs);
    }
    
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
        
        template <typename Result, typename Validation>
        Result concat_impl(Validation) { return Result{}; }
        template <typename Result, typename Validation, typename Head, typename... Tail>
        Result concat_impl(Validation, Head&& head, Tail&&... tail) {
            Result result { std::forward<Head>(head) };
            result.append(concat_impl<Result>(Validation{}, std::forward<Tail>(tail)...));
            return result;
        }

        template <typename EncodingForm, typename Container,
                  typename CodePointSequences,
                  bool = wheels::is_deduced<EncodingForm>{},
                  bool = wheels::is_deduced<Container>{},
                  bool = detail::same_encoding<CodePointSequences>{}
                      && detail::same_container<CodePointSequences>{}>
        struct common_text {};

        template <typename EncodingForm, typename Container,
                  typename X, bool Y>
        struct common_text<EncodingForm, Container, X, false, false, Y>
        : wheels::identity<text<EncodingForm, Container>> {};
        
        template <typename EncodingForm, typename CodePointSequences>
        struct deduce_container
        : std::conditional<
            detail::same_container<CodePointSequences>{},
            detail::SameContainer<CodePointSequences>,
            DefaultContainer<EncodingForm>> {};
        template <typename EncodingForm, typename... CodePointSequences>
        using DeduceContainer = wheels::Invoke<deduce_container<EncodingForm, list<CodePointSequences...>>>;
        
        template <typename EncodingForm, typename Container,
                  typename CodePointSequences,
                  bool X>
        struct common_text<EncodingForm, Container, CodePointSequences, false, true, X>
        : wheels::identity<text<EncodingForm, DeduceContainer<EncodingForm, CodePointSequences>>> {};

        template <typename EncodingForm, typename Container, typename CodePointSequences>
        struct common_text<EncodingForm, Container, CodePointSequences, true, true, true>
        : wheels::identity<text<SameEncoding<CodePointSequences>, SameContainer<CodePointSequences>>> {};

        template <typename EncodingForm, typename Container, typename... CodePointSequences>
        using CommonText = wheels::Invoke<common_text<EncodingForm, Container, list<CodePointSequences...>>>;
    } // namespace detail

    // Concatenation
    
    template <typename EncodingForm = wheels::deduced, typename Container = wheels::deduced,
              typename Validation, typename... CodePointSequences,
              wheels::EnableIf<detail::is_validation_strategy<wheels::Unqualified<Validation>>>...,
              typename Text = detail::CommonText<EncodingForm, Container, CodePointSequences...>>
    Text concat(Validation&&, CodePointSequences&&... sequences) {
        return detail::concat_impl<Text>(wheels::Unqualified<Validation>{}, std::forward<CodePointSequences>(sequences)...);
    }
    
    template <typename EncodingForm, typename Container>
    text<EncodingForm, Container> concat() { return {}; }
    
    template <typename EncodingForm = wheels::deduced, typename Container = wheels::deduced,
              typename Head, typename... Tail,
              wheels::DisableIf<detail::is_validation_strategy<wheels::Unqualified<Head>>>...,
              typename Text = detail::CommonText<EncodingForm, Container, Head, Tail...>>
    Text concat(Head&& head, Tail&&... tail) {
        return concat<EncodingForm, Container>(default_validation, std::forward<Head>(head), std::forward<Tail>(tail)...);
    }
} // namespace ogonek
#endif // OGONEK_TEXT_HPP
