#pragma once

#include <cassert>
#include <cstdint>
#include <cstdlib>

#include <cuda_runtime.h>

// CUDA pinned host memory allocator
struct CudaHostAllocator {
  static void *allocate(size_t size) {
    void *ptr = nullptr;
    assert(cudaSuccess == cudaMallocHost(&ptr, size, cudaHostAllocMapped | cudaHostAllocPortable));
    assert(ptr);
    return ptr;
  }

  static void deallocate(void *ptr) { assert(cudaSuccess == cudaFreeHost(ptr)); }
};

// CUDA device global memory allocator
struct CudaDeviceAllocator {
  static void *allocate(size_t size) {
    void *ptr = nullptr;
    assert(cudaSuccess == cudaMalloc(&ptr, size));
    assert(ptr);
    return ptr;
  }

  static void deallocate(void *ptr) { assert(cudaSuccess == cudaFree(ptr)); }
};
