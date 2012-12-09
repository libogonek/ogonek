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

// Vector with small buffer optimization (primarily for decomposing iterators)

#ifndef OGONEK_DETAIL_SMALL_VECTOR_HPP
#define OGONEK_DETAIL_SMALL_VECTOR_HPP

#include <ogonek/detail/partial_array.h++>

#include <vector>
#include <utility>

namespace ogonek {
    namespace detail {
        template <typename T>
        struct small_vector {
            static_assert(std::is_pod<T>::value, "small_vector only works with PODs");
        public:
            small_vector() : is_small(false) { make_small(); }
            small_vector(small_vector const& that) : is_small(that.is_small) {
                if(is_small) {
                    make_small(that.storage.small);
                } else {
                    make_large(that.storage.large);
                }
            }
            small_vector(small_vector&& that) : is_small(that.is_small) {
                if(is_small) {
                    make_small(std::move(that.storage.small));
                    that.destroy_small();
                } else {
                    make_large(std::move(that.storage.large));
                    that.destroy_large();
                }
                that.make_small();
                that.is_small = true;
            }
            small_vector& operator=(small_vector that) {
                swap(that);
                return *this;
            }
            ~small_vector() {
                if(is_small) {
                    destroy_small();
                } else {
                    destroy_large();
                }
            }

            void swap(small_vector& that) {
                if(is_small && that.is_small) {
                    std::swap(storage.small, that.storage.small);
                } else if(!is_small && !that.is_small) {
                    std::swap(storage.large, that.storage.large);
                } else if(is_small) {
                    this->swap_small_large(that);
                } else {
                    that.swap_small_large(*this);
                }
                std::swap(is_small, that.is_small);
            }

            using value_type = T;
            using pointer = T*;
            using const_pointer = T const*;
            using reference = T&;
            using const_reference = T const&;
            using iterator = pointer;
            using const_iterator = const_pointer;

            iterator begin() {
                if(is_small) return &*storage.small.begin();
                else return &*storage.large.begin();
            }
            iterator end() {
                if(is_small) return &*storage.small.end();
                else return &*storage.large.end();
            }
            const_iterator begin() const {
                if(is_small) return &*storage.small.begin();
                else return &*storage.large.begin();
            }
            const_iterator end() const {
                if(is_small) return &*storage.small.end();
                else return &*storage.large.end();
            }

            reference operator[](std::size_t i) {
                if(is_small) return storage.small[i];
                else return storage.large[i];
            }
            const_reference operator[](std::size_t i) const {
                if(is_small) return storage.small[i];
                else return storage.large[i];
            }

        private:
            template <typename... Args>
            void make_small(Args&&... args) {
                ::new(&storage.small) small_storage(std::forward<Args>(args)...);
            }
            template <typename... Args>
            void make_large(Args&&... args) {
                ::new(&storage.large) large_storage(std::forward<Args>(args)...);
            }

            void destroy_small() {
                storage.small.~small_storage();
            }
            void destroy_large() {
                storage.large.~large_storage();
            }

            void swap_small_large(small_vector& that) {
                auto temp = std::move(that.storage.large);
                that.destroy_large();
                that.make_small(std::move(this->storage.small));
                this->destroy_small();
                this->make_large(std::move(temp));
            }

            bool is_small;

            static constexpr small_size = 4;
            using small_storage = partial_array<T, small_size>;
            using large_storage = std::vector<T>;
            union {
                small_storage small;
                large_storage large;
            } storage;
        };
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_DETAIL_SMALL_VECTOR_HPP

