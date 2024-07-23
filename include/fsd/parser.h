// Copyright: Leon Freist, 2024
// Author   : Leon Freist
// License  : MIT

#pragma once

#include <fsd/constant.h>
#include <fsd/term.h>
#include <fsd/tokenizer.h>
#include <optional>

#include <expected>
#include <stack>
#include <string_view>

namespace fsd {

class Parser {
 public:
  explicit Parser(std::string_view input);

  std::expected<Expression, Error> parse();

 private:
  static Expression parse_number(const Token& token);
  std::optional<Error> handle_addition();
  std::optional<Error> handle_subtraction();
  std::optional<Error> handle_multiplication();
  std::optional<Error> handle_division();
  std::optional<Error> handle_literal(std::string_view literal);
  std::optional<Error> handle_right_paren();

  std::optional<Error> concatenate_next();

 private:
  enum class Operation_TP { ADD, SUB, MUL, DIV, POW, SIN, COS, TAN, ASIN, ACOS, ATAN, EXP, LPAR, RPAR };

  Tokenizer _tokenizer;
  std::stack<Operation_TP> _operator_stack;
  std::stack<Expression> _operand_stack;
};

std::expected<std::unique_ptr<Term_I>, Error> parse(std::string_view input);

}  // namespace fsd
