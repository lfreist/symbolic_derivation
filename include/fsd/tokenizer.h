// Copyright: Leon Freist, 2024
// Author   : Leon Freist
// License  : MIT

#pragma once

#include <fsd/constant.h>
#include <fsd/variable.h>
#include <fsd/term.h>
#include <fsd/operations.h>

#include <string_view>
#include <expected>
#include <stack>

namespace fsd {

enum class ErrorType {
  UNKNOWN_TOKEN,
  MISSING_OPERAND,
  MISSING_OPERATOR,
  ITERATOR_END,
};

struct Error {
  ErrorType type;
  std::size_t position;

  auto operator<=>(const Error&) const = default;
};

enum class TokenType_TP {
  NUMBER,       // [0-9]+[\.]?[0-9]*
  LITERAL,      // [a-zA-Z]+([0-9]*[a-zA-Z]*)*
  PLUS,         // +
  MINUS,        // -
  MUL,          // *
  POW,          // **
  SLASH,        // /
  LEFT_PAREN,   // (
  RIGHT_PAREN,  // )
  COMMA,        // ,
  END
};

struct Token {
  std::string_view value;
  TokenType_TP type;

  auto operator<=>(const Token&) const = default;
};

class Tokenizer {
 public:
  class Iterator {
   public:
    using iterator_category = std::input_iterator_tag;
    using value_type = Token;
    using difference_type = std::ptrdiff_t;
    using pointer = Token*;
    using reference = Token&;

    Iterator(Tokenizer& tokenizer, bool end);

    std::expected<Token, Error> operator*();
    std::expected<Token, Error>* operator->();
    Iterator& operator++();
    bool operator!=(const Iterator& other) const;

   private:
    Tokenizer& _tokenizer;
    std::expected<Token, Error> _current_token;
  };

 public:
  explicit Tokenizer(std::string_view input);

  std::expected<Token, Error> next_token();

  Iterator begin();
  Iterator end();

  [[nodiscard]] std::string_view get_input() const;
  [[nodiscard]] std::string_view::const_iterator get_current_position() const;

 private:
  std::string_view _input;
  std::string_view::const_iterator _position;
};

}  // namespace tokenizer