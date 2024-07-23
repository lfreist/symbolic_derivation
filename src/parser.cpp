// Copyright: Leon Freist, 2024
// Author   : Leon Freist
// License  : MIT

#include <fsd/parser.h>
#include <fsd/operations.h>

#include <charconv>

namespace fsd {

Parser::Parser(std::string_view input) : _tokenizer(input) {}

std::expected<Expression, Error> Parser::parse() {
  for (auto exp_token : _tokenizer) {
    if (!exp_token.has_value()) {
      return std::unexpected(exp_token.error());
    }
    Token token = exp_token.value();
    switch (token.type) {
      case TokenType_TP::NUMBER:
        _operand_stack.push(parse_number(token));
        break;
      case TokenType_TP::PLUS:
        handle_addition();
        break;
      case TokenType_TP::MINUS:
        handle_subtraction();
        break;
      case TokenType_TP::LITERAL:
        handle_literal(token.value);
        break;
      case TokenType_TP::RIGHT_PAREN:
        handle_right_paren();
        break;
      case TokenType_TP::END:
          break;
      case TokenType_TP::LEFT_PAREN:
        _operator_stack.push(Operation_TP::LPAR);
        break;
      case TokenType_TP::MUL:
        handle_multiplication();
        break;
      case TokenType_TP::POW:
        _operator_stack.push(Operation_TP::POW);
        break;
      case TokenType_TP::SLASH:
        handle_division();
        break;
      case TokenType_TP::COMMA:
        // comma is skipped, we "know" the number of arguments for supported functions
        break;
    }
  }
  while (true) {
    if (_operator_stack.empty()) {
      break;
    }
    if (concatenate_next().has_value()) {
      return std::unexpected(Error());
    }
  }
  if (_operand_stack.size() == 1) {
    auto expr = std::move(_operand_stack.top());
    _operand_stack.pop();
    return {std::move(expr)};
  }
  return std::unexpected(Error());
}

std::optional<Error> Parser::handle_addition() {
  std::optional<Error> result;
  if (!_operator_stack.empty() && (_operator_stack.top() == Operation_TP::MUL || _operator_stack.top() == Operation_TP::DIV || _operator_stack.top() == Operation_TP::POW)) {
    result = concatenate_next();
  }
  _operator_stack.push(Operation_TP::ADD);
  return result;
}

std::optional<Error> Parser::handle_subtraction() {
  std::optional<Error> result;
  if (!_operator_stack.empty() && (_operator_stack.top() == Operation_TP::MUL || _operator_stack.top() == Operation_TP::DIV || _operator_stack.top() == Operation_TP::POW)) {
    result = concatenate_next();
  }
  _operator_stack.push(Operation_TP::SUB);
  return result;
}

std::optional<Error> Parser::handle_multiplication() {
  std::optional<Error> result;
  if (!_operator_stack.empty() && _operator_stack.top() == Operation_TP::POW) {
    result = concatenate_next();
  }
  _operator_stack.push(Operation_TP::MUL);
  return result;
}

std::optional<Error> Parser::handle_division() {
  std::optional<Error> result;
  if (!_operator_stack.empty() && _operator_stack.top() == Operation_TP::POW) {
    result = concatenate_next();
  }
  _operator_stack.push(Operation_TP::DIV);
  return result;
}

std::optional<Error> Parser::handle_literal(std::string_view literal) {
  // TODO: how do i extract functions from variables?
  //       functions '(' as suffix
  //       variables have no '(' as suffix
  _operand_stack.push(variable({literal.data(), literal.size()}));
  return std::nullopt;
}

std::optional<Error> Parser::handle_right_paren() {
  while (true) {
    if (_operator_stack.empty()) {
      // return unexpected
      return Error(ErrorType::MISSING_OPERATOR);
    }
    Operation_TP op = _operator_stack.top();
    if (op == Operation_TP::LPAR) {
      // (...) detected
      _operator_stack.pop();
      return std::nullopt;
    }
    std::optional<Error> maybe = concatenate_next();
    if (maybe.has_value()) {
      return maybe;
    }
  }
}

std::optional<Error> Parser::concatenate_next() {
  Expression right = std::move(_operand_stack.top());
  _operand_stack.pop();
  Expression left = std::move(_operand_stack.top());
  _operand_stack.pop();
  Operation_TP op = _operator_stack.top();
  _operator_stack.pop();
  switch (op) {
    // binary functions
    case Operation_TP::ADD:
      _operand_stack.push(std::move(left) + std::move(right));
      break;
    case Operation_TP::SUB:
      _operand_stack.push(std::move(left) - std::move(right));
      break;
    case Operation_TP::MUL:
      _operand_stack.push(std::move(left) * std::move(right));
      break;
    case Operation_TP::DIV:
      _operand_stack.push(std::move(left) / std::move(right));
      break;
    case Operation_TP::POW:
      _operand_stack.push(fsd::pow(std::move(left), std::move(right)));
      break;
    // unary functions
    case Operation_TP::SIN:
    case Operation_TP::COS:
    case Operation_TP::TAN:
    case Operation_TP::ASIN:
    case Operation_TP::ACOS:
    case Operation_TP::ATAN:
    case Operation_TP::EXP:
    default:
      // not valid
      // TODO: return unexpected here
      break;
  }
  return std::nullopt;
}

Expression Parser::parse_number(const fsd::Token& token) {
  if (token.value.contains('.')) {
    // token is floating point
    double fp;
    std::from_chars(token.value.begin(), token.value.end(), fp);
    return constant(fp);
  } else {
    // token is int
    // TODO (safety): check how many bits are required here
    int integer;
    std::from_chars(token.value.begin(), token.value.end(), integer);
    return constant(integer);
  }
}

}  // namespace fsd
