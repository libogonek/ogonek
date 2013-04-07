// Ogonek
//
// Written in 2013 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
//
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// A simplistic boost.optional replacement with moves

#ifndef OGONEK_DETAIL_CONTAINER_OPTIONAL_HPP
#define OGONEK_DETAIL_CONTAINER_OPTIONAL_HPP

#include <wheels/meta.h++>

#include <cassert>

namespace ogonek {
    namespace detail {
        struct none_t {} constexpr none = {};

        template <typename T>
        struct optional {
        public:
            optional() : present(false) {}

            optional(none_t) : present(false) {}

            optional(T const& t) {
                place(t);
            }
            optional(T&& t) {
                place(std::move(t));
            }

            optional(optional const& that) {
                if(that.present) place(*that);
                else present = false;
            }
            optional(optional&& that) {
                if(that.present) place(std::move(*that));
                else present = false;
            }

            optional& operator=(none_t) {
                if(present) destroy();
                return *this;
            }

            optional& operator=(optional const& that) {
                if(present && that.present) **this == *that;
                else if(present) destroy();
                else if(that.present) place(*that);
                else present = false;
                return *this;
            }
            optional& operator=(optional&& that) {
                if(present && that.present) **this == std::move(*that);
                else if(present) destroy();
                else if(that.present) place(std::move(*that));
                else present = false;
                return *this;
            }

            ~optional() {
                if(present) destroy();
            }

            T& operator*() { return get(); }
            T const& operator*() const { return get(); }

            T* operator->() { return &get(); }
            T const* operator->() const { return &get(); }

            explicit operator bool() const { return present; }

        private:
            using storage_type = wheels::StorageFor<T>;

            template <typename... Args>
            void place(Args&&... args) {
                assert(!present);
                ::new(&storage) T(std::forward<Args>(args)...);
                present = true;
            }
            void destroy() {
                assert(present);
                get().~T();
                present = false;
            }

            T& get() {
                return *static_cast<T*>(static_cast<void*>(&storage));
            }
            T const& get() const {
                return *static_cast<T const*>(static_cast<void const*>(&storage));
            }

            bool present;
            storage_type storage;
        };
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_DETAIL_CONTAINER_OPTIONAL_HPP
