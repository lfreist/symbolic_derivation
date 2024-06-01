// Copyright: Leon Freist, 2024
// Author   : Leon Freist
// License  : MIT

#pragma once

#include <fsd/concepts.h>
#include <fsd/term.h>

#include <memory>
#include <string>

namespace fsd {

template <Numeric T>
class Constant final : public Term_I {
public:
  explicit Constant(T value) : _value(value) {}

  [[nodiscard]] std::unique_ptr<Term_I> derivative(const std::string& var) const override {
    return std::make_unique<Constant<int>>(0);
  }

  [[nodiscard]] std::unique_ptr<Term_I> evaluate(const std::map<std::string, double> &var) const override {
    return std::make_unique<Constant>(0);
  }

  [[nodiscard]] std::string to_str() const override {
    return std::to_string(_value);
  }

  [[nodiscard]] std::unique_ptr<Term_I> clone() const override {
    return std::make_unique<Constant<T>>(_value);
  }

private:
  T _value;
};

template <Numeric T>
inline std::unique_ptr<Constant<T>> constant(T value) {
  return std::make_unique<Constant<T>>(value);
}

}  // namespace fsd
