#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"
#include "path_image.hpp"

#include <iostream>

int main() {
    size_t w = 480;
    size_t h = 480;
    ElevationDataset e = ElevationDataset("/home/vagrant/src/mp5-mountain-paths-JiahongCheng/example-data/ex_input_data/map-input-w480-h480.dat", w, h);
    GrayscaleImage ws = GrayscaleImage(e);
    std::cout << "hello" << std::endl;
    PathImage path = PathImage(ws, e);
    std::cout << "hello world" << std::endl;
    path.ToPpm("/home/vagrant/src/mp5-mountain-paths-JiahongCheng/example-data/ex_output_paths/name.ppm");
    std::cout << "hello world again" << std::endl;
    return 0;
}