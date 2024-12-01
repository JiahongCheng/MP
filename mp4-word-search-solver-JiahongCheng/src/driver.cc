#include <iostream>
#include <string>
#include <vector>

#include "WordSearchSolver.hpp"

int main() {
  std::vector<std::vector<char>> puzzle{{'o', 'o', 'o', 'o', 'o'},
                                        {'o', 'a', 'o', 'l', 'o'},
                                        {'l', 'a', 't', 'a', 'o'},
                                        {'l', 'a', 't', 'o', 'o'},
                                        {'h', 'e', 'l', 'l', 'o'}};
  WordSearchSolver wss(puzzle);
  std::cout << wss.FindWord("hello", CheckDirection::kHorizontal) << "first";
  std::cout << wss.FindWord("hello") << "second";
}