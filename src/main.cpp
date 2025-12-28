#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <colorscheme.hpp>
#include <formatConverter.hpp>

int main(int argc, char** argv) {
    std::string imagePath = std::string(argv[1]);
    int newWidth = 1366; 
    int newHeight = 768; 

    Colorscheme colorscheme("colorschemes/tokyonight.yaml");
    std::cout << "opening " << imagePath << std::endl;
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);
    colorscheme.applyToImage(image, image);
    cv::imwrite("output.png", image);
    cv::resize(image, image, cv::Size(newWidth, newHeight), cv::INTER_LINEAR);
    cv::imshow(imagePath, image);
    cv::waitKey(0);
    cv::destroyWindow(imagePath);
    return 0;
}
