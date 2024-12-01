#ifndef WORDSEARCHSOLVER_HPP
#define WORDSEARCHSOLVER_HPP

#include <cstddef>
#include <string>
#include <vector>

#include "WordLocation.hpp"

enum class CheckDirection { kHorizontal, kVertical, kLeftDiag, kRightDiag };

class WordSearchSolver {
public:
  WordSearchSolver(const std::vector<std::vector<char>>& puzzle);
  WordLocation FindWord(const std::string& word);
  WordLocation FindWord(const std::string& word, CheckDirection direction);

private:
  bool LocationInBounds(size_t row, size_t col) const;
  std::vector<std::vector<char>> puzzle_;
  size_t puzzle_height_;
  size_t puzzle_width_;

  WordLocation CheckHorizontal(const std::string& word, size_t row, size_t col);
  WordLocation CheckVertical(const std::string& word, size_t row, size_t col);
  WordLocation CheckRightDiag(const std::string& word, size_t row, size_t col);
  WordLocation CheckLeftDiag(const std::string& word, size_t row, size_t col);
  
};

#endif