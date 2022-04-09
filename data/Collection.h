#pragma once

#include <cassert>
#include <cstdint>

// generic SoA-based product
template <typename T, typename Allocator>
class Collection {
public:
  Collection() : buffer_{nullptr}, layout_{} {}

  Collection(size_t elements) : buffer_{Allocator::allocate(T::compute_size(elements))}, layout_{elements, buffer_} {
    assert(reinterpret_cast<uintptr_t>(buffer_) % T::alignment == 0);
  }

  Collection(Collection const &) = delete;
  Collection &operator=(Collection const &) = delete;

  Collection(Collection &&other) : buffer_{other.buffer_}, layout_{std::move(other.layout_)} {
    other.buffer_ = nullptr;
  }

  Collection &operator=(Collection &&other) {
    layout_ = std::move(other.layout_);
    buffer_ = other.buffer_;
    other.buffer_ = nullptr;
    return *this;
  }

  ~Collection() { Allocator::deallocate(buffer_); }

  T &operator*() { return layout_; }

  T const &operator*() const { return layout_; }

  T *operator->() { return &layout_; }

  T const *operator->() const { return &layout_; }

private:
  void *buffer_;
  T layout_;
};
