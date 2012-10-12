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

#include <wheels/meta.h++>

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
        static_assert(std::is_same<CodeUnit<EncodingForm>, detail::ValueType<Container>>::value,
                      "The container's value type should be the same as the encoding form code units");

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
        template <typename ValidationCallback>
        basic_text(codepoint const* literal, ValidationCallback&& callback)
        : basic_text(boost::make_iterator_range(literal, literal + std::char_traits<codepoint>::length(literal)),
                     std::forward<ValidationCallback>(callback)) {}

        //! Construct from a codepoint range
        template <typename CodepointRange>
        explicit basic_text(CodepointRange const& range)
        : basic_text(range, throw_validation_error) {}

        //! Construct from a codepoint range, with validation callback
        template <typename CodepointRange, typename ValidationCallback>
        basic_text(CodepointRange const& range, ValidationCallback&& callback)
        : basic_text(direct{}, EncodingForm::encode(range, std::forward<ValidationCallback>(callback))) {
            static_assert(std::is_same<detail::RangeValueType<CodepointRange>, codepoint>::value,
                          "Can only construct text from a range of codepoints");
        }

        // -- storage
        //! Construct from an underlying container
        explicit basic_text(Container storage)
        : detail::validated<EncodingForm>(storage, throw_validation_error),
          storage_(std::move(storage)) {}

        //** Range **

        using iterator = decoding_iterator<EncodingForm, typename Container::iterator, decltype(skip_validation)>;
        using const_iterator = decoding_iterator<EncodingForm, typename Container::const_iterator, decltype(skip_validation)>;

        iterator begin() { return iterator { storage_.begin(), storage_.end(), skip_validation }; }
        iterator end() { return iterator { storage_.end(), storage_.end(), skip_validation }; }
        const_iterator begin() const { return const_iterator { storage_.begin(), storage_.end(), skip_validation }; }
        const_iterator end() const { return const_iterator { storage_.end(), storage_.end(), skip_validation }; }

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

    class any_text {
    public:
        using iterator = boost::any_range<codepoint, boost::forward_traversal_tag, codepoint, std::ptrdiff_t>::iterator;
        using const_iterator = iterator;

    private:
        class placeholder;
        using handle_type = std::unique_ptr<placeholder>;

        class placeholder {
        public:
            placeholder() = default;
            placeholder(placeholder const&) = delete;
            placeholder(placeholder&&) = delete;
            virtual ~placeholder() = default;

            virtual handle_type clone() = 0;

            virtual iterator begin() = 0;
            virtual const_iterator end() = 0;
            virtual iterator begin() const = 0;
            virtual const_iterator end() const = 0;
        };

        template <typename EncodingForm, typename Container>
        class holder : public placeholder {
        public:
            using text_type = basic_text<EncodingForm, Container>;
            holder(text_type const& text) : text(text) {}
            holder(text_type&& text) : text(std::move(text)) {}

            handle_type clone() {
                return handle_type { new holder(*this) };
            }

            iterator begin() { return text.begin(); }
            const_iterator end() { return text.end(); }
            iterator begin() const { return text.begin(); }
            const_iterator end() const { return text.end(); }

        private:
            text_type text;
        };

    public:
        //** Constructors **
        any_text() {}
        any_text(any_text const& that)
        : handle { that.handle->clone() } {}
        any_text(any_text&& that) = default;
        any_text& operator=(any_text const& that) {
            handle = handle_type { that.handle->clone() };
            return *this;
        }
        any_text& operator=(any_text&& that) = default;

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

        /*
        //! Move the underlying storage out
        template <typename Container>
        Container move_storage();
        //! View the underlying storage
        template <typename Container>
        Container const& storage() const;
        */

    private:
        handle_type handle;
    };
} // namespace ogonek

#endif // OGONEK_TEXT_HPP
#if 0
#endif
