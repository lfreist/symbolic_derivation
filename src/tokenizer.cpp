// Copyright: Leon Freist, 2024
// Author   : Leon Freist
// License  : MIT

#include <fsd/operations.h>
#include <fsd/tokenizer.h>

#include <cctype>
#include <expected>

namespace fsd {

Tokenizer::Tokenizer(const std::string_view input) : _input(input), _position(_input.begin()) {}

std::expected<Token, Error> Tokenizer::next_token() {
  while (_position != _input.end() && std::isspace(*_position)) {
    _position++;
  }

  if (_position == _input.end()) {
    return Token("", TokenType_TP::END);
  }

  if (std::isdigit(*_position)) {
    // number[0] is digit
    const auto start = _position;
    _position++;
    while (_position != _input.end() && (std::isdigit(*_position) || *_position == '.')) {
      // number[1:] is digit or '.' (for floating point numbers)
      _position++;
    }
    return Token(std::string_view(start, _position), TokenType_TP::NUMBER);
  }
  if (std::isalpha(*_position)) {
    // variable[1] is alpha
    const auto start = _position;
    _position++;
    while (_position != _input.end() && std::isalnum(*_position)) {
      // variable[1:] are alpha or numeric
      _position++;
    }
    return Token(std::string_view(start, _position), TokenType_TP::LITERAL);
  }

  switch (*_position) {
    case '+':
      _position++;
      return Token(std::string_view(_position - 1, _position), TokenType_TP::PLUS);
    case '-':
      _position++;
      return Token(std::string_view(_position - 1, _position), TokenType_TP::MINUS);
    case '*':
      _position++;
      if (_position != _input.end() && *_position == '*') {
        // check if **
        Token token(std::string_view(_position - 1, _position + 1), TokenType_TP::POW);
        _position++;
        return token;
      }
      return Token(std::string_view(_position - 1, _position), TokenType_TP::MUL);
    case '/':
      _position++;
      return Token(std::string_view(_position - 1, _position), TokenType_TP::SLASH);
    case '(':
      _position++;
      return Token(std::string_view(_position - 1, _position), TokenType_TP::LEFT_PAREN);
    case ')':
      _position++;
      return Token(std::string_view(_position - 1, _position), TokenType_TP::RIGHT_PAREN);
    case ',':
      _position++;
      return Token(std::string_view(_position - 1, _position), TokenType_TP::COMMA);
    default:
      break;
  }
  return std::unexpected(Error(ErrorType::UNKNOWN_TOKEN, _position - _input.begin()));
}

Tokenizer::Iterator Tokenizer::end() { return {*this, true}; }

Tokenizer::Iterator Tokenizer::begin() { return {*this, false}; }

std::string_view Tokenizer::get_input() const { return _input; }

std::string_view::const_iterator Tokenizer::get_current_position() const { return _position; }

Tokenizer::Iterator::Iterator(Tokenizer& tokenizer, bool end) : _tokenizer(tokenizer) {
  if (!end) {
    _current_token = tokenizer.next_token();
  }
}

std::expected<Token, Error> Tokenizer::Iterator::operator*() { return _current_token; }

std::expected<Token, Error>* Tokenizer::Iterator::operator->() { return &_current_token; }

Tokenizer::Iterator& Tokenizer::Iterator::operator++() {
  _current_token = _tokenizer.next_token();
  return *this;
}

bool Tokenizer::Iterator::operator!=(const Iterator& other) const {
  return _current_token.has_value() && _current_token.value().type != TokenType_TP::END;
}

}  // namespace fsd