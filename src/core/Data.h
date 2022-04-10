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
    if (data_.find(label) == data_.end()) {
      std::cerr << "The requested collection of type " << typeid(T).name() << " and label '" << label
                << "' is not available" << std::endl;
      abort();
    }
    WrapperBase const& wb = *data_.at(label);
    // add here an explicit check on the collection type
    auto const& w = dynamic_cast<Wrapper<T> const&>(wb);
    return w.get();
  }

  void clear() { data_.clear(); }

private:
  std::unordered_map<std::string, std::unique_ptr<WrapperBase>> data_;
};
