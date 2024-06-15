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

  std::map<std::string, double> map;
  map["x"] = 4;
  std::cout << expr->evaluate(map) << std::endl;
  std::cout << expr->to_str() << std::endl;
  std::cout << expr->derivative("x")->to_str() << std::endl;
  std::cout << expr->derivative("x")->evaluate(map) << std::endl;

  return 0;
}