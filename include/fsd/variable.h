// Copyright: Leon Freist, 2024
// Author   : Leon Freist
// License  : MIT

#pragma once

#include <fsd/term.h>

#include <memory>
#include <string>

#include <fsd/constant.h>

namespace fsd {

class Variable final : public Term_I {
public:
  explicit Variable(std::string name) : _name(std::move(name)) {}

  [[nodiscard]] std::unique_ptr<Term_I> derivative(const std::string& var) const override {
    if (_name == var) {
      return std::make_unique<Constant<int>>(1);
    }
    return std::make_unique<Constant<int>>(0);
  }

  [[nodiscard]] double evaluate(const std::map<std::string, double> &var) const override {
    if (var.contains(_name)) {
      return var.at(_name);
    }
    throw std::runtime_error("no value for variable " + _name);
  }

  [[nodiscard]] std::string to_str() const override {
    return _name;
  }

  [[nodiscard]] std::unique_ptr<Term_I> clone() const override {
    return std::make_unique<Variable>(_name);
  }

  [[nodiscard]] const std::string& get_name() const {
    return _name;
  }

private:
  std::string _name;
};

inline std::unique_ptr<Variable> variable(std::string name) {
  return std::make_unique<Variable>(std::move(name));
}

}  // namespace fsd
