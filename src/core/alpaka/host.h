#pragma once

#include "core/alpaka/config.h"

// alpaka host device
inline const alpaka_common::DevHost host = alpaka::getDevByIdx<alpaka_common::PltfHost>(0u);
