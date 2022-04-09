#pragma once

#include "data/Collection.h"
#include "data/cuda/CudaAllocators.h"

// generic SoA-based product in CUDA pinned host memory
template <typename T>
using CudaHostCollection = Collection<T, CudaHostAllocator>;

// generic SoA-based product in CUDA device global memory
template <typename T>
using CudaDeviceCollection = Collection<T, CudaDeviceAllocator>;
