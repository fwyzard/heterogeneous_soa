#include <any>
#include <string>
#include <unordered_map>

#include "core/Configuration.h"
#include "core/Data.h"
#include "core/Producer.h"
#include "modules/hip/XyzIdHipTranscriber.h"
#include "xyzid/hip/XyzIdHipCollection.h"

class XyzIdHipTranscriber : public Producer {
public:
  XyzIdHipTranscriber(std::string const &label, Configuration const &config)
      : Producer{label, config}, source_{get<std::string>(config, "source")} {}

  void produce(Data &data) override {
    XyzIdHipDeviceCollection const &source = data.get<XyzIdHipDeviceCollection>(source_);

    XyzIdHipHostCollection product{source->size()};
    hipMemcpy(product->data(), source->data(), source->extent(), hipMemcpyDeviceToHost);

    data.put(label(), std::move(product));
  }

private:
  const std::string source_;
};

DEFINE_MODULE(XyzIdHipTranscriber);
