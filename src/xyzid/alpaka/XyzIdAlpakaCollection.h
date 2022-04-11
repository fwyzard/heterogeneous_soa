#pragma once

#include "core/alpaka/config.h"
#include "data/alpaka/AlpakaCollection.h"
#include "xyzid/XyzIdSoA.h"

// SoA with x, y, z, id fields using Alpaka
template <typename TDev>
using XyzIdAlpakaCollection = AlpakaCollection<XyzIdSoA, TDev>;

// SoA with x, y, z, id fields in pinned host memory
using XyzIdAlpakaHostCollection = AlpakaHostCollection<XyzIdSoA>;

namespace ALPAKA_ACCELERATOR_NAMESPACE {

  // SoA with x, y, z, id fields in device global memory
  using XyzIdAlpakaDeviceCollection = AlpakaDeviceCollection<XyzIdSoA>;

}  // namespace ALPAKA_ACCELERATOR_NAMESPACE
