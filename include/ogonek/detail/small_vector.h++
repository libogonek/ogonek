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

// Vector with small buffer optimization (primarily for decomposing iterators)

#ifndef OGONEK_DETAIL_SMALL_VECTOR_HPP
#define OGONEK_DETAIL_SMALL_VECTOR_HPP

#include <ogonek/detail/partial_array.h++>

#include <wheels/meta.h++>

#include <vector>
#include <type_traits>
#include <utility>

#include <cassert>
#include <cstddef>

namespace ogonek {
    namespace detail {
        template <typename T, std::size_t N>
        struct small_vector {
            static_assert(std::is_pod<T>::value, "small_vector only works with PODs");
        public:
            small_vector() : is_small(true) { place_small(); }
            small_vector(small_vector const& that) : is_small(that.is_small) {
                if(is_small) {
                    place_small(that.as_small());
                } else {
                    place_large(that.as_large());
                }
            }
            small_vector(small_vector&& that) : is_small(that.is_small) {
                if(is_small) {
                    place_small(std::move(that.as_small()));
                    that.destroy_small();
                } else {
                    place_large(std::move(that.as_large()));
                    that.destroy_large();
                }
                that.place_small();
                that.is_small = true;
            }
            small_vector& operator=(small_vector that) {
                swap(that);
                return *this;
            }
            ~small_vector() {
                if(is_small) destroy_small();
                else destroy_large();
            }

            template <typename RAIterator>
            small_vector(RAIterator first, RAIterator last)
            : is_small(last - first <= int(N)) {
                if(is_small) place_small(first, last);
                else place_large(first, last);
            }
            small_vector(std::initializer_list<T> list)
            : is_small(list.size() <= N) {
                if(is_small) place_small(list);
                else place_large(list);
            }

            void clear() {
                if(is_small) {
                    as_small().clear();
                } else {
                    destroy_large();
                    place_small();
                }
            }
            void push_back(T const& item) {
                if(is_small && as_small().size() == N) grow();

                if(is_small) as_small().push_back(item);
                else as_large().push_back(item);
            }

            void swap(small_vector& that) {
                if(is_small && that.is_small) {
                    std::swap(as_small(), that.as_small());
                } else if(!is_small && !that.is_small) {
                    std::swap(as_large(), that.as_large());
                } else if(is_small) {
                    this->swap_small_large(that);
                } else {
                    that.swap_small_large(*this);
                }
                std::swap(is_small, that.is_small);
            }

            std::size_t size() const {
                if(is_small) return as_small().size();
                else return as_large().size();
            }

            using value_type = T;
            using pointer = T*;
            using const_pointer = T const*;
            using reference = T&;
            using const_reference = T const&;
            using iterator = pointer;
            using const_iterator = const_pointer;

            iterator begin() {
                if(is_small) return &*as_small().begin();
                else return &*as_large().begin();
            }
            iterator end() {
                return begin() + size();
            }
            const_iterator begin() const {
                if(is_small) return &*as_small().begin();
                else return &*as_large().begin();
            }
            const_iterator end() const {
                return begin() + size();
            }

            reference operator[](std::size_t i) {
                if(is_small) return as_small()[i];
                else return as_large()[i];
            }
            const_reference operator[](std::size_t i) const {
                if(is_small) return as_small()[i];
                else return as_large()[i];
            }
            
            iterator erase(iterator it) {
                if(is_small) return get_pointer(as_small(), as_small().erase(get_iterator(as_small(), it)));
                else return get_pointer(as_large(), as_large().erase(get_iterator(as_large(), it)));
            }

        private:
            using small_storage = partial_array<T, N>;
            using large_storage = std::vector<T>;
            using storage_type = wheels::StorageFor<small_storage, large_storage>;
            
            template <typename Container>
            static auto get_iterator(Container& container, iterator it) -> decltype(container.begin()) {
                return container.begin() + std::distance(container.data(), it);
            }
            template <typename Container>
            static auto get_pointer(Container& container, typename Container::iterator it) -> decltype(container.data()) {
                return container.data() + std::distance(container.begin(), it);
            }

            template <typename... Args>
            void place_small(Args&&... args) {
                ::new(&storage) small_storage(std::forward<Args>(args)...);
            }
            template <typename... Args>
            void place_large(Args&&... args) {
                ::new(&storage) large_storage(std::forward<Args>(args)...);
            }

            void destroy_small() {
                as_small().~small_storage();
            }
            void destroy_large() {
                as_large().~large_storage();
            }

            small_storage& as_small() {
                return *static_cast<small_storage*>(static_cast<void*>(&storage));
            }
            small_storage const& as_small() const {
                return *static_cast<small_storage const*>(static_cast<void const*>(&storage));
            }
            large_storage& as_large() {
                return *static_cast<large_storage*>(static_cast<void*>(&storage));
            }
            large_storage const& as_large() const {
                return *static_cast<large_storage const*>(static_cast<void const*>(&storage));
            }

            void grow() {
                assert(is_small);
                auto copy(as_small());
                destroy_small();
                place_large(copy.begin(), copy.end());
                is_small = false;
            }

            void shrink() {
                assert(!is_small && as_large().size() <= N);
                small_storage copy(as_large().begin(), as_large().end());
                destroy_large();
                place_small(copy);
                is_small = true;
            }

            void swap_small_large(small_vector& that) {
                auto temp = std::move(that.as_large());
                that.destroy_large();
                that.place_small(std::move(this->as_small()));
                this->destroy_small();
                this->place_large(std::move(temp));
            }

            storage_type storage;
            bool is_small;
        };
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_DETAIL_SMALL_VECTOR_HPP
