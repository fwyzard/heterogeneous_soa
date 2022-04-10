#include <cassert>
#include <string>
#include <unordered_map>

#include "core/Configuration.h"
#include "core/Data.h"
#include "core/Producer.h"
#include "data/hip/HipAllocators.h"
#include "modules/hip/XyzIdPmrHipTranscriber.h"
#include "xyzid/XyzIdPmrCollection.h"
#include "xyzid/hip/XyzIdHipCollection.h"

class XyzIdPmrHipTranscriber : public Producer {
public:
  XyzIdPmrHipTranscriber(std::string const &label, Configuration const &config)
      : Producer{label, config}, source_{get<std::string>(config, "source")} {}

  void produce(Data &data) override {
    XyzIdHipDeviceCollection const &source = data.get<XyzIdHipDeviceCollection>(source_);

    XyzIdPmrCollection product{source->size(), HipHostAllocator{}};
    assert(hipSuccess == hipMemcpy(product->data(), source->data(), source->extent(), hipMemcpyDeviceToHost));

    data.put(label(), std::move(product));
  }

private:
  const std::string source_;
};

DEFINE_MODULE(XyzIdPmrHipTranscriber);
