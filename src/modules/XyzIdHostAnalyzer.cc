#include <cassert>
#include <string>
#include <unordered_map>

#include "core/Analyzer.h"
#include "core/Configuration.h"
#include "core/Data.h"
#include "core/Process.h"
#include "modules/XyzIdHostAnalyzer.h"
#include "xyzid/XyzIdHostCollection.h"

class XyzIdHostAnalyzer : public Analyzer {
public:
  XyzIdHostAnalyzer(std::string const &label, Configuration const &config)
      : Analyzer{label, config}, source_{get<std::string>(config, "source")} {}

  void analyze(Data const &data) override {
    XyzIdHostCollection const &product = data.get<XyzIdHostCollection>(source_);

    for (size_t i = 0; i < product->size(); ++i) {
      //std::cout << source_ << "[" << i << "] = " << product->id(i) << std ::endl;
      assert(product->id(i) == static_cast<int32_t>(i));
    }
    std::cout << "XyzIdHostAnalyzer:\n" << source_ << ".size() = " << product->size() << '\n' << std ::endl;
  }

private:
  const std::string source_;
};

DEFINE_MODULE(XyzIdHostAnalyzer);
