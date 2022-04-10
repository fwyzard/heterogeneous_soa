#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>

// generic SoA-based product
template <typename T>
class PolyCollection {
public:
  PolyCollection() : buffer_{}, layout_{} {}

  // Note: the `allocator` parameter is not used; its only purpose is to specify the _type_ of the Allocator.
  template <typename Allocator>
  PolyCollection(size_t elements, Allocator /* allocator */)
      : buffer_{static_cast<std::byte *>(Allocator::allocate(T::compute_size(elements))), Allocator::deallocate},
        layout_{elements, buffer_.get()} {
    assert(reinterpret_cast<uintptr_t>(buffer_.get()) % T::alignment == 0);
  }

  ~PolyCollection() = default;

  // non-copyable
  PolyCollection(PolyCollection const &) = delete;
  PolyCollection &operator=(PolyCollection const &) = delete;

  // movable
  PolyCollection(PolyCollection &&other) = default;
  PolyCollection &operator=(PolyCollection &&other) = default;

  T &operator*() { return layout_; }

  T const &operator*() const { return layout_; }

  T *operator->() { return &layout_; }

  T const *operator->() const { return &layout_; }

private:
  // Note: `void (*)(void *)` could be replaced by `std::function<void(void*)>` to support a stateful allocator
  std::unique_ptr<std::byte[], void (*)(void *)> buffer_;
  T layout_;
};
