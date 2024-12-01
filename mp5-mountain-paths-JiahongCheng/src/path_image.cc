#include "path_image.hpp"
#include "grayscale_image.hpp"
#include "elevation_dataset.hpp"
#include "path.hpp"

#include <iostream>

#include <fstream>
#include <cmath>

/*
class PathImage {
public:
  // write behavior declarations here; define in path_image.cc.
  PathImage(const GrayscaleImage &image, const ElevationDataset &dataset);
  size_t Width() const;
  size_t Height() const;
  unsigned int MaxColorValue() const;
  const std::vector<Path>& Paths() const;
  const std::vector<std::vector<Color> >& GetPathImage() const;
  void ToPpm(const std::string& name) const;
private:
  std::vector<Path> paths_;
  size_t width_ = 0;
  size_t height_ = 0;
  std::vector<std::vector<Color>> path_image_;
  static const int kMaxColorValue = 255;
};
*/

PathImage::PathImage(const GrayscaleImage &image, const ElevationDataset &dataset) {
  width_ = dataset.Width();
  height_ = dataset.Height();
  path_image_ = image.GetImage();
  for (size_t row = 0; row < height_; row++) {
    Path p = Path(width_, row); 
    for (size_t col = 1; col < width_; col++) {
      size_t prev_row = p.GetPath().at(col - 1); //first col
      int prev_c_data = dataset.GetData().at(prev_row).at(col - 1);// dataset = std::vector<std::vector<int>
      if (prev_row == 0) {
        int mid = abs(dataset.DatumAt(prev_row, col) - prev_c_data);
        int down = abs(dataset.DatumAt(prev_row + 1, col) - prev_c_data);
        if (mid <= down) { p.SetLoc(col, prev_row); p.IncEleChange(mid);
        } else if((down < mid)) { p.SetLoc(col, prev_row + 1); p.IncEleChange(down); }
      } else if (prev_row == height_ - 1) { int mid = abs(dataset.DatumAt(prev_row, col) - prev_c_data); int up = abs(dataset.DatumAt(prev_row - 1, col) - prev_c_data);
        if ((up < mid)) { p.SetLoc(col, prev_row - 1); p.IncEleChange(up);
        } else if ((mid <= up)) { p.SetLoc(col, prev_row); p.IncEleChange(mid); }
      } else { int up = abs(dataset.DatumAt(prev_row - 1, col) - prev_c_data); int mid = abs(dataset.DatumAt(prev_row, col) - prev_c_data); int down = abs(dataset.DatumAt(prev_row + 1, col) - prev_c_data);
        if ((up < mid && up < down)) { p.SetLoc(col, prev_row - 1); p.IncEleChange(up);
        } else if ((mid <= up && mid <= down)) { p.SetLoc(col, prev_row); p.IncEleChange(mid);
        } else if((down < up && down < mid) || (down == up && down < mid)) {  p.SetLoc(col, prev_row + 1); p.IncEleChange(down); }
      }
    }
    paths_.push_back(p);
  } 
  Color red = Color(kRedR, kRedG, kRedB); Color green  = Color(kGreenR, kGreenG, kGreenB); Path min = paths_[0];
  for (const Path& p: paths_) {
    for (size_t i = 0; i < width_; i++) {
      path_image_.at(p.GetPath().at(i)).at(i) = red;
    }
  }
  for (size_t i = 0; i < height_; i++) {
    if (paths_.at(i).EleChange() < min.EleChange()) {
      min = paths_.at(i);
    }
  }
  for (size_t w = 0; w < width_; w++) {
    path_image_.at(min.GetPath().at(w)).at(w) = green;
  }
}



void PathImage::ToPpm(const std::string& name) const {
  std::ofstream ofs{name};
    if (!ofs.is_open()) {
        throw std::runtime_error("invalid file path");
    }
    ofs << "P3" << '\n';
    ofs << width_ << " " << height_ << '\n';
    ofs << "255" << '\n';
    for (size_t row = 0; row < height_; row++) {
        for (size_t col = 0; col < width_; col++) {
            ofs << path_image_[row][col].Red() << " ";
            ofs << path_image_[row][col].Green() << " ";
            ofs << path_image_[row][col].Blue() << " ";
        }
        ofs << '\n';
    }
}

/*

Path WalkingDirection(Path p, size_t prev_row, size_t col, int upper_right, int current_row, int bottom_right, int prev_c_data) {
  Path output = p;
  if (upper_right < current_row && bottom_right > upper_right) { output.SetLoc(col, prev_row - 1); output.IncEleChange(abs(prev_c_data - upper_right));
      } 
      if (current_row < bottom_right && current_row < upper_right) { output.SetLoc(col, prev_row); output.IncEleChange(abs(prev_c_data - current_row));
      }
      if (bottom_right < current_row && bottom_right < upper_right) { output.SetLoc(col, prev_row + 1); output.IncEleChange(abs(prev_c_data - bottom_right));
      }
  return output;
}


*/

//void BestWay(std::vector<Path> paths_, std::vector<std::vector<Color>> path_image_) {

//}