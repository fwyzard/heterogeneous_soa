#pragma once

#include "data/HostCollection.h"
#include "xyzid/XyzIdSoA.h"

// SoA with x, y, z, id fields in aligned host memory
using XyzIdHostCollection = HostCollection<XyzIdSoA>;
