#include <list>
#include <memory>
#include <string>

#include "core/Configuration.h"
#include "core/Process.h"
#include "modules/XyzIdHostAnalyzer.h"
#include "modules/XyzIdHostProducer.h"
#include "modules/alpaka/XyzIdAlpakaAnalyzer.h"
#include "modules/alpaka/XyzIdAlpakaTranscriber.h"
#include "modules/alpaka/XyzIdAlpakaProducer.h"

int main(void) {
  Process process;

  // XyzIdHostProducer
  {
    Configuration config;
    config["size"] = uint32_t{42};
    registerModule<XyzIdHostProducer>(process, "hostProducer", config);
  }

  // XyzIdHostAnalyzer
  {
    Configuration config;
    config["source"] = std::string{"hostProducer"};
    registerModule<XyzIdHostAnalyzer>(process, "hostAnalyzer", config);
  }

  // alpaka_serial_sync::XyzIdAlpakaProducer
  {
    Configuration config;
    config["size"] = uint32_t{42};
    registerModule<alpaka_serial_sync::XyzIdAlpakaProducer>(process, "serialAlpakaProducer", config);
  }

  // alpaka_serial_sync::XyzIdAlpakaAnalyzer
  {
    Configuration config;
    config["source"] = std::string{"serialAlpakaProducer"};
    registerModule<alpaka_serial_sync::XyzIdAlpakaAnalyzer>(process, "serialAlpakaAnalyzer", config);
  }

  // alpaka_cuda_async::XyzIdAlpakaProducer
  {
    Configuration config;
    config["size"] = uint32_t{42};
    registerModule<alpaka_cuda_async::XyzIdAlpakaProducer>(process, "cudaAlpakaProducer", config);
  }

  // alpaka_cuda_async::XyzIdAlpakaTranscriber
  {
    Configuration config;
    config["source"] = std::string{"cudaAlpakaProducer"};
    registerModule<alpaka_cuda_async::XyzIdAlpakaTranscriber>(process, "cudaAlpakaTranscriber", config);
  }

  // alpaka_serial_sync::XyzIdAlpakaAnalyzer for CUDA-based collections
  {
    Configuration config;
    config["source"] = std::string{"cudaAlpakaTranscriber"};
    registerModule<alpaka_serial_sync::XyzIdAlpakaAnalyzer>(process, "serialAlpakaAnalyzerFromCuda", config);
  }

  // alpaka_hip_async::XyzIdAlpakaProducer
  {
    Configuration config;
    config["size"] = uint32_t{42};
    registerModule<alpaka_hip_async::XyzIdAlpakaProducer>(process, "hipAlpakaProducer", config);
  }

  // alpaka_hip_async::XyzIdAlpakaTranscriber
  {
    Configuration config;
    config["source"] = std::string{"hipAlpakaProducer"};
    registerModule<alpaka_hip_async::XyzIdAlpakaTranscriber>(process, "hipAlpakaTranscriber", config);
  }

  // alpaka_serial_sync::XyzIdAlpakaAnalyzer for CUDA-based collections
  {
    Configuration config;
    config["source"] = std::string{"hipAlpakaTranscriber"};
    registerModule<alpaka_serial_sync::XyzIdAlpakaAnalyzer>(process, "serialAlpakaAnalyzerFromHip", config);
  }

  process.run();

  return 0;
}
