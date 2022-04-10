#pragma once

#include "data/cuda/CudaCollection.h"
#include "xyzid/XyzIdSoA.h"

// SoA with x, y, z, id fields in CUDA pinned host memory
using XyzIdCudaHostCollection = CudaHostCollection<XyzIdSoA>;

// SoA with x, y, z, id fields in CUDA device global memory
using XyzIdCudaDeviceCollection = CudaDeviceCollection<XyzIdSoA>;
