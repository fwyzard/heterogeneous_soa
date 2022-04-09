#include <cassert>
#include <cstring>
#include <string>

#include "core/Configuration.h"
#include "core/Data.h"
#include "core/Producer.h"
#include "modules/cuda/XyzIdCudaConverter.h"
#include "xyzid/XyzIdHostCollection.h"
#include "xyzid/cuda/XyzIdCudaCollection.h"

class XyzIdCudaConverter : public Producer {
public:
  XyzIdCudaConverter(std::string const &label, Configuration const &config)
      : Producer{label, config}, source_{get<std::string>(config, "source")} {}

  void produce(Data &data) override {
    XyzIdCudaHostCollection const &source = data.get<XyzIdCudaHostCollection>(source_);

    XyzIdHostCollection product{source->size()};
    std::memcpy(product->data(), source->data(), source->extent());

    data.put(label(), std::move(product));
  }

private:
  const std::string source_;
};

DEFINE_MODULE(XyzIdCudaConverter);
