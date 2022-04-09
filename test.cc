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
#include "modules/cuda/XyzIdCudaConverter.h"
#include "modules/hip/XyzIdHipAnalyzer.h"
#include "modules/hip/XyzIdHipProducer.h"
#include "modules/hip/XyzIdHipTranscriber.h"
#include "modules/hip/XyzIdHipConverter.h"

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

  // XyzIdCudaConverter
  {
    Configuration config;
    config["source"] = std::string{"cudaTranscriber"};
    registerModule<XyzIdCudaConverter>(process, "cudaConverter", config);
  }

  // XyzIdHostAnalyzer for CUDA-based collections
  {
    Configuration config;
    config["source"] = std::string{"cudaConverter"};
    registerModule<XyzIdHostAnalyzer>(process, "hostAnalyzerFromCuda", config);
  }

  // XyzIdHipProducer
  {
    Configuration config;
    config["size"] = uint32_t{42};
    registerModule<XyzIdHipProducer>(process, "hipProducer", config);
  }

  // XyzIdHipTranscriber
  {
    Configuration config;
    config["source"] = std::string{"hipProducer"};
    registerModule<XyzIdHipTranscriber>(process, "hipTranscriber", config);
  }

  // XyzIdHipAnalyzer
  {
    Configuration config;
    config["source"] = std::string{"hipTranscriber"};
    registerModule<XyzIdHipAnalyzer>(process, "hipAnalyzer", config);
  }

  // XyzIdHipConverter
  {
    Configuration config;
    config["source"] = std::string{"hipTranscriber"};
    registerModule<XyzIdHipConverter>(process, "hipConverter", config);
  }

  // XyzIdHostAnalyzer for HIP-based collections
  {
    Configuration config;
    config["source"] = std::string{"hipConverter"};
    registerModule<XyzIdHostAnalyzer>(process, "hostAnalyzerFromHip", config);
  }

  process.run();

  return 0;
}
