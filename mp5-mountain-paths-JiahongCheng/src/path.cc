#include "path.hpp"

#include <cstdlib> 
#include <vector>



/*
public:
  // write behavior declarations here; define in path.cc.
  Path(size_t length, size_t starting_row);
  size_t Length() const;
  size_t StartingRow() const;
  unsigned int EleChange() const;
  void IncEleChange(unsigned int value);
  const std::vector<size_t>& GetPath() const;
  void SetLoc( size_t col, size_t row );
private:
  size_t length_;
  size_t starting_row_;
  std::vector<size_t> path_;
  unsigned int ele_change_ = 0;
*/

Path::Path(size_t length, size_t starting_row) {
    length_ = length; 
    starting_row_ = starting_row;
    for (size_t i = 0; i < length_; i++) {
        path_.push_back(starting_row);
    }
}

size_t Path::Length() const {
    return length_;
}
size_t Path::StartingRow() const {
    return starting_row_;
}
unsigned int Path::EleChange() const {
    return ele_change_;
}

void Path::IncEleChange(unsigned int value) {
    ele_change_ = ele_change_ + value;
}
const std::vector<size_t>& Path::GetPath() const {
    return path_;
}

void Path::SetLoc( size_t col, size_t row ) {
    path_[col] = row;
}