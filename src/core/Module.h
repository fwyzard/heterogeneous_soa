#pragma once

#include <any>
#include <string>
#include <unordered_map>

#include "core/Data.h"
#include "core/Configuration.h"

class Module {
public:
  Module(std::string const &label, Configuration const &) : label_(label) {}

  virtual ~Module() = default;

  virtual void run(Data &data) = 0;

  std::string const &label() { return label_; }

private:
  const std::string label_;
};
