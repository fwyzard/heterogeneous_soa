#include <any>
#include <string>
#include <unordered_map>

#include "core/Configuration.h"
#include "core/Data.h"
#include "core/Producer.h"
#include "modules/XyzIdHostProducer.h"
#include "xyzid/XyzIdHostCollection.h"

class XyzIdHostProducer : public Producer {
public:
  XyzIdHostProducer(std::string const &label, Configuration const &config)
      : Producer{label, config}, size_{get<uint32_t>(config, "size")} {}

  void produce(Data &data) override {
    XyzIdHostCollection product{size_};
    for (size_t i = 0; i < size_; ++i) {
      product->id(i) = i;
    }

    data.put(label(), std::move(product));
  }

private:
  const uint32_t size_;
};

DEFINE_MODULE(XyzIdHostProducer);
