#include "elevation_dataset.hpp"

#include <fstream>
#include <iostream>

ElevationDataset::ElevationDataset(const std::string& filename, size_t width, size_t height) {
    width_ = width;
    height_ = height;
    std::ifstream ifs{filename};
    if (!ifs.is_open()) {
        throw std::runtime_error("file can not open");
    }
    int tmp = 0;
    std::vector<int> data;
    while (ifs.good()) {
        ifs >> tmp;
        if (ifs.fail()) {
            ifs.clear();
            ifs.ignore(1, '\n');
        } else {
            data.push_back(tmp);
        }
    }
    
    if (data.size() != width * height) {
        throw std::runtime_error("invalid size");
    }
    max_ele_ = Max(data);
    min_ele_ = Min(data);
    size_t i = 0;
    for (size_t row = 0; row < height_; row++) {
        std::vector<int> tmpdata;
        for (size_t col = 0; col < width_; col ++) {
            tmpdata.push_back(data[i]);
            i++;
        }
        data_.push_back(tmpdata);
    }
}

int ElevationDataset::DatumAt(size_t row, size_t col) const {
    return data_[row][col];
}

int Max(std::vector<int> input) {
    int max = input[0];
    for (unsigned int i = 0; i < input.size(); i++) {
        if(input[i] > max) {
            max = input[i];
        }
    }
    return max;
}
int Min(std::vector<int> input) {
    int min = input[0];
    for (unsigned int i = 0; i < input.size(); i++) {
        if(input[i] < min) {
            min = input[i];
        }
    }
    return min;
}