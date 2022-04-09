#pragma once

#include <cassert>
#include <cstdint>
#include <cstdlib>

#include <hip/hip_runtime.h>

// HIP pinned host memory allocator
struct HipHostAllocator {
  static void *allocate(size_t size) {
    void *ptr = nullptr;
    assert(hipSuccess == hipHostMalloc(&ptr, size, hipHostMallocMapped | hipHostMallocPortable));
    assert(ptr);
    return ptr;
  }

  static void deallocate(void *ptr) { assert(hipSuccess == hipHostFree(ptr)); }
};

// HIP device global memory allocator
struct HipDeviceAllocator {
  static void *allocate(size_t size) {
    void *ptr = nullptr;
    assert(hipSuccess == hipMalloc(&ptr, size));
    assert(ptr);
    return ptr;
  }

  static void deallocate(void *ptr) { assert(hipSuccess == hipFree(ptr)); }
};
