#pragma once

#include <any>
#include <string>
#include <unordered_map>

#include "core/Configuration.h"
#include "core/Data.h"
#include "core/Module.h"

class Analyzer : public Module {
public:
  Analyzer(std::string const &label, Configuration const &config) : Module(label, config) {}

  virtual void analyze(Data const &data) = 0;

private:
  void run(Data &data) override { analyze(data); }
};
