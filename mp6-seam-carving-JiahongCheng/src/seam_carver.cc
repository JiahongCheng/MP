#include "seam_carver.hpp"
#include <iostream>
#include <sstream>

// implement the rest of SeamCarver's functions here

const ImagePPM& SeamCarver::GetImage() const { return image_; }
int SeamCarver::GetHeight() const { return height_; }
int SeamCarver::GetWidth() const { return width_; }

int SeamCarver::GetEnergy(int row, int col) const {
  Pixel left {};
  Pixel right {};
  Pixel up {};
  Pixel down {};

  //////////////////////// row
  if (row == 0) {
    up = image_.GetPixel(height_ + row - 1, col); //same col, bottom row
    down = image_.GetPixel(row + 1, col);
  } else if (row + 1 == height_) {
    up = image_.GetPixel(row - 1, col);
    down = image_.GetPixel(0, col); //back to the first row (0)
  } else {
    up = image_.GetPixel(row - 1, col);
    down = image_.GetPixel(row + 1, col);
  }
  /////////////////////// col
  if (col == 0) {
    left = image_.GetPixel(row, width_ + col - 1); //go to the last col
    right = image_.GetPixel(row, col + 1);
  } else if (col + 1 == width_) {
    left = image_.GetPixel(row, col - 1);
    right = image_.GetPixel(row, 0); //back to first col
  } else {
    left = image_.GetPixel(row, col - 1);
    right = image_.GetPixel(row, col + 1);
  }

  return (left.GetRed() - right.GetRed()) * (left.GetRed() - right.GetRed()) 
    + (left.GetBlue() - right.GetBlue()) * (left.GetBlue() - right.GetBlue()) 
    + (left.GetGreen() - right.GetGreen()) * (left.GetGreen() - right.GetGreen())
    + (up.GetRed() - down.GetRed()) * (up.GetRed() - down.GetRed())
    + (up.GetBlue() - down.GetBlue()) * (up.GetBlue() - down.GetBlue())
    + (up.GetGreen() - down.GetGreen()) * (up.GetGreen() - down.GetGreen());
}

/*
int* SeamCarver::GetHorizontalSeam() const {
  int** array = new int*[height_];

  for (int row = 0; row < height_; row++) {//create new 2d array
    array[row] = new int[width_];
  }
  for (int row = 0; row < height_; row++) {
    array[row][width_ - 1] = GetEnergy(row, width_ - 1);
  }
  for (int col = width_ - 2; col >= 0; col--) {
    for (int row  = 0; row < height_; row++) {
      if (row == 0) {//first row
        if (array[row][col + 1] <= array[row + 1][col + 1]) {
          array[row][col] = GetEnergy(row, col) + array[row][col + 1];
        }
        if (array[row][col + 1] > array[row + 1][col + 1]) {
          array[row][col] = GetEnergy(row, col) + array[row + 1][col + 1];
        }
      } else if (row == height_ - 1) {//last row
        if (array[row][col + 1] <= array[row - 1][col + 1]) {
          array[row][col] = GetEnergy(row, col) + array[row][col + 1];
        }
        if (array[row][col + 1] > array[row - 1][col + 1]) {
          array[row][col] = GetEnergy(row, col) + array[row - 1][col + 1];
        }
      } else {
        if (array[row][col + 1] > array[row - 1][col + 1])
      }
    }
  }
}
*/
int* SeamCarver::GetHorizontalSeam() const {
  int** array = new int*[height_];
  for (int row = 0; row < height_; row++) {//create new 2d array
    array[row] = new int[width_];
  }
  for (int row = 0; row < height_; row++) {
    array[row][width_ - 1] = GetEnergy(row, width_ - 1);
  }
  for (int col = width_ - 2; col >= 0; col--) {
    for (int row  = 0; row < height_; row++) {
      int min = array[row][col + 1];
      if (row == 0) {//first row
        if (min <= array[row + 1][col + 1]) {//row + 1 bottom
          array[row][col] = GetEnergy(row, col) + min;
        } else if (min > array[row + 1][col + 1]) {
          array[row][col] = GetEnergy(row, col) + array[row + 1][col + 1];
        }
      } else if (row + 1 == height_) {//bounce to the last row
        if (min > array[row - 1][col + 1]) {// row - 1 upper
          array[row][col] = GetEnergy(row, col) + array[row - 1][col + 1];
        } else if (min <= array[row - 1][col + 1]) {
          array[row][col] = GetEnergy(row, col) + min;
        }
      } else {//rest all cases
        if (array[row - 1][col + 1] < min && array[row - 1][col + 1] < array[row + 1][col + 1]) {
          array[row][col] = GetEnergy(row, col) + array[row - 1][col + 1];
        } else if (min <= array[row + 1][col + 1] && min <= array[row - 1][col + 1]) {
          array[row][col] = GetEnergy(row, col) + min;
        } else {
          array[row][col] = GetEnergy(row, col) + array[row + 1][col + 1];
        }
      }
    }
  }
  int* path = GetHorPath(array);
  for (int row = 0; row < height_; row++) {
    delete[] array[row];
  }
  delete[] array;
  return path;
}

