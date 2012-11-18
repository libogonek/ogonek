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

// Unicode text string

#ifndef OGONEK_TEXT_HPP
#define OGONEK_TEXT_HPP

#include "encoding/iterator.h++"
#include "traits.h++"
#include "types.h++"
#include "validation.h++"

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
    namespace detail {
        template <typename EncodingForm>
        struct validated {
            validated() = default;
            template <typename Range>
            validated(Range const& range) : validated(range, throw_validation_error) {}
            template <typename Range, typename ValidationCallback>
            validated(Range const& range, ValidationCallback&& callback) {
                for(auto&& _ : EncodingForm::decode(range, std::forward<ValidationCallback>(callback))) {
                    (void)_;
                    // TODO this is *wrong*
                    // do nothing, just consume the input
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
        using IteratorValueType = typename std::iterator_traits<Iterator>::value_type;
        template <typename Range>
        using RangeValueType = typename boost::range_value<Range>::type;

        template <typename Range, typename Value>
        struct is_range_of : std::is_same<RangeValueType<Range>, Value> {};
    } // namespace detail

    template <typename EncodingForm, typename Container = std::basic_string<CodeUnit<EncodingForm>>>
    struct basic_text : private detail::validated<EncodingForm> {
    private:
        static_assert(std::is_convertible<CodeUnit<EncodingForm>, detail::ValueType<Container>>::value,
                      "The container's value type should be convertible to the encoding form code units");
        static_assert(std::is_convertible<detail::ValueType<Container>, CodeUnit<EncodingForm>>::value,
                      "The encoding form code units should be convertible to the container's value type");

        struct direct {};

    public:
        //** Constructors **

        // -- basic
        //! Empty string
        basic_text() = default;

        // Copies and moves (explicit to prevent the range construction templates from being used)
        basic_text(basic_text const&) = default;
        basic_text(basic_text&&) = default;
        basic_text& operator=(basic_text const&) = default;
        basic_text& operator=(basic_text&&) = default;

        // -- codepoints
        //! Construct from a null-terminated codepoint string (intended for UTF-32 literals)
        basic_text(codepoint const* literal)
        : basic_text(literal, throw_validation_error) {}

        //! Construct from a null-terminated codepoint string, with validation callback
        template <typename ValidationPolicy>
        basic_text(codepoint const* literal, ValidationPolicy)
        : basic_text(boost::make_iterator_range(literal, literal + std::char_traits<codepoint>::length(literal)),
                     ValidationPolicy{}) {}

        //! Construct from a codepoint range
        template <typename CodepointRange>
        explicit basic_text(CodepointRange const& range)
        : basic_text(range, throw_validation_error) {}

        //! Construct from a codepoint range, with validation policy
        template <typename CodepointRange, typename ValidationPolicy>
        basic_text(CodepointRange const& range, ValidationPolicy)
        : basic_text(direct{}, EncodingForm::encode(range, ValidationPolicy{})) {
            static_assert(std::is_same<detail::RangeValueType<CodepointRange>, codepoint>::value,
                          "Can only construct text from a range of codepoints");
        }

        // -- storage
        //! Construct from an underlying container
        explicit basic_text(Container storage)
        : detail::validated<EncodingForm>(storage, throw_validation_error),
          storage_(std::move(storage)) {}

        //** Range **

        using iterator = decoding_iterator<EncodingForm, typename Container::iterator, skip_validation_t>;
        using const_iterator = decoding_iterator<EncodingForm, typename Container::const_iterator, skip_validation_t>;

        iterator begin() { return iterator { storage_.begin(), storage_.end() }; }
        iterator end() { return iterator { storage_.end(), storage_.end() }; }
        const_iterator begin() const { return const_iterator { storage_.begin(), storage_.end() }; }
        const_iterator end() const { return const_iterator { storage_.end(), storage_.end() }; }

        //** Interoperation **

        //! Move the underlying storage out
        Container move_storage() {
            return std::move(storage_);
        }
        //! View the underlying storage
        Container const& storage() const {
            return storage_;
        }

    private:
        template <typename Range>
        basic_text(direct, Range&& range)
        : storage_(boost::begin(range), boost::end(range)) {}

        Container storage_;
    };

    class utf8;
    class utf16;
    using posix_text = basic_text<utf8, std::string>;
    using windows_text = basic_text<utf16, std::wstring>;
#ifdef OGONEK_WINDOWS
    using native_text = windows_text;
#else
    using native_text = posix_text;
#endif

    class narrow;
    class wide;
    using narrow_text = basic_text<narrow, std::string>;
    using wide_text = basic_text<wide, std::wstring>;

    class any_text {
    public:
        using iterator = boost::any_range<codepoint, boost::single_pass_traversal_tag, codepoint, std::ptrdiff_t>::iterator;
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

        protected:
            placeholder(placeholder const&) = default;
            placeholder(placeholder&&) = default;
        };

        template <typename EncodingForm, typename Container>
        class holder : public placeholder {
        public:
            using text_type = basic_text<EncodingForm, Container>;

            holder(text_type const& text) : text(text) {}
            holder(text_type&& text) : text(std::move(text)) {}

            handle_type clone() override {
                return handle_type { new holder(*this) };
            }

            iterator begin() override { return iterator { text.begin() }; }
            iterator end() override { return iterator { text.end() }; }
            const_iterator begin() const override { return const_iterator { text.begin() }; }
            const_iterator end() const override { return const_iterator { text.end() }; }

            void* get() override { return &text; }
            void const* get() const override { return &text; }

        private:
            holder(holder const&) = default;
            holder(holder&&) = default;

            text_type text;
        };

    public:
        //** Constructors **
        any_text() {}
        any_text(any_text const& that)
        : handle { that.handle->clone() } {}
        any_text(any_text&&) = default;
        any_text& operator=(any_text const& that) {
            handle = handle_type { that.handle->clone() };
            return *this;
        }
        any_text& operator=(any_text&&) = default;

        template <typename EncodingForm, typename Container>
        any_text(basic_text<EncodingForm, Container> const& text)
        : handle { new holder<EncodingForm, Container>(text) } {}
        template <typename EncodingForm, typename Container>
        any_text(basic_text<EncodingForm, Container>&& text)
        : handle { new holder<EncodingForm, Container>(std::move(text)) } {}

        template <typename EncodingForm, typename Container>
        any_text& operator=(basic_text<EncodingForm, Container> const& text) {
            handle = handle_type { new holder<EncodingForm, Container>(text) };
            return *this;
        }
        template <typename EncodingForm, typename Container>
        any_text& operator=(basic_text<EncodingForm, Container>&& text) {
            handle = handle_type { new holder<EncodingForm, Container>(std::move(text)) };
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

    private:
        handle_type handle;
    };
} // namespace ogonek

#endif // OGONEK_TEXT_HPP
