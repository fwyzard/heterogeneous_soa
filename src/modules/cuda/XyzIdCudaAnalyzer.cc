#include <cassert>
#include <string>
#include <unordered_map>

#include "core/Analyzer.h"
#include "core/Configuration.h"
#include "core/Data.h"
#include "core/Process.h"
#include "modules/cuda/XyzIdCudaAnalyzer.h"
#include "xyzid/cuda/XyzIdCudaCollection.h"

class XyzIdCudaAnalyzer : public Analyzer {
public:
  XyzIdCudaAnalyzer(std::string const &label, Configuration const &config)
      : Analyzer{label, config}, source_{get<std::string>(config, "source")} {}

  void analyze(Data const &data) override {
    XyzIdCudaHostCollection const &product = data.get<XyzIdCudaHostCollection>(source_);
    assert(cudaSuccess == cudaDeviceSynchronize());

    for (size_t i = 0; i < product->size(); ++i) {
      //std::cout << source_ << "[" << i << "] = " << product->id(i) << std ::endl;
      assert(product->id(i) == static_cast<int32_t>(i));
    }
    std::cout << "XyzIdCudaAnalyzer:\n" << source_ << ".size() = " << product->size() << '\n' << std ::endl;
  }

private:
  const std::string source_;
};

DEFINE_MODULE(XyzIdCudaAnalyzer);
