#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <chrono>
#include <boost/format.hpp>
#include "sphere2cube.h"

cv::Mat bicubicImage(cv::Mat face) {
  cv::Mat image;
  cv::resize(face, image, cv::Size(), 0.5, 0.5, cv::INTER_CUBIC);
  return image;
}

char *duplicate_str(std::string str) {
  int calloc_size = str.length() + 1;
  char *duplicate = (char *)calloc(calloc_size, sizeof(char));
  str.copy(duplicate, str.length());
  return duplicate;
}

const char *concat(std::string directory, std::string prefix, const char* filename) {
    std::string separator = "/";
    std::string dir = directory + separator;
    std::string pre = duplicate_str(prefix);
    dir += pre + "_";
    return strcat(duplicate_str(dir), filename);
}

int main(int argc, char** argv){
    std::string directory(argv[1]);
    std::string prefix(argv[2]);
    int tilesize = atoi(argv[3]);

    cv::Mat image = cv::imread(argv[4], CV_LOAD_IMAGE_COLOR);
    Sphere2Cube s2c(tilesize * 2);
    Faces cube;

    auto t1 = std::chrono::steady_clock::now();
    s2c.transform(image, cube);

    const char* up_file_path = concat(directory, prefix, "up.jpg");
    const char* front_file_path = concat(directory, prefix, "front.jpg");
    const char* right_file_path = concat(directory, prefix, "right.jpg");
    const char* back_file_path = concat(directory, prefix, "back.jpg");
    const char* left_file_path = concat(directory, prefix, "left.jpg");
    const char* down_file_path = concat(directory, prefix, "down.jpg");

    cv::imwrite(up_file_path, bicubicImage(cube.faces[0]));
    cv::imwrite(front_file_path, bicubicImage(cube.faces[1]));
    cv::imwrite(right_file_path, bicubicImage(cube.faces[2]));
    cv::imwrite(back_file_path, bicubicImage(cube.faces[3]));
    cv::imwrite(left_file_path, bicubicImage(cube.faces[4]));
    cv::imwrite(down_file_path, bicubicImage(cube.faces[5]));

    auto t2 = std::chrono::steady_clock::now();
    printf("Cost %f s.\n", std::chrono::duration_cast<std::chrono::duration<double> >(t2 - t1).count());

    return 0;
}
