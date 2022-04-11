#include <string>

#include "core/Configuration.h"
#include "core/Data.h"
#include "core/Producer.h"
#include "core/alpaka/Process.h"
#include "core/alpaka/config.h"
#include "core/alpaka/host.h"
#include "core/alpaka/device.h"
#include "core/alpaka/queue.h"
#include "modules/alpaka/XyzIdAlpakaProducer.h"
#include "xyzid/alpaka/XyzIdAlpakaCollection.h"

namespace ALPAKA_ACCELERATOR_NAMESPACE {

  class XyzIdAlpakaProducer : public Producer {
  public:
    XyzIdAlpakaProducer(std::string const &label, Configuration const &config)
        : Producer{label, config}, size_{get<uint32_t>(config, "size")} {}

    void produce(Data &data) override {
      XyzIdAlpakaDeviceCollection product{size_, device};
      for (size_t i = 0; i < size_; ++i) {
        int32_t value = static_cast<int32_t>(i);
        auto host_view = alpaka::createView(host, &value, Vec1D{1});
        auto device_view = alpaka::createView(device, &product->id(i), Vec1D{1});
        alpaka::memcpy(queue, device_view, host_view);
      }
      data.put(label(), std::move(product));
    }

  private:
    const uint32_t size_;
  };

}  // namespace ALPAKA_ACCELERATOR_NAMESPACE

DEFINE_ALPAKA_MODULE(XyzIdAlpakaProducer);