int* SeamCarver::GetVerticalSeam() const {
  int** array = new int*[height_];
  for (int row = 0; row < height_; row++) {//2d array
    array[row] = new int[width_];
  }
  for (int col = 0; col < width_; col++) {
    array[height_ - 1][col] = GetEnergy(height_ - 1, col);
  }
  for (int row = height_ - 2; row >= 0; row--) {
    for (int col = 0; col < width_; col++) {
      int min = array[row + 1][col];
      if (col == 0) {
        if (min <= array[row + 1][col + 1]) {//right
          array[row][col] = GetEnergy(row, col) + min;
        } else if (array[row + 1][col + 1] < min) {
          array[row][col] = GetEnergy(row, col) + array[row + 1][col + 1];
        }
      } else if (col + 1 == width_) {//left
        if (min > array[row + 1][col - 1]) {
          array[row][col] = GetEnergy(row, col) + array[row + 1][col - 1];
        } else if (min <= array[row + 1][col - 1]) {
          array[row][col] = GetEnergy(row, col) + min;
        }
      } else {//rest case
        if (min > array[row + 1][col - 1] && array[row + 1][col + 1] >= array[row + 1][col - 1]) {
          array[row][col] = GetEnergy(row, col) + array[row + 1][col - 1];
        } else if (min <= array[row + 1][col + 1] && min <= array[row + 1][col - 1]) {
          array[row][col] = GetEnergy(row, col) + min;
        } else {
          array[row][col] = GetEnergy(row, col) + array[row + 1][col + 1];
        }
      }
    }
  }
  int* path = GetVerPath(array);
  for (int i = 0; i < height_; i++) {
    delete[] array[i];
  }
  delete[] array;
  return path;
}


void SeamCarver::RemoveHorizontalSeam() {
  int* path = GetHorizontalSeam();
  auto** new_pixel = new Pixel*[height_ - 1];
  int i = 0;
  for (int row = 0; row < height_ - 1; row++) {//create new image
    new_pixel[row] = new Pixel[width_];
  }
  for (int col = 0; col < width_; col++) {
    i = 0;
    for (int row = 0; row < height_; row++) {
      if (row == path[col]) {
        continue;
      }
      new_pixel[i][col] = image_.GetPixel(row, col);
      i++;
    }
  }
  height_--;
  image_.NewHeight(new_pixel, height_, width_);
  delete[] path;
}

void SeamCarver::RemoveVerticalSeam() {
  std::cout << "remove" << std::endl;
  int* path = GetVerticalSeam();
  auto** new_pixel = new Pixel*[height_];
  int i = 0; 
  for (int row = 0; row < height_; row++) {//create new image
    new_pixel[row] = new Pixel[width_ - 1];
  }
  for (int row = 0; row < height_; row++) {
    i = 0;
    for (int col = 0; col < width_; col++) {
      if (col == path[row]) {
        continue;
      }
      new_pixel[row][i] = image_.GetPixel(row, col);
      i++;
    }
  }
  width_--;
  image_.NewWidth(new_pixel, height_, width_);
  delete[] path;
}


int* SeamCarver::GetHorPath(int** array) const {
  int* path = new int[width_];
  int min = array[0][0];
  path[0] = 0;
  for (int row = 0; row < height_; row++) {
    if (array[row][0] < min) {
      min = array[row][0];
      path[0] = row;
    }
  } 
  int row = path[0];
  for (int col = 1; col < width_; col++) {
    if (row == 0) {//bounce top
      if (array[row + 1][col] < array[row][col]) {
        path[col] = row + 1;
        row = path[col];
      } else if (array[row + 1][col] >= array[row][col]) {
        path[col] = row;
      }
    } else if (row + 1 == height_) {//bounce bottom
      if (array[row - 1][col] < array[row][col]) {
        path[col] = row - 1;
        row = path[col];
      } else if (array[row - 1][col] >= array[row][col]) {
        path[col] = row;
      }
    } else {//all other case
      if (array[row + 1][col] < array[row][col] && array[row + 1][col] < array[row - 1][col]) {
        path[col] = row + 1;
        row = path[col];
      } else if (array[row + 1][col] >= array[row][col] && array[row - 1][col] >= array[row][col]) {
        path[col] = row;
      } else if (array[row - 1][col] <= array[row + 1][col] && array[row - 1][col] < array[row][col]) {
        path[col] = row - 1; 
        row = path[col];
      }
    }
  }
  return path;
}

int* SeamCarver::GetVerPath(int** array) const {
  int* path =  new int[height_];//array
  int min = array[0][0];
  path[0] = 0;
  for (int col = 0; col < width_; col++) {
    if (min > array[0][col]) {
      min = array[0][col];
      path[0] = col;
    }
  } 
  int col = path[0];
  for (int row = 1; row < height_; row++) {
    std::cout << row << " " << col << std::endl;
    if (col == 0) {
      if (array[row][col + 1] < array[row][col]) {
        path[row] = col + 1;
        col = path[row];
      } else if (array[row][col + 1] >= array[row][col]) {
        path[row] = col;
      }
    } else if (col + 1 == width_) {
      if (array[row][col - 1] < array[row][col]) {
        path[row] = col - 1;
        col = path[row];
      } else if (array[row][col - 1] >= array[row][col]) {
        path[row] = col;
      }
    } else {
      if (array[row][col + 1] < array[row][col] && array[row][col + 1] < array[row][col - 1]) {
        path[row] = col + 1;
        col = path[row];
      } else if (array[row][col + 1] >= array[row][col] && array[row][col - 1] >= array[row][col]) {
        path[row] = col;
      } else if (array[row][col - 1] <= array[row][col + 1] && array[row][col - 1] < array[row][col]) {
        path[row] = col - 1; 
        col = path[row];
      }
    }
  }
  return path;
}



// given functions below, DO NOT MODIFY

SeamCarver::SeamCarver(const ImagePPM& image): image_(image) {
  height_ = image.GetHeight();
  width_ = image.GetWidth();
}

void SeamCarver::SetImage(const ImagePPM& image) {
  image_ = image;
  width_ = image.GetWidth();
  height_ = image.GetHeight();
}
