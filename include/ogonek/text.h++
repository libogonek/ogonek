// Ogonek
//
// Written in 2016 by Martinho Fernandes <ogonek@rmf.io>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Text type

#ifndef OGONEK_TEXT_HPP
#define OGONEK_TEXT_HPP

#include <utility>

namespace ogonek {
    template <typename Encoding, typename Storage>
    struct text {
    public:
        text() = default;
        text(Storage const& storage) : storage_(storage) {}
        text(Storage&& storage) : storage_(std::move(storage)) {}

        Storage const& storage() const { return storage_; }

    private:
        Storage storage_;
    };
} // namespace ogonek

#endif // OGONEK_TEXT_HPP

