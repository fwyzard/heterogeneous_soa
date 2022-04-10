#include <cassert>
#include <string>
#include <unordered_map>

#include "core/Configuration.h"
#include "core/Data.h"
#include "core/Producer.h"
#include "modules/cuda/XyzIdCudaProducer.h"
#include "xyzid/cuda/XyzIdCudaCollection.h"

class XyzIdCudaProducer : public Producer {
public:
  XyzIdCudaProducer(std::string const &label, Configuration const &config)
      : Producer{label, config}, size_{get<uint32_t>(config, "size")} {}

  void produce(Data &data) override {
    XyzIdCudaDeviceCollection product{size_};
    for (size_t i = 0; i < size_; ++i) {
      int32_t value = static_cast<int32_t>(i);
      assert(cudaSuccess == cudaMemcpy(&product->id(i), &value, sizeof(int32_t), cudaMemcpyHostToDevice));
    }
    data.put(label(), std::move(product));
  }

private:
  const uint32_t size_;
};

DEFINE_MODULE(XyzIdCudaProducer);
