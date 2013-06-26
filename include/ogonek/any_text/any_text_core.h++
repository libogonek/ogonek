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

// any_text core

#ifndef OGONEK_ANY_TEXT_CORE_HPP
#define OGONEK_ANY_TEXT_CORE_HPP

#include <ogonek/text.h++>
#include <ogonek/types.h++>

#include <wheels/mem/unique.h++>

#include <boost/range/any_range.hpp>
#include <boost/iterator/iterator_categories.hpp>

#include <cstddef>
#include <memory>
#include <utility>

namespace ogonek {
    class any_text {
    public:
        using iterator = boost::any_range<code_point, boost::single_pass_traversal_tag, code_point, std::ptrdiff_t>::iterator;
        using const_iterator = iterator;

    private:
        class placeholder;
        using handle_type = wheels::mem::unique<placeholder>;

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
        : handle { wheels::mem::make_unique<holder<EncodingForm, Container>>(text) } {}
        template <typename EncodingForm, typename Container>
        any_text(text<EncodingForm, Container>&& text)
        : handle { wheels::mem::make_unique<holder<EncodingForm, Container>>(std::move(text)) } {}

        template <typename EncodingForm, typename Container>
        any_text& operator=(text<EncodingForm, Container> const& text) {
            handle = wheels::mem::make_unique<holder<EncodingForm, Container>>(text);
            return *this;
        }
        template <typename EncodingForm, typename Container>
        any_text& operator=(text<EncodingForm, Container>&& text) {
            handle = wheels::mem::make_unique<holder<EncodingForm, Container>>(std::move(text));
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

#endif // OGONEK_ANY_TEXT_CORE_HPP
