// Copyright: Leon Freist, 2024
// Author   : Leon Freist
// License  : MIT

#pragma once

#include <memory>
#include <string>
#include <map>

namespace fsd {

class Term_I {
 public:
  virtual ~Term_I() = default;
  [[nodiscard]] virtual std::unique_ptr<Term_I> derivative(const std::string& var) const = 0;
  [[nodiscard]] virtual double evaluate(const std::map<std::string, double>& var) const = 0;
  [[nodiscard]] virtual std::string to_str() const = 0;

  [[nodiscard]] virtual std::unique_ptr<Term_I> clone() const = 0;
};

typedef std::unique_ptr<Term_I> Expression;

}  // namespace fsd