#pragma once

#include "data/alpaka/AlpakaCollection.h"

namespace ALPAKA_ACCELERATOR_NAMESPACE {

  // generic SoA-based product in device memory
  template <typename T>
  using AlpakaDeviceCollection = AlpakaCollection<T, Device>;

}  // namespace ALPAKA_ACCELERATOR_NAMESPACE
