#include "grayscale_image.hpp"
#include <iostream>
#include <cmath>

#include <fstream>
/*
class GrayscaleImage {
public:
  // write behavior declarations here; define in grayscale_image.cc.
  GrayscaleImage(const ElevationDataset& dataset);
  GrayscaleImage(const std::string& filename, size_t width, size_t height);
  size_t Width() const;
  size_t Height() const;
  unsigned int MaxColorValue() const;
  const Color& ColorAt(int row, int col) const;
  const std::vector<std::vector<Color> >& GetImage() const;
  void ToPpm( const std::string& name ) const;
private:
  size_t width_;
  size_t height_;
  std::vector<std::vector<Color>> image_;
  static const int kMaxColorValue = 255;
};
*/



GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
    width_ = dataset.Width();
    height_ = dataset.Height();
    //std::cout << width_ << std::endl;
    int shade_of_gray = 0;
    for (size_t row = 0; row < height_; row++) {
        std::vector<Color> tmp;
        for (size_t col = 0; col < width_; col++) {
            int color_int = dataset.DatumAt(row, col);
            if (dataset.MaxEle() != dataset.MinEle()) {
                shade_of_gray = (int) std::round(double(color_int - dataset.MinEle()) / double(dataset.MaxEle() - dataset.MinEle()) * kMaxColorValue);
            } 
            Color c = {shade_of_gray, shade_of_gray, shade_of_gray};
            tmp.push_back(c);
        }
        image_.push_back(tmp);
    }
}

GrayscaleImage::GrayscaleImage(const std::string& filename, size_t width, size_t height) {
    ElevationDataset dataset = ElevationDataset(filename, width, height);
    width_ = dataset.Width();
    height_ = dataset.Height();
    int shade_of_gray = 0; 

    for (size_t row = 0; row < height_; row++) {
        std::vector<Color> tmp;
        for (size_t col = 0; col < width_; col++) {
            int color_int = dataset.DatumAt(row, col);
            if (dataset.MaxEle() != dataset.MinEle()) {
                shade_of_gray = (int) std::round(double(color_int - dataset.MinEle()) / double(dataset.MaxEle() - dataset.MinEle()) * kMaxColorValue);
            } 
            Color c = {shade_of_gray, shade_of_gray, shade_of_gray};
            tmp.push_back(c);
        }
        image_.push_back(tmp);
    }
    //std::cout << image_[0][0].Blue() << std::endl;
}

void GrayscaleImage::ToPpm( const std::string& name ) const {
    std::ofstream ofs{name};
    if (!ofs.is_open()) {
        throw std::runtime_error("invalid file gray");
    }
    ofs << "P3" << '\n';
    ofs << width_ << " " << height_ << '\n';
    ofs << "255" << '\n';
    for (size_t row = 0; row < height_; row++) {
        for (size_t col = 0; col < width_; col++) {
            ofs << image_[row][col].Red() << " ";
            ofs << image_[row][col].Green() << " ";
            ofs << image_[row][col].Blue() << " ";
        }
        ofs << '\n';
    }
}


size_t GrayscaleImage::Width() const { return width_; }
size_t GrayscaleImage::Height() const {return height_; }
unsigned int GrayscaleImage::MaxColorValue() const { return kMaxColorValue; }
const Color& GrayscaleImage::ColorAt(int row, int col) const { return image_[row][col]; }
const std::vector<std::vector<Color> >& GrayscaleImage::GetImage() const { return image_; }




