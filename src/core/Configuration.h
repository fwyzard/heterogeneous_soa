#pragma once

#include <any>
#include <iostream>
#include <string>
#include <unordered_map>

using Configuration = std::unordered_map<std::string, std::any>;

template <typename T>
T get(Configuration const& configuration, std::string const& parameter) {
  if (configuration.find(parameter) == configuration.end()) {
    std::cerr << "The requested configuration parameter of type " << typeid(T).name() << " and label '" << parameter
              << "' is not available" << std::endl;
    abort();
  }
  // add here an explicit check on the parameter type
  return std::any_cast<T>(configuration.at(parameter));
}
