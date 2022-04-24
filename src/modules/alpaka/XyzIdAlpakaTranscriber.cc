// The "Transcriber" makes sense only across different memory spaces
#if defined(ALPAKA_ACC_GPU_CUDA_ENABLED) or defined(ALPAKA_ACC_GPU_HIP_ENABLED)

#include <string>

#include "core/Configuration.h"
#include "core/Data.h"
#include "core/Producer.h"
#include "core/alpaka/Process.h"
#include "core/alpaka/config.h"
#include "core/alpaka/queue.h"
#include "core/alpaka/host.h"
#include "modules/alpaka/XyzIdAlpakaTranscriber.h"
#include "xyzid/alpaka/XyzIdAlpakaCollection.h"

namespace ALPAKA_ACCELERATOR_NAMESPACE {

  class XyzIdAlpakaTranscriber : public Producer {
  public:
    XyzIdAlpakaTranscriber(std::string const &label, Configuration const &config)
        : Producer{label, config}, source_{get<std::string>(config, "source")} {}

    void produce(Data &data) override {
      XyzIdAlpakaDeviceCollection const &source = data.get<XyzIdAlpakaDeviceCollection>(source_);

      XyzIdAlpakaHostCollection product{source->size(), host, device};
      alpaka::memcpy(queue, product.buffer(), source.buffer());

      // wait for any async work to complete
      alpaka::wait(queue);

      data.put(label(), std::move(product));
    }

  private:
    const std::string source_;
  };

}  // namespace ALPAKA_ACCELERATOR_NAMESPACE

DEFINE_ALPAKA_MODULE(XyzIdAlpakaTranscriber);

#endif  // defined(ALPAKA_ACC_GPU_CUDA_ENABLED) or defined(ALPAKA_ACC_GPU_HIP_ENABLED)
