#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include <boost/core/demangle.hpp>

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
      std::cerr << "The requested collection with label '" << label << "' and type '"
                << boost::core::demangle(typeid(T).name()) << "' is not available" << std::endl;
      abort();
    }
    WrapperBase const& wb = *data_.at(label);
    if (typeid(T) == wb.type()) {
      auto const& w = dynamic_cast<Wrapper<T> const&>(wb);
      return w.get();
    } else {
      std::cerr << "The requested collection with label '" << label << "' and type '"
                << boost::core::demangle(typeid(T).name()) << "' is not available" << std::endl;
      std::cerr << "The collection with label '" << label << "' is of type '" << boost::core::demangle(wb.type().name())
                << "'" << std::endl;
      abort();
    }
  }

  void clear() { data_.clear(); }

private:
  std::unordered_map<std::string, std::unique_ptr<WrapperBase>> data_;
};
