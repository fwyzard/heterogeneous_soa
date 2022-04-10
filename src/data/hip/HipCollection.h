#pragma once

#include "data/Collection.h"
#include "data/hip/HipAllocators.h"

// generic SoA-based product in HIP pinned host memory
template <typename T>
using HipHostCollection = Collection<T, HipHostAllocator>;

// generic SoA-based product in HIP device global memory
template <typename T>
using HipDeviceCollection = Collection<T, HipDeviceAllocator>;
