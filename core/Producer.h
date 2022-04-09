#pragma once

#include <any>
#include <string>
#include <unordered_map>

#include "core/Configuration.h"
#include "core/Data.h"
#include "core/Module.h"

class Producer : public Module {
public:
  Producer(std::string const &label, Configuration const &config) : Module(label, config) {}

  virtual void produce(Data &data) = 0;

private:
  void run(Data &data) override { produce(data); }
};
