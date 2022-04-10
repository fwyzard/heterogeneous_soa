#include <cassert>
#include <string>
#include <unordered_map>

#include "core/Configuration.h"
#include "core/Data.h"
#include "core/Producer.h"
#include "modules/cuda/XyzIdCudaTranscriber.h"
#include "xyzid/cuda/XyzIdCudaCollection.h"

class XyzIdCudaTranscriber : public Producer {
public:
  XyzIdCudaTranscriber(std::string const &label, Configuration const &config)
      : Producer{label, config}, source_{get<std::string>(config, "source")} {}

  void produce(Data &data) override {
    XyzIdCudaDeviceCollection const &source = data.get<XyzIdCudaDeviceCollection>(source_);

    XyzIdCudaHostCollection product{source->size()};
    assert(cudaSuccess == cudaMemcpy(product->data(), source->data(), source->extent(), cudaMemcpyDeviceToHost));

    data.put(label(), std::move(product));
  }

private:
  const std::string source_;
};

DEFINE_MODULE(XyzIdCudaTranscriber);
