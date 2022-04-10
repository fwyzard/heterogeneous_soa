#pragma once

#include "data/PolyCollection.h"
#include "xyzid/XyzIdSoA.h"

// SoA with x, y, z, id fields in aligned host memory
using XyzIdPolyCollection = PolyCollection<XyzIdSoA>;
