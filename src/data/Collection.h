#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>

// generic SoA-based product
template <typename T, typename Allocator>
class Collection {
public:
  Collection() : buffer_{}, layout_{} {}

  Collection(size_t elements)
      : buffer_{static_cast<std::byte *>(Allocator::allocate(T::compute_size(elements))), Allocator::deallocate},
        layout_{elements, buffer_.get()} {
    assert(reinterpret_cast<uintptr_t>(buffer_.get()) % T::alignment == 0);
  }

  ~Collection() = default;

  // non-copyable
  Collection(Collection const &) = delete;
  Collection &operator=(Collection const &) = delete;

  // movable
  Collection(Collection &&other) = default;
  Collection &operator=(Collection &&other) = default;

  T &operator*() { return layout_; }

  T const &operator*() const { return layout_; }

  T *operator->() { return &layout_; }

  T const *operator->() const { return &layout_; }

private:
  std::unique_ptr<std::byte[], void (*)(void *)> buffer_;
  T layout_;
};
