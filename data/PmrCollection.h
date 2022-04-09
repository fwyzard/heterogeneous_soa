#pragma once

#include <cassert>
#include <cstdint>
#include <functional>

// generic SoA-based product
template <typename T>
class PmrCollection {
public:
  PmrCollection() : buffer_{nullptr}, layout_{}, deallocate_{} {}

  template <typename Allocator>
  PmrCollection(size_t elements, Allocator &&allocator)
      : buffer_{allocator.allocate(T::compute_size(elements))},
        layout_{elements, buffer_},
        deallocate_{[allocator](void *ptr) { allocator.deallocate(ptr); }} {
    assert(reinterpret_cast<uintptr_t>(buffer_) % T::alignment == 0);
  }

  ~PmrCollection() { deallocate_(buffer_); }

  T &operator*() { return layout_; }

  T const &operator*() const { return layout_; }

  T *operator->() { return &layout_; }

  T const *operator->() const { return &layout_; }

private:
  void *buffer_;
  T layout_;
  std::function<void(void *)> deallocate_;
};
