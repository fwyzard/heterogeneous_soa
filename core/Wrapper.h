#pragma once

class WrapperBase {
public:
  WrapperBase() = default;
  virtual ~WrapperBase() = default;
};

template <typename T>
class Wrapper : public WrapperBase {
public:
  //Wrapper() = default;

  Wrapper(T const& product) : product_{product} {}

  Wrapper(T&& product) : product_{std::move(product)} {}

  //void set(T const& product) { product_ = product; }

  //void set(T&& product) { product_ = std::move(product); }

  T const& get() const { return product_; }

private:
  T product_;
};
