#pragma once

#include "core/Process.h"
#include "core/alpaka/config.h"

#define DEFINE_ALPAKA_MODULE(TYPE)                                  \
  template void registerModule<ALPAKA_ACCELERATOR_NAMESPACE::TYPE>( \
      Process & process, std::string const& label, Configuration const& config)

// This should be made dependent on the backends available at compile time

#define DECLARE_ALPAKA_MODULE(TYPE)                                              \
  namespace alpaka_serial_sync {                                                 \
    class TYPE;                                                                  \
  }                                                                              \
  extern template void registerModule<alpaka_serial_sync::TYPE>(                 \
      Process & process, std::string const& label, Configuration const& config); \
                                                                                 \
  namespace alpaka_hip_async {                                                   \
    class TYPE;                                                                  \
  }                                                                              \
  extern template void registerModule<alpaka_hip_async::TYPE>(                   \
      Process & process, std::string const& label, Configuration const& config); \
                                                                                 \
  namespace alpaka_cuda_async {                                                  \
    class TYPE;                                                                  \
  }                                                                              \
  extern template void registerModule<alpaka_cuda_async::TYPE>(                  \
      Process & process, std::string const& label, Configuration const& config)
