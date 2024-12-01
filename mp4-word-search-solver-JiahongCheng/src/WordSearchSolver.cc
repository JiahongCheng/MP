#include "WordSearchSolver.hpp"

bool WordSearchSolver::LocationInBounds(size_t row, size_t col) const {
  return ((row < puzzle_height_) && (col < puzzle_width_));
}
/*
public:
  WordSearchSolver(const std::vector<std::vector<char>>& puzzle);
  WordLocation FindWord(const std::string& word);
  WordLocation FindWord(const std::string& word, CheckDirection direction);

private:
  bool LocationInBounds(size_t row, size_t col) const;
  std::vector<std::vector<char>> puzzle_;
  size_t puzzle_height_;
  size_t puzzle_width_;
};
*/
 
WordSearchSolver::WordSearchSolver(const std::vector<std::vector<char>>& puzzle):
  puzzle_(puzzle), puzzle_height_(puzzle.size()), puzzle_width_(puzzle[0].size()) {

}


WordLocation WordSearchSolver::FindWord(const std::string& word) {
  WordLocation location {};
  bool output = false;
  for (size_t i = 0; i < puzzle_height_&& !output; i++) {
    for (size_t j = 0; j < puzzle_width_ && !output; j++) {
      if (!(CheckHorizontal(word, i, j).char_positions.empty())) {
        return CheckHorizontal(word, i, j);
      }
      if (!(CheckVertical(word, i, j).char_positions.empty())) {
        return CheckVertical(word, i, j);
      }
      if (!(CheckLeftDiag(word, i, j).char_positions.empty())) {
        return CheckLeftDiag(word, i, j);
      }
      if (!(CheckRightDiag(word, i, j).char_positions.empty())) {
        return CheckRightDiag(word, i, j);
      }
    }
  }
  return location;
}

WordLocation WordSearchSolver::FindWord(const std::string& word, CheckDirection direction) {
  for (size_t i = 0; i < puzzle_height_; i++) {
    for (size_t j = 0; j < puzzle_width_; j++) {
      switch (direction) {
        case CheckDirection::kHorizontal:
          if (!(CheckHorizontal(word, i, j).char_positions.empty())) {
            return CheckHorizontal(word, i, j);
          }
          break;
        case CheckDirection::kVertical:
          if (!(CheckVertical(word, i, j).char_positions.empty())) {
            return CheckVertical(word, i, j);
          }
          break;
        case CheckDirection::kRightDiag:
          if (!(CheckRightDiag(word, i, j).char_positions.empty())) {
            return CheckRightDiag(word, i, j);
          }
          break;
        case CheckDirection::kLeftDiag:
          if (!(CheckLeftDiag(word, i, j).char_positions.empty())) {
            return CheckLeftDiag(word, i, j);
          }
          break;
        default:
          break;
      }
    } 
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::CheckHorizontal(const std::string& word, size_t row, size_t col) {
  WordLocation location {};
  for (size_t i = 0; i < word.size(); i++) {
    if (!LocationInBounds(row, col + i) || word[i] != puzzle_[row][col + i]) {
      return WordLocation{};
    }
    location.char_positions.push_back({word[i], row, col + i});
  }
  location.word = word;
  return location;
}

WordLocation WordSearchSolver::CheckVertical(const std::string& word, size_t row, size_t col) {
  WordLocation location {};
  for (size_t i = 0; i < word.size(); i++) {
    if (!LocationInBounds(row + i, col) || word[i] != puzzle_[row + i][col]) {
      return WordLocation{};
    }
    CharPositions char_pos = { word[i], row + i, col };
    location.char_positions.push_back(char_pos);
  }
  location.word = word;
  return location;
}

//Vector<int>dimensions
//Dimensions = [row,col]

WordLocation WordSearchSolver::CheckLeftDiag(const std::string& word, size_t row, size_t col) {
  WordLocation location;
  std::vector<CharPositions> positions;

  for (size_t i = 0; i < word.size(); i++) {
    if (LocationInBounds(row + i, col - i) && word[i] == puzzle_[row + i][col - i]) {
      positions.push_back({word[i], row + i, col - i});
    } else {
      return WordLocation{};
    }
  }

  location.char_positions = positions;
  location.word = word;
  return location;
}


WordLocation WordSearchSolver::CheckRightDiag(const std::string& word, size_t row, size_t col) {
  WordLocation location {};
  for (size_t i = 0; i < word.size(); i++) {
    if (!LocationInBounds(row + i, col + i) || word[i] != puzzle_[row + i][col + i]) {
      return WordLocation{};
    }
    location.char_positions.push_back({word[i], row + i, col + i});
  }
  location.word = word;
  return location;
}