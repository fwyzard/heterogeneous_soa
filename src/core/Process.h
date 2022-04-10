#pragma once

#include <memory>
#include <list>
#include <string>

#include "core/Configuration.h"
#include "core/Data.h"
#include "core/Module.h"

class Process {
public:
  Process() = default;

  void insert(std::unique_ptr<Module> module) { modules_.push_back(std::move(module)); }

  void run() const {
    Data data;
    for (std::unique_ptr<Module> const& module : modules_) {
      module->run(data);
    }
    data.clear();
  }

private:
  std::list<std::unique_ptr<Module>> modules_;
};

template <typename T>
void registerModule(Process& process, std::string const& label, Configuration const& config) {
  process.insert(std::make_unique<T>(label, config));
}

#define DEFINE_MODULE(TYPE) \
  template void registerModule<TYPE>(Process & process, std::string const& label, Configuration const& config)

#define DECLARE_MODULE(TYPE) \
  class TYPE;                \
  extern template void registerModule<TYPE>(Process & process, std::string const& label, Configuration const& config)
