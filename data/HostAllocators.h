#pragma once

#include <cassert>
#include <cstdint>
#include <cstdlib>

// host memory allocator
struct Allocator {
  static void *allocate(size_t size) {
    void *ptr = nullptr;
    ptr = malloc(size);
    assert(ptr);
    return ptr;
  }

  static void deallocate(void *ptr) { free(ptr); }
};

// aligned host memory allocator
template <size_t N>
struct AlignedAllocator {
  static void *allocate(size_t size) {
    void *ptr = nullptr;
    ptr = aligned_alloc(N, size);
    assert(ptr);
    assert(reinterpret_cast<uintptr_t>(ptr) % N == 0);
    return ptr;
  }

  static void deallocate(void *ptr) { free(ptr); }
};
