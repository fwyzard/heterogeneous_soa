#include <cassert>
#include <string>
#include <unordered_map>

#include "core/Configuration.h"
#include "core/Data.h"
#include "core/Producer.h"
#include "data/cuda/CudaAllocators.h"
#include "modules/cuda/XyzIdPolyCudaTranscriber.h"
#include "xyzid/XyzIdPolyCollection.h"
#include "xyzid/cuda/XyzIdCudaCollection.h"

class XyzIdPolyCudaTranscriber : public Producer {
public:
  XyzIdPolyCudaTranscriber(std::string const &label, Configuration const &config)
      : Producer{label, config}, source_{get<std::string>(config, "source")} {}

  void produce(Data &data) override {
    XyzIdCudaDeviceCollection const &source = data.get<XyzIdCudaDeviceCollection>(source_);

    XyzIdPolyCollection product{source->size(), CudaHostAllocator{}};
    assert(cudaSuccess == cudaMemcpy(product->data(), source->data(), source->extent(), cudaMemcpyDeviceToHost));

    data.put(label(), std::move(product));
  }

private:
  const std::string source_;
};

DEFINE_MODULE(XyzIdPolyCudaTranscriber);
