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
#include <ogonek/error/error_handler.h++>
#include <ogonek/error/assume_valid.h++>
#include <ogonek/error/throw_error.h++>
#include <ogonek/encoding.h++>
#include <ogonek/encoding/iterator.h++>
#include <ogonek/encoding/utf16.h++>
#include <ogonek/encoding/utf32.h++>
#include <ogonek/encoding/encode.h++>
#include <ogonek/sequence/as_unicode.h++>

#include <taussig/interop.h++>
#include <taussig/as_sequence.h++>

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
            validated(Range const& range, ErrorHandler const& handler) {
                for(auto s = decode<EncodingForm>(range, handler);
                    !seq::empty(s);
                    seq::pop_front(s)) {}
                    // do nothing, just consume the input
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
        text(text<EncodingForm, Container1> const& that, ErrorHandler&&)
        : storage_(that.storage_.begin(), that.storage_.end()) {}

        //! Construct from a different text, different encoding, with validation
        template <typename EncodingForm1, typename Container1, typename ErrorHandler,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...>
        text(text<EncodingForm1, Container1> const& that, ErrorHandler&& handler)
        : storage_(seq::materialize<Container>(encode<EncodingForm>(that, std::forward<ErrorHandler>(handler)))) {}

        // -- sequences
        //! Construct from a code point sequence
        template <typename Source,
                  wheels::EnableIf<is_unicode_source<Source>>...>
        explicit text(Source&& source)
        : text(std::forward<Source>(source), default_error_handler) {}

        //! Construct from a code point sequence, with validation policy
        template <typename Source, typename ErrorHandler,
                  wheels::EnableIf<is_unicode_source<Source, ErrorHandler>>...,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...>
        text(Source&& source, ErrorHandler&& handler)
        : storage_(seq::materialize<Container>(encode<EncodingForm>(as_unicode(std::forward<Source>(source), std::forward<ErrorHandler>(handler))))) {}

        // -- storage
        //! Construct directly from a container
        explicit text(Container const& storage) : text(storage, default_error_handler) {}

        //! Construct directly from a container, with validation
        template <typename ErrorHandler,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...>
        text(Container const& storage, ErrorHandler&& handler)
        : storage_(seq::materialize<Container>(
                    encode<EncodingForm>(decode<EncodingForm>(storage, std::forward<ErrorHandler>(handler)))
                   )) {} // NOTE recoding is necessary because the data needs to be valid and may change
                         // NOTE once static wellformedness is properly in, the inefficiencies can be optimized away

        //! Construct directly from a container, moving
        explicit text(Container&& storage)
        : text(std::move(storage), default_error_handler) {}

        //! Construct directly from a container, with throwing validation, moving
        text(Container&& storage, throw_error_t)
        : detail::validated<EncodingForm>(storage, throw_error), storage_(std::move(storage)) {}

        //! Construct directly from a container, without validation, moving
        text(Container&& storage, assume_valid_t)
        : storage_(std::move(storage)) {}

        //! Construct directly from a container, with validation, (not) moving
        template <typename ErrorHandler,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...>
        text(Container&& storage, ErrorHandler&& handler)
        : text(storage, std::forward<ErrorHandler>(handler)) {}

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

        void assign(text const& that) { operator=(that); }
        template <typename ErrorHandler,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...>
        void assign(text const& that, ErrorHandler&&) { operator=(that); }

        void assign(text&& that) { operator=(std::move(that)); }
        template <typename ErrorHandler,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...>
        void assign(text&& that, ErrorHandler&&) { operator=(std::move(that)); }

        template <typename Container1, typename ErrorHandler,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...>
        void assign(text<EncodingForm, Container1> const& that, ErrorHandler&&) {
            storage_.assign(that.storage_.begin(), that.storage_.end());
        }

        template <typename Source,
                  wheels::EnableIf<is_unicode_source<Source>>...,
                  wheels::DisableIf<wheels::is_related<Source, text<EncodingForm, Container>>>...>
        void assign(Source&& source) {
            assign(std::forward<Source>(source), default_error_handler);
        }
        template <typename Source, typename ErrorHandler,
                  wheels::EnableIf<is_unicode_source<Source, ErrorHandler>>...,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...,
                  wheels::DisableIf<wheels::is_related<Source, text<EncodingForm, Container>>>...>
        void assign(Source&& source, ErrorHandler&& handler) {
            insert_code_units_ex(storage_.end(), encode<EncodingForm>(as_unicode(std::forward<Source>(source), std::forward<ErrorHandler>(handler)), std::forward<ErrorHandler>(handler)));
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
        template <typename Source,
                  wheels::EnableIf<is_unicode_source<Source>>...,
                  wheels::DisableIf<wheels::is_related<Source, text<EncodingForm, Container>>>...>
        void append(Source&& source) {
            append(std::forward<Source>(source), default_error_handler);
        }
        template <typename Source, typename ErrorHandler,
                  wheels::EnableIf<is_unicode_source<Source, ErrorHandler>>...,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...,
                  wheels::DisableIf<wheels::is_related<Source, text<EncodingForm, Container>>>...>
        void append(Source&& source, ErrorHandler&& handler) {
            insert_code_units_ex(storage_.end(), encode<EncodingForm>(as_unicode(std::forward<Source>(source), std::forward<ErrorHandler>(handler)), std::forward<ErrorHandler>(handler)));
        }

        // -- erasure
        template <typename Range>
        iterator erase(Range const& range) {
            // TODO make with sequence from text
            return erase(boost::begin(range), boost::end(range));
        }
        iterator erase(iterator from, iterator to) {
            // TODO k
            return {
                storage_.erase(detail::decoding_iterator_access::first(from), detail::decoding_iterator_access::first(to)),
                storage_.end()
            };
        }

        // -- inserting
        void insert(iterator at, text const& that) {
            // TODO Ooooh
            insert_code_units(detail::decoding_iterator_access::first(at), that.storage_);
        }
        template <typename ErrorHandler,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...>
        void insert(iterator at, text const& that, ErrorHandler&&) {
            // TODO Ooooh
            insert(at, that);
        }
        template <typename Source,
                  wheels::EnableIf<is_unicode_source<Source>>...,
                  wheels::DisableIf<wheels::is_related<Source, text<EncodingForm, Container>>>...>
        void insert(iterator at, Source&& source) {
            // TODO Ooooh
            insert(at, std::forward<Source>(source), default_error_handler);
        }
        template <typename Source, typename ErrorHandler,
                  wheels::EnableIf<is_unicode_source<Source, ErrorHandler>>...,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...,
                  wheels::DisableIf<wheels::is_related<Source, text<EncodingForm, Container>>>...>
        void insert(iterator at, Source&& source, ErrorHandler&& handler) {
            // TODO Ooooh
            insert_code_units_ex(detail::decoding_iterator_access::first(at),
                              encode<EncodingForm>(as_unicode(std::forward<Source>(source), std::forward<ErrorHandler>(handler)), std::forward<ErrorHandler>(handler)));
                              // TODO this line is repeated all over! REFACTOR
        }

        // -- replacing
        template <typename Range, typename Source,
                  wheels::EnableIf<is_unicode_source<Source>>...>
        void replace(Range const& range, Source&& source) {
            // TODO replace Range with sequence from text
            replace(range, std::forward<Source>(source), default_error_handler);
        }
        template <typename Range, typename Source, typename ErrorHandler,
                  wheels::EnableIf<is_unicode_source<Source, ErrorHandler>>...,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...>
        void replace(Range const& range, Source&& source, ErrorHandler&& handler) {
            // TODO replace Range with sequence from text
            replace(boost::begin(range), boost::end(range), std::forward<Source>(source), std::forward<ErrorHandler>(handler));
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
        template <typename Source,
                  wheels::EnableIf<is_unicode_source<Source>>...,
                  wheels::DisableIf<wheels::is_related<Source, text<EncodingForm, Container>>>...>
        void replace(iterator from, iterator to, Source&& source) {
            replace(from, to, std::forward<Source>(source), default_error_handler);
        }
        template <typename Source, typename ErrorHandler,
                  wheels::EnableIf<is_unicode_source<Source, ErrorHandler>>...,
                  wheels::EnableIf<is_error_handler<ErrorHandler>>...,
                  wheels::DisableIf<wheels::is_related<Source, text<EncodingForm, Container>>>...>
        void replace(iterator from, iterator to, Source&& source, ErrorHandler&& handler) {
            auto it = erase(from, to);
            insert_code_units_ex(detail::decoding_iterator_access::first(it),
                              encode<EncodingForm>(as_unicode(std::forward<Source>(source), std::forward<ErrorHandler>(handler)), std::forward<ErrorHandler>(handler)));
        }
    private:
        boost::iterator_range<char32_t const*> make_range(char32_t const* literal) {
            return boost::make_iterator_range(literal, literal + std::char_traits<char32_t>::length(literal));
        }
        boost::iterator_range<char16_t const*> make_range(char16_t const* literal) {
            return boost::make_iterator_range(literal, literal + std::char_traits<char16_t>::length(literal));
        }

        template <typename CodeUnitRange>
        void insert_code_units(detail::Iterator<Container> it, CodeUnitRange const& range) {
            static_assert(is_stateless<EncodingForm>(), "inserting with stateful encodings is not supported");
            storage_.insert(it, boost::begin(range), boost::end(range));
        }

        template <typename Source>
        void insert_code_units_ex(detail::Iterator<Container> it, Source&& source) {
            static_assert(is_stateless<EncodingForm>(), "inserting with stateful encodings is not supported");
            auto s = seq::as_sequence(std::forward<Source>(source));
            storage_.insert(it, seq::begin(s), seq::end(s));
        }

        template <typename, typename>
        friend class text;

        Container storage_;
    };
} // namespace ogonek

#endif // OGONEK_TEXT_CORE_HPP
