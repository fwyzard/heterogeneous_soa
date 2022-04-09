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

  ~PmrCollection() { if (buffer_ and deallocate_) deallocate_(buffer_); }

  // non-copyable
  PmrCollection(PmrCollection const &) = delete;
  PmrCollection &operator=(PmrCollection const &) = delete;

  // movable
  PmrCollection(PmrCollection &&other) : buffer_{other.buffer_}, layout_{std::move(other.layout_)}, deallocate_{std::move(other.deallocate_)} {
    other.buffer_ = nullptr;
    other.deallocate_ = std::function<void(void *)>{};
  }

  PmrCollection &operator=(PmrCollection &&other) {
    layout_ = std::move(other.layout_);
    buffer_ = other.buffer_;
    deallocate_ = std::move(other.deallocate_);
    other.buffer_ = nullptr;
    other.deallocate_ = std::function<void(void *)>{};
    return *this;
  }

  T &operator*() { return layout_; }

  T const &operator*() const { return layout_; }

  T *operator->() { return &layout_; }

  T const *operator->() const { return &layout_; }

private:
  void *buffer_;
  T layout_;
  std::function<void(void *)> deallocate_;
};
