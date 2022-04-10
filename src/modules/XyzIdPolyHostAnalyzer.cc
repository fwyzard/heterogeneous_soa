#include <cassert>
#include <string>
#include <unordered_map>

#include "core/Analyzer.h"
#include "core/Configuration.h"
#include "core/Data.h"
#include "core/Process.h"
#include "modules/XyzIdPolyHostAnalyzer.h"
#include "xyzid/XyzIdPolyCollection.h"

class XyzIdPolyHostAnalyzer : public Analyzer {
public:
  XyzIdPolyHostAnalyzer(std::string const &label, Configuration const &config)
      : Analyzer{label, config}, source_{get<std::string>(config, "source")} {}

  void analyze(Data const &data) override {
    XyzIdPolyCollection const &product = data.get<XyzIdPolyCollection>(source_);

    for (size_t i = 0; i < product->size(); ++i) {
      //std::cout << source_ << "[" << i << "] = " << product->id(i) << std ::endl;
      assert(product->id(i) == static_cast<int32_t>(i));
    }
    std::cout << "XyzIdPolyHostAnalyzer:\n" << source_ << ".size() = " << product->size() << '\n' << std ::endl;
  }

private:
  const std::string source_;
};

DEFINE_MODULE(XyzIdPolyHostAnalyzer);
