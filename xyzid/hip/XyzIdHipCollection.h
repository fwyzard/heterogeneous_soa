#pragma once

#include "data/hip/HipCollection.h"
#include "xyzid/XyzIdSoA.h"

// SoA with x, y, z, id fields in HIP pinned host memory
using XyzIdHipHostCollection = HipHostCollection<XyzIdSoA>;

// SoA with x, y, z, id fields in HIP device global memory
using XyzIdHipDeviceCollection = HipDeviceCollection<XyzIdSoA>;
