// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include <catch/catch.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "color.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"
#include "path_image.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("True == True", "") { REQUIRE(true == true); }

/////////////////////////////////////////////////////////////////////////////////////////////


/*

if (row == 0) {
        int current_row = abs(dataset.GetData().at(prev_col).at(col) - prev_c_data);
        int bottom_right = abs(dataset.GetData().at(prev_col + 1).at(col) - prev_c_data); 
        if ((current_row < bottom_right) || current_row <= bottom_right) { p.SetLoc(col, prev_col); p.IncEleChange(abs(prev_c_data - current_row)); }
        if (bottom_right < current_row) { p.SetLoc(col, prev_col + 1); p.IncEleChange(abs(prev_c_data - bottom_right)); }
      } else if (row == height_ - 1) {
        int upper_right = abs(dataset.GetData().at(prev_col - 1).at(col) - prev_c_data); 
        int current_row = abs(dataset.GetData().at(prev_col).at(col) - prev_c_data);
        if (upper_right < current_row) { p.SetLoc(col, prev_col - 1); p.IncEleChange(abs(prev_c_data - upper_right)); } 
        if ((current_row < upper_right) || (current_row == upper_right)) { p.SetLoc(col, prev_col); p.IncEleChange(abs(prev_c_data - current_row)); }
      }
      int upper_right = abs(dataset.GetData().at(prev_col - 1).at(col) - prev_c_data); 
      int current_row = abs(dataset.GetData().at(prev_col).at(col) - prev_c_data);
      int bottom_right = abs(dataset.GetData().at(prev_col + 1).at(col) - prev_c_data); 
      if (upper_right < current_row && bottom_right > upper_right) { p.SetLoc(col, prev_col - 1); p.IncEleChange(abs(prev_c_data - upper_right)); } 
      if ((current_row < bottom_right && current_row < upper_right) || (current_row <= bottom_right && current_row == upper_right)) { p.SetLoc(col, prev_col); p.IncEleChange(abs(prev_c_data - current_row)); }
      if ((bottom_right < current_row && bottom_right < upper_right) || (bottom_right == upper_right && bottom_right < current_row)){ p.SetLoc(col, prev_col + 1); p.IncEleChange(abs(prev_c_data - bottom_right)); }
      











    for (size_t row = 0; row < height_; row++) {
    Path p = Path(width_, row); 
    for (size_t col = 1; col < width_; col++) {
      size_t prev_row = p.GetPath().at(col - 1); //first col
      int prev_c_data = dataset.GetData().at(prev_row).at(col); // dataset = std::vector<std::vector<int>
      if (row == 0) {
        int mid = abs(dataset.DatumAt(prev_row, col) - prev_c_data);
        int down = abs(dataset.DatumAt(prev_row + 1, col) - prev_c_data);
        if ((mid < down) || (mid == down)) {
          p.SetLoc(col, prev_row);
          p.IncEleChange(abs(prev_c_data - mid));
        } else if((down < mid)) {
          p.SetLoc(col, prev_row + 1);
          p.IncEleChange(abs(prev_c_data - mid));
        }
      } else if (row == height_ - 1) {
        int mid = abs(dataset.DatumAt(prev_row, col) - prev_c_data);
        int up = abs(dataset.DatumAt(prev_row - 1, col) - prev_c_data);
        if ((up < mid)) {
          p.SetLoc(col, prev_row - 1);
          p.IncEleChange(abs(prev_c_data - up));
        } else if ((mid < up) || (mid == up)) {
          p.SetLoc(col, prev_row);
          p.IncEleChange(abs(prev_c_data - mid));
        }
      } else {
        int up = abs(dataset.DatumAt(prev_row - 1, col) - prev_c_data);
        int mid = abs(dataset.DatumAt(prev_row, col) - prev_c_data);
        int down = abs(dataset.DatumAt(prev_row + 1, col) - prev_c_data);
        if ((up < mid && up < down)) {
          p.SetLoc(col, prev_row - 1);
          p.IncEleChange(abs(prev_c_data - up));
        } else if ((mid < up && mid < down) || (mid == up && mid <= down)) {
          p.SetLoc(col, prev_row);
          p.IncEleChange(abs(prev_c_data - mid));
        } else if((down < up && down < mid) || (down == up && down < mid)) {
          p.SetLoc(col, prev_row + 1);
          p.IncEleChange(abs(prev_c_data - mid));
        }
      }
      // for visual///////////////////////////////
      for (size_t i = 0; i < p.Length(); i++) {
        std::cout << p.GetPath().at(i) << std::endl;
        break;
      }
      break;
      /////////////////////////////////
    }
    paths_.push_back(p);
  } 





















      */

