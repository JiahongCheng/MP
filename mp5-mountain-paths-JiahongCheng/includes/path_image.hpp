#ifndef PATH_IMAGE_H
#define PATH_IMAGE_H

#include <cstdlib>  // for size_t
#include <vector>

#include "color.hpp"
#include "path.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"

class PathImage {
public:
  // write behavior declarations here; define in path_image.cc.
  PathImage(const GrayscaleImage &image, const ElevationDataset &dataset);
  size_t Width() const { return width_; };
  size_t Height() const { return height_; }
  unsigned int MaxColorValue() const {return kMaxColorValue; }
  const std::vector<Path>& Paths() const { return paths_; }
  const std::vector<std::vector<Color> >& GetPathImage() const { return path_image_; }
  void ToPpm(const std::string& name) const;
private:
  std::vector<Path> paths_;
  size_t width_ = 0;
  size_t height_ = 0;
  std::vector<std::vector<Color>> path_image_;
  static const int kMaxColorValue = 255;

  static const int kRedR = 252;
  static const int kRedG = 25;
  static const int kRedB = 63;
  static const int kGreenR = 31;
  static const int kGreenG = 253;
  static const int kGreenB = 13;
};

//Path WalkingDirection(Path p, size_t prev_row, size_t col, int upper_right, int current_row, int bottom_right, int prev_c_data);


//void BestWay(std::vector<Path> paths_, std::vector<std::vector<Color>> path_image_);

#endif