// Copyright: Leon Freist, 2024
// Author   : Leon Freist
// License  : MIT

#include <fsd/tokenizer.h>
#include <gtest/gtest.h>

TEST(TokenizerTest, get_input) {
  const std::string input("a**2 + 24");
  fsd::Tokenizer tokenizer(input);
  EXPECT_EQ(tokenizer.get_input(), std::string_view(input));
}

TEST(TokenizerTest, get_current_position) {
  const std::string input("a**2 + 24");
  fsd::Tokenizer tokenizer(input);
  EXPECT_EQ(tokenizer.get_current_position(), std::string_view(input).begin());
  auto token = tokenizer.next_token();
  EXPECT_EQ(tokenizer.get_current_position(), std::string_view(input).begin() + 1);
}

TEST(TokenizerTest, next_token) {
  {
    const std::string input("a");
    fsd::Tokenizer tokenizer(input);
    auto token = tokenizer.next_token();
    EXPECT_TRUE(token.has_value());
    EXPECT_EQ(token.value(),
              fsd::Token(std::string_view(input.begin(), input.begin() + 1), fsd::TokenType_TP::LITERAL));
  }
  {
    const std::string input("1");
    fsd::Tokenizer tokenizer(input);
    auto token = tokenizer.next_token();
    EXPECT_TRUE(token.has_value());
    EXPECT_EQ(token.value(), fsd::Token(std::string_view(input.begin(), input.begin() + 1), fsd::TokenType_TP::NUMBER));
  }
  {
    const std::string input("1324");
    fsd::Tokenizer tokenizer(input);
    auto token = tokenizer.next_token();
    EXPECT_TRUE(token.has_value());
    EXPECT_EQ(token.value(), fsd::Token(std::string_view(input.begin(), input.begin() + 4), fsd::TokenType_TP::NUMBER));
  }
  {
    const std::string input("1.34");
    fsd::Tokenizer tokenizer(input);
    auto token = tokenizer.next_token();
    EXPECT_TRUE(token.has_value());
    EXPECT_EQ(token.value(), fsd::Token(std::string_view(input.begin(), input.begin() + 4), fsd::TokenType_TP::NUMBER));
  }
  {
    const std::string input("+");
    fsd::Tokenizer tokenizer(input);
    auto token = tokenizer.next_token();
    EXPECT_TRUE(token.has_value());
    EXPECT_EQ(token.value(), fsd::Token(std::string_view(input.begin(), input.begin() + 1), fsd::TokenType_TP::PLUS));
  }
  {
    const std::string input("-");
    fsd::Tokenizer tokenizer(input);
    auto token = tokenizer.next_token();
    EXPECT_TRUE(token.has_value());
    EXPECT_EQ(token.value(), fsd::Token(std::string_view(input.begin(), input.begin() + 1), fsd::TokenType_TP::MINUS));
  }
  {
    const std::string input("*");
    fsd::Tokenizer tokenizer(input);
    auto token = tokenizer.next_token();
    EXPECT_TRUE(token.has_value());
    EXPECT_EQ(token.value(), fsd::Token(std::string_view(input.begin(), input.begin() + 1), fsd::TokenType_TP::MUL));
  }
  {
    const std::string input("/");
    fsd::Tokenizer tokenizer(input);
    auto token = tokenizer.next_token();
    EXPECT_TRUE(token.has_value());
    EXPECT_EQ(token.value(), fsd::Token(std::string_view(input.begin(), input.begin() + 1), fsd::TokenType_TP::SLASH));
  }
  {
    const std::string input("**");
    fsd::Tokenizer tokenizer(input);
    auto token = tokenizer.next_token();
    EXPECT_TRUE(token.has_value());
    EXPECT_EQ(token.value(), fsd::Token(std::string_view(input.begin(), input.begin() + 2), fsd::TokenType_TP::POW));
  }
  {
    const std::string input(",");
    fsd::Tokenizer tokenizer(input);
    auto token = tokenizer.next_token();
    EXPECT_TRUE(token.has_value());
    EXPECT_EQ(token.value(), fsd::Token(std::string_view(input.begin(), input.begin() + 1), fsd::TokenType_TP::COMMA));
  }
  {
    const std::string input("(");
    fsd::Tokenizer tokenizer(input);
    auto token = tokenizer.next_token();
    EXPECT_TRUE(token.has_value());
    EXPECT_EQ(token.value(),
              fsd::Token(std::string_view(input.begin(), input.begin() + 1), fsd::TokenType_TP::LEFT_PAREN));
  }
  {
    const std::string input(")");
    fsd::Tokenizer tokenizer(input);
    auto token = tokenizer.next_token();
    EXPECT_TRUE(token.has_value());
    EXPECT_EQ(token.value(),
              fsd::Token(std::string_view(input.begin(), input.begin() + 1), fsd::TokenType_TP::RIGHT_PAREN));
  }
  {
    const std::string input("a12b");
    fsd::Tokenizer tokenizer(input);
    auto token = tokenizer.next_token();
    EXPECT_TRUE(token.has_value());
    EXPECT_EQ(token.value(),
              fsd::Token(std::string_view(input.begin(), input.begin() + 4), fsd::TokenType_TP::LITERAL));
  }
  {
    const std::string input("aaaa");
    fsd::Tokenizer tokenizer(input);
    auto token = tokenizer.next_token();
    EXPECT_TRUE(token.has_value());
    EXPECT_EQ(token.value(),
              fsd::Token(std::string_view(input.begin(), input.begin() + 4), fsd::TokenType_TP::LITERAL));
  }
  {
    const std::string input;
    fsd::Tokenizer tokenizer(input);
    auto token = tokenizer.next_token();
    EXPECT_TRUE(token.has_value());
    EXPECT_EQ(token.value(), fsd::Token(std::string_view(), fsd::TokenType_TP::END));
  }
  {
    const std::string input("&%$");
    fsd::Tokenizer tokenizer(input);
    auto token = tokenizer.next_token();
    EXPECT_FALSE(token.has_value());
    EXPECT_EQ(token.error(), fsd::Error(fsd::ErrorType::UNKNOWN_TOKEN, 0));
  }
  {
    const std::string input("a**21 * 5+3.65 $-asd/ x, s");
    fsd::Tokenizer tokenizer(input);

    auto token = tokenizer.next_token();
    EXPECT_TRUE(token.has_value());
    EXPECT_EQ(token.value(), fsd::Token(std::string_view(input.begin(), input.begin() + 1), fsd::TokenType_TP::LITERAL));
    token = tokenizer.next_token();
    EXPECT_TRUE(token.has_value());
    EXPECT_EQ(token.value(), fsd::Token(std::string_view(input.begin() + 1, input.begin() + 3), fsd::TokenType_TP::POW));
    token = tokenizer.next_token();
    EXPECT_TRUE(token.has_value());
    EXPECT_EQ(token.value(), fsd::Token(std::string_view(input.begin() + 3, input.begin() + 5), fsd::TokenType_TP::NUMBER));
    token = tokenizer.next_token();
    EXPECT_TRUE(token.has_value());
    EXPECT_EQ(token.value(), fsd::Token(std::string_view(input.begin() + 6, input.begin() + 7), fsd::TokenType_TP::MUL));
    token = tokenizer.next_token();
    EXPECT_TRUE(token.has_value());
    EXPECT_EQ(token.value(), fsd::Token(std::string_view(input.begin() + 8, input.begin() + 9), fsd::TokenType_TP::NUMBER));
    token = tokenizer.next_token();
    EXPECT_TRUE(token.has_value());
    EXPECT_EQ(token.value(), fsd::Token(std::string_view(input.begin() + 9, input.begin() + 10), fsd::TokenType_TP::PLUS));
    token = tokenizer.next_token();
    EXPECT_TRUE(token.has_value());
    EXPECT_EQ(token.value(), fsd::Token(std::string_view(input.begin() + 10, input.begin() + 14), fsd::TokenType_TP::NUMBER));
    token = tokenizer.next_token();
    EXPECT_FALSE(token.has_value());
    EXPECT_EQ(token.error(), fsd::Error(fsd::ErrorType::UNKNOWN_TOKEN, 15));
    token = tokenizer.next_token();
    EXPECT_TRUE(token.has_value());
    EXPECT_EQ(token.value(), fsd::Token(std::string_view(input.begin() + 13, input.begin() + 14), fsd::TokenType_TP::MINUS));
    token = tokenizer.next_token();
    EXPECT_TRUE(token.has_value());
    EXPECT_EQ(token.value(), fsd::Token(std::string_view(input.begin() + 14, input.begin() + 17), fsd::TokenType_TP::LITERAL));
    token = tokenizer.next_token();
    EXPECT_TRUE(token.has_value());
    EXPECT_EQ(token.value(), fsd::Token(std::string_view(), fsd::TokenType_TP::SLASH));
    token = tokenizer.next_token();
    EXPECT_TRUE(token.has_value());
    EXPECT_EQ(token.value(), fsd::Token(std::string_view(), fsd::TokenType_TP::LITERAL));
    token = tokenizer.next_token();
    EXPECT_TRUE(token.has_value());
    EXPECT_EQ(token.value(), fsd::Token(std::string_view(), fsd::TokenType_TP::COMMA));
    token = tokenizer.next_token();
    EXPECT_TRUE(token.has_value());
    EXPECT_EQ(token.value(), fsd::Token(std::string_view(), fsd::TokenType_TP::LITERAL));
    token = tokenizer.next_token();
    EXPECT_TRUE(token.has_value());
    EXPECT_EQ(token.value(), fsd::Token(std::string_view(), fsd::TokenType_TP::END));
    token = tokenizer.next_token();
    EXPECT_TRUE(token.has_value());
    EXPECT_EQ(token.value(), fsd::Token(std::string_view(), fsd::TokenType_TP::END));
  }
}