#pragma once

#include "data/PmrCollection.h"
#include "xyzid/XyzIdSoA.h"

// SoA with x, y, z, id fields in aligned host memory
using XyzIdPmrCollection = PmrCollection<XyzIdSoA>;
