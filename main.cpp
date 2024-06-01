//
// Created by lfreist on 31/05/2024.
//

#include <fsd/constant.h>
#include <fsd/operations.h>
#include <fsd/variable.h>
#include <fsd/term.h>

#include <iostream>

int main(int argc, char** argv) {
  const auto expr = fsd::constant(2) * fsd::pow(fsd::variable("x"), fsd::constant(3) + fsd::constant(1));

  std::cout << expr->to_str() << std::endl;
  std::cout << expr->derivative("x")->to_str() << std::endl;

  return 0;
}