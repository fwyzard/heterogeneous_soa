#include <list>
#include <memory>
#include <string>

#include "core/Configuration.h"
#include "core/Process.h"
#include "modules/XyzIdHostAnalyzer.h"
#include "modules/XyzIdHostProducer.h"
#include "modules/cuda/XyzIdCudaAnalyzer.h"
#include "modules/cuda/XyzIdCudaProducer.h"
#include "modules/cuda/XyzIdCudaTranscriber.h"

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

  // XyzIdCudaProducer
  {
    Configuration config;
    config["size"] = uint32_t{42};
    registerModule<XyzIdCudaProducer>(process, "cudaProducer", config);
  }

  // XyzIdCudaTranscriber
  {
    Configuration config;
    config["source"] = std::string{"cudaProducer"};
    registerModule<XyzIdCudaTranscriber>(process, "cudaTranscriber", config);
  }

  // XyzIdCudaAnalyzer
  {
    Configuration config;
    config["source"] = std::string{"cudaTranscriber"};
    registerModule<XyzIdCudaAnalyzer>(process, "cudaAnalyzer", config);
  }

  process.run();

  return 0;
}
