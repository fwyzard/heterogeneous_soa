#pragma once

#include "data/Collection.h"
#include "data/HostAllocators.h"

// generic SoA-based product in aligned host memory
template <typename T>
using HostCollection = Collection<T, AlignedAllocator<T::alignment>>;
