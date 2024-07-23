// Copyright: Leon Freist, 2024
// Author   : Leon Freist
// License  : MIT

#pragma once

#include <fsd/term.h>
#include <fsd/constant.h>

#include <memory>
#include <string>

namespace fsd {

enum class BinaryOperation_TP {
  ADD,
  SUB,
  MUL,
  DIV,
  POW,
};

enum class UnaryOperation_TP {
  EXP,
  SQRT,
  SIN,
  COS,
  TAN,
  ASIN,
  ACOS,
  ATAN,
};

template <UnaryOperation_TP T>
class UnaryOp final : public Term_I {};

template <BinaryOperation_TP T>
class BinaryOp final : public Term_I {
public:
  BinaryOp(std::unique_ptr<Term_I> lhs, std::unique_ptr<Term_I> rhs) : _lhs(std::move(lhs)), _rhs(std::move(rhs)) {}

  [[nodiscard]] std::unique_ptr<Term_I> derivative(const std::string& var) const override;

  [[nodiscard]] double evaluate(const std::map<std::string, double>& var) const override;

  [[nodiscard]] std::string to_str() const override;

  [[nodiscard]] std::unique_ptr<Term_I> clone() const override {
    return std::make_unique<BinaryOp<T>>(_lhs->clone(), _rhs->clone());
  }

private:
  std::unique_ptr<Term_I> _lhs {nullptr};
  std::unique_ptr<Term_I> _rhs {nullptr};
};

inline std::unique_ptr<Term_I> operator+(std::unique_ptr<Term_I>& lhs, std::unique_ptr<Term_I>& rhs) {
  return std::make_unique<BinaryOp<BinaryOperation_TP::ADD>>(lhs->clone(), rhs->clone());
}

inline std::unique_ptr<Term_I> operator+(std::unique_ptr<Term_I>&& lhs, std::unique_ptr<Term_I>&& rhs) {
  return std::make_unique<BinaryOp<BinaryOperation_TP::ADD>>(std::move(lhs), std::move(rhs));
}

inline std::unique_ptr<Term_I> operator-(std::unique_ptr<Term_I> lhs, std::unique_ptr<Term_I> rhs) {
  return std::make_unique<BinaryOp<BinaryOperation_TP::SUB>>(std::move(lhs), std::move(rhs));
}

inline std::unique_ptr<Term_I> operator*(std::unique_ptr<Term_I> lhs, std::unique_ptr<Term_I> rhs) {
  return std::make_unique<BinaryOp<BinaryOperation_TP::MUL>>(std::move(lhs), std::move(rhs));
}

inline std::unique_ptr<Term_I> operator/(std::unique_ptr<Term_I> lhs, std::unique_ptr<Term_I> rhs) {
  return std::make_unique<BinaryOp<BinaryOperation_TP::DIV>>(std::move(lhs), std::move(rhs));
}

inline std::unique_ptr<Term_I> pow(std::unique_ptr<Term_I> lhs, std::unique_ptr<Term_I> rhs) {
  return std::make_unique<BinaryOp<BinaryOperation_TP::POW>>(std::move(lhs), std::move(rhs));
}

}  // namespace fsd