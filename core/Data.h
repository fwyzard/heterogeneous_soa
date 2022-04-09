#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "core/Wrapper.h"

class Data {
public:
  template <typename T>
  void put(std::string const& label, T&& product) {
    data_[label] = std::make_unique<Wrapper<T>>(std::move(product));
  }

  template <typename T>
  T const& get(std::string const& label) const {
    WrapperBase const& wb = *data_.at(label);
    auto const& w = dynamic_cast<Wrapper<T> const&>(wb);
    return w.get();
  }

  void clear() { data_.clear(); }

private:
  std::unordered_map<std::string, std::unique_ptr<WrapperBase>> data_;
};
