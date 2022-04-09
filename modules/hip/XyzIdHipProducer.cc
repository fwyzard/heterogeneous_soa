#include <any>
#include <string>
#include <unordered_map>

#include "core/Configuration.h"
#include "core/Data.h"
#include "core/Producer.h"
#include "modules/hip/XyzIdHipProducer.h"
#include "xyzid/hip/XyzIdHipCollection.h"

class XyzIdHipProducer : public Producer {
public:
  XyzIdHipProducer(std::string const &label, Configuration const &config)
      : Producer{label, config}, size_{get<uint32_t>(config, "size")} {}

  void produce(Data &data) override {
    XyzIdHipDeviceCollection product{size_};
    for (size_t i = 0; i < size_; ++i) {
      int32_t value = static_cast<int32_t>(i);
      hipMemcpy(&product->id(i), &value, sizeof(int32_t), hipMemcpyHostToDevice);
    }
    data.put(label(), std::move(product));
  }

private:
  const uint32_t size_;
};

DEFINE_MODULE(XyzIdHipProducer);
