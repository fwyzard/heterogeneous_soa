#include <any>
#include <string>
#include <unordered_map>

#include "core/Configuration.h"
#include "core/Data.h"
#include "core/Producer.h"
#include "data/HostAllocators.h"
#include "modules/XyzIdPmrHostProducer.h"
#include "xyzid/XyzIdPmrCollection.h"

class XyzIdPmrHostProducer : public Producer {
public:
  XyzIdPmrHostProducer(std::string const &label, Configuration const &config)
      : Producer{label, config}, size_{get<uint32_t>(config, "size")} {}

  void produce(Data &data) override {
    XyzIdPmrCollection product{size_, AlignedAllocator<4096>{}};
    for (size_t i = 0; i < size_; ++i) {
      product->id(i) = i;
    }

    data.put(label(), std::move(product));
  }

private:
  const uint32_t size_;
};

DEFINE_MODULE(XyzIdPmrHostProducer);
