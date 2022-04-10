#include <cassert>
#include <cstring>
#include <string>

#include "core/Configuration.h"
#include "core/Data.h"
#include "core/Producer.h"
#include "modules/hip/XyzIdHipConverter.h"
#include "xyzid/XyzIdHostCollection.h"
#include "xyzid/hip/XyzIdHipCollection.h"

class XyzIdHipConverter : public Producer {
public:
  XyzIdHipConverter(std::string const &label, Configuration const &config)
      : Producer{label, config}, source_{get<std::string>(config, "source")} {}

  void produce(Data &data) override {
    XyzIdHipHostCollection const &source = data.get<XyzIdHipHostCollection>(source_);

    XyzIdHostCollection product{source->size()};
    std::memcpy(product->data(), source->data(), source->extent());

    data.put(label(), std::move(product));
  }

private:
  const std::string source_;
};

DEFINE_MODULE(XyzIdHipConverter);
