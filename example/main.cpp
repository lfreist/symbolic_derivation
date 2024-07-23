//
// Created by lfreist on 31/05/2024.
//

#include <fsd/constant.h>
#include <fsd/operations.h>
#include <fsd/parser.h>
#include <fsd/term.h>
#include <fsd/variable.h>

#include <iostream>
#include <string>

int main(int argc, char** argv) {
  /*
  const auto expr = fsd::constant(2) * fsd::pow(fsd::variable("x"), fsd::constant(3) + fsd::constant(1));

  std::map<std::string, double> map;
  map["x"] = 4;
  std::cout << expr->evaluate(map) << std::endl;
  std::cout << expr->to_str() << std::endl;
  std::cout << expr->derivative("x")->to_str() << std::endl;
  std::cout << expr->derivative("x")->evaluate(map) << std::endl;
   */

  std::string expression_str(argv[1]);

  std::map<std::string, double> map;
  map.insert({"x", 4});
  fsd::Parser parser(expression_str);
  auto result = parser.parse();
  if (result.has_value()) {
    std::cout << result.value()->to_str() << "\n"
              << " [x=4]        " << result.value()->evaluate(map) << "\n"
              << " diff x       " << result.value()->derivative("x")->to_str() << "\n"
              << " diff x [x=4] " << result.value()->derivative("x")->evaluate(map) << std::endl;
  } else {
    std::cerr << "Error parsing expression at position " << result.error().position << std::endl;
  }

  return 0;
}