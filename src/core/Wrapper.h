#pragma once

#include <typeinfo>

class WrapperBase {
public:
  template <typename T>
  WrapperBase(T const&) : type_{&typeid(T)} {}

  virtual ~WrapperBase() = default;

  std::type_info const& type() const { return *type_; }

private:
  std::type_info const* type_;
};

template <typename T>
class Wrapper : public WrapperBase {
public:
  Wrapper(T const& product) : WrapperBase{product_}, product_{product} {}

  Wrapper(T&& product) : WrapperBase{product_}, product_{std::move(product)} {}

  T const& get() const { return product_; }

private:
  T product_;
};
