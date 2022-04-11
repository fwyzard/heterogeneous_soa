// The "Analyzer" makes sense only in the cpu memory space
#if defined(ALPAKA_ACC_CPU_B_SEQ_T_SEQ_ENABLED)

#include <string>

#include "core/Analyzer.h"
#include "core/Configuration.h"
#include "core/Data.h"
#include "core/Process.h"
#include "core/alpaka/Process.h"
#include "core/alpaka/config.h"
#include "modules/alpaka/XyzIdAlpakaAnalyzer.h"
#include "xyzid/alpaka/XyzIdAlpakaCollection.h"

namespace ALPAKA_ACCELERATOR_NAMESPACE {

  class XyzIdAlpakaAnalyzer : public Analyzer {
  public:
    XyzIdAlpakaAnalyzer(std::string const &label, Configuration const &config)
        : Analyzer{label, config}, source_{get<std::string>(config, "source")} {}

    void analyze(Data const &data) override {
      XyzIdAlpakaHostCollection const &product = data.get<XyzIdAlpakaHostCollection>(source_);

      for (size_t i = 0; i < product->size(); ++i) {
        //std::cout << source_ << "[" << i << "] = " << product->id(i) << std ::endl;
        assert(product->id(i) == static_cast<int32_t>(i));
      }
      std::cout << "XyzIdAlpakaAnalyzer:\n" << source_ << ".size() = " << product->size() << '\n' << std ::endl;
    }

  private:
    const std::string source_;
  };

}  // namespace ALPAKA_ACCELERATOR_NAMESPACE

DEFINE_ALPAKA_MODULE(XyzIdAlpakaAnalyzer);

#endif  // defined(ALPAKA_ACC_CPU_B_SEQ_T_SEQ_ENABLED)
