// Copyright: Leon Freist, 2024
// Author   : Leon Freist
// License  : MIT

#include <fsd/constant.h>
#include <fsd/operations.h>
#include <fsd/variable.h>

#include <format>
#include <cmath>

namespace fsd {

template <>
std::unique_ptr<Term_I> BinaryOp<BinaryOperation_TP::ADD>::derivative(const std::string& var) const {
  return std::make_unique<BinaryOp<BinaryOperation_TP::ADD>>(_lhs->derivative(var), _rhs->derivative(var));
}

template <>
std::unique_ptr<Term_I> BinaryOp<BinaryOperation_TP::SUB>::derivative(const std::string& var) const {
  return std::make_unique<BinaryOp<BinaryOperation_TP::SUB>>(_lhs->derivative(var), _rhs->derivative(var));
}

template <>
std::unique_ptr<Term_I> BinaryOp<BinaryOperation_TP::MUL>::derivative(const std::string& var) const {
  return std::make_unique<BinaryOp<BinaryOperation_TP::ADD>>(
    std::make_unique<BinaryOp<BinaryOperation_TP::MUL>>(_lhs->derivative(var), _rhs->clone()),
    std::make_unique<BinaryOp<BinaryOperation_TP::MUL>>(_lhs->clone(), _rhs->derivative(var))
  );
}

template <>
std::unique_ptr<Term_I> BinaryOp<BinaryOperation_TP::DIV>::derivative(const std::string& var) const {
  return std::make_unique<BinaryOp<BinaryOperation_TP::DIV>>(
    std::make_unique<BinaryOp<BinaryOperation_TP::SUB>>(
      std::make_unique<BinaryOp<BinaryOperation_TP::MUL>>(_lhs->derivative(var), _rhs->clone()),
      std::make_unique<BinaryOp<BinaryOperation_TP::MUL>>(_lhs->clone(), _rhs->derivative(var))
    ),
    std::make_unique<BinaryOp<BinaryOperation_TP::MUL>>(
      _rhs->clone(),
      _rhs->clone()
    )
  );
}

template <>
std::unique_ptr<Term_I> BinaryOp<BinaryOperation_TP::POW>::derivative(const std::string& var) const {
  if (const auto* left = dynamic_cast<Variable*>(_lhs.get()); left == nullptr || left->get_name() != var) {
    return left->derivative(var);
  }
  return std::make_unique<BinaryOp<BinaryOperation_TP::MUL>>(
    _rhs->clone(),
    std::make_unique<BinaryOp<BinaryOperation_TP::POW>>(
      _lhs->clone(),
      std::make_unique<BinaryOp<BinaryOperation_TP::SUB>>(_rhs->clone(), constant(1))
    )
  );
}

template <>
double BinaryOp<BinaryOperation_TP::ADD>::evaluate(const std::map<std::string, double>& var) const {
  return _lhs->evaluate(var) + _rhs->evaluate(var);
}

template <>
double BinaryOp<BinaryOperation_TP::SUB>::evaluate(const std::map<std::string, double>& var) const {
  return _lhs->evaluate(var) - _rhs->evaluate(var);
}

template <>
double BinaryOp<BinaryOperation_TP::MUL>::evaluate(const std::map<std::string, double>& var) const {
  return _lhs->evaluate(var) * _rhs->evaluate(var);
}

template <>
double BinaryOp<BinaryOperation_TP::DIV>::evaluate(const std::map<std::string, double>& var) const {
  return _lhs->evaluate(var) / _rhs->evaluate(var);
}

template <>
double BinaryOp<BinaryOperation_TP::POW>::evaluate(const std::map<std::string, double>& var) const {
  return std::pow(_lhs->evaluate(var), _rhs->evaluate(var));
}

template <>
std::string BinaryOp<BinaryOperation_TP::ADD>::to_str() const {
  return std::format("({} + {})", _lhs->to_str(), _rhs->to_str());
}

template <>
std::string BinaryOp<BinaryOperation_TP::SUB>::to_str() const {
  return std::format("({} - {})", _lhs->to_str(), _rhs->to_str());
}

template <>
std::string BinaryOp<BinaryOperation_TP::MUL>::to_str() const {
  return std::format("({} * {})", _lhs->to_str(), _rhs->to_str());
}

template <>
std::string BinaryOp<BinaryOperation_TP::DIV>::to_str() const {
  return std::format("({} / {})", _lhs->to_str(), _rhs->to_str());
}

template <>
std::string BinaryOp<BinaryOperation_TP::POW>::to_str() const {
  return std::format("{}^({})", _lhs->to_str(), _rhs->to_str());
}

}  // namespace fsd