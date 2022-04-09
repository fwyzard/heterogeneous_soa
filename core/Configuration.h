#pragma once

#include <any>
#include <iostream>
#include <string>
#include <unordered_map>

using Configuration = std::unordered_map<std::string, std::any>;

template <typename T>
T get(Configuration const& configuration, std::string const& parameter) {
  // add checks here
  return std::any_cast<T>(configuration.at(parameter));
}
