#include "board.hpp"

// you might need additional includes
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

/**************************************************************************/
/* your function definitions                                              */
/**************************************************************************/

void InitBoard(Board& b) {
  // below was minimal to get tests to actually compile and given test case to
  // fail
  for (int i = 0; i < Board::kBoardHeight; i++) {
    for (int j = 0; j < Board::kBoardWidth; j++) {
      b.board[i][j] = DiskType::kEmpty;
    }
  }
  // b.board[0][0] = DiskType::kEmpty;
}
void DropDiskToBoard(Board& b, DiskType disk, int col) {
  if (col >= Board::kBoardWidth || col < 0) {
    throw std::runtime_error("Invalid Column");
  }
  bool fill = false;
  for (int i = 0; i < Board::kBoardHeight; i++) {
    if (b.board[i][col] == DiskType::kEmpty) {
      fill = true;
    }
  }
  if (!(fill)) {
    throw std::runtime_error("column filled");
  }

  for (int i = 0; i < Board::kBoardHeight; i++) {
    // check if the colume is empty
    if (b.board[i][col] == DiskType::kEmpty) {
      b.board[i][col] = disk;
      break;
    }
  }
}

bool CheckForWinner(Board& b, DiskType disk) {
  bool win = false;
  if (SearchForWinner(b, disk, WinningDirection::kHorizontal)) {
    win = true;
  }
  if (SearchForWinner(b, disk, WinningDirection::kVertical)) {
    win = true;
  }
  if (SearchForWinner(b, disk, WinningDirection::kRightDiag)) {
    win = true;
  }
  if (SearchForWinner(b, disk, WinningDirection::kLeftDiag)) {
    win = true;
  }
  return win;
}
bool SearchForWinner(Board& b, DiskType disk, WinningDirection to_check) {
  bool output = false;
  if (to_check == WinningDirection::kHorizontal) {
    output = CheckHorizontal(b, disk);
  }
  if (to_check == WinningDirection::kVertical) {
    output = CheckVertical(b, disk);
  }
  if (to_check == WinningDirection::kLeftDiag) {
    output = CheckLeftDiag(b, disk);
  }
  if (to_check == WinningDirection::kRightDiag) {
    output = CheckRightDiag(b, disk);
  }
  return output;
}
bool CheckHorizontal(Board& b, DiskType disk) {
  bool output = false;
  for (int i = 0; i < Board::kBoardHeight; i++) {
    int num = 0;
    for (int j = 0; j < Board::kBoardWidth; j++) {
      if (b.board[i][j] == disk && b.board[i][j + 1] == disk) {
        num++;
        if (num == 3) {
          output = true;
        }
      }
    }
  }
  return output;
}

bool CheckVertical(Board& b, DiskType disk) {
  bool output = false;
  for (int i = 0; i < Board::kBoardWidth; i++) {
    int num = 0;
    for (int j = 0; j < Board::kBoardHeight - 1; j++) {
      if (b.board[j][i] == disk && b.board[j + 1][i] == disk) {
        num++;
        if (num >= 3) {
          output = true;
        }
      }
    }
  }
  return output;
}

bool CheckLeftDiag(Board& b, DiskType disk) {
  bool output = false;
  int i = 0;
  while (i < Board::kBoardHeight - 3) {
    int j = 3;
    while (j < Board::kBoardWidth) {
      if (b.board[i][j] == disk && b.board[i + 1][j - 1] == disk &&
          b.board[i + 2][j - 2] == disk && b.board[i + 3][j - 3] == disk) {
        output = true;
      }
      j++;
    }
    i++;
  }
  return output;
}

bool CheckRightDiag(Board& b, DiskType disk) {
  bool output = false;
  int i = 0;
  while (i < Board::kBoardHeight - 3) {
    int j = 0;
    while (j < Board::kBoardWidth - 3) {
      if (b.board[i][j] == disk && b.board[i + 1][j + 1] == disk &&
          b.board[i + 2][j + 2] == disk && b.board[i + 3][j + 3] == disk) {
        output = true;
      }
      j++;
    }
    i++;
  }
  return output;
}

bool BoardLocationInBounds(int row, int col) {
  bool b = true;
  if (row >= Board::kBoardHeight || row < 0 || col >= Board::kBoardWidth ||
      col < 0) {
    b = false;
  }
  return b;
}

/**************************************************************************/
/* provided to you                                                        */
/**************************************************************************/
std::string BoardToStr(const Board& b) {
  constexpr int kTotalWidth = Board::kBoardWidth * 11 - Board::kBoardHeight - 1;
  std::stringstream ss;
  ss << std::endl;
  for (int row = Board::kBoardHeight; row > 0; --row) {
    ss << " |";
    for (int col = 0; col < Board::kBoardWidth; ++col) {
      std::string value_here;
      value_here.push_back(static_cast<char>(b.board[row - 1][col]));
      ss << ' ' << CenterStr(value_here, Board::kBoardWidth + 1) << '|';
    }
    ss << std::endl;
    ss << " |" << std::setw(kTotalWidth) << std::setfill('-') << '|'
       << std::endl;
  }
  ss << " |";
  for (int col = 0; col < Board::kBoardWidth; ++col) {
    ss << ' ' << CenterStr(std::to_string(col), Board::kBoardWidth + 1) << '|';
  }
  return ss.str();
}

std::string CenterStr(const std::string& str, int col_width) {
  // quick and easy (but error-prone) implementation
  auto padl = (col_width - str.length()) / 2;
  auto padr = (col_width - str.length()) - padl;
  std::string strf = std::string(padl, ' ') + str + std::string(padr, ' ');
  return strf;
}