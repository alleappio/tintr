#include <iostream>
#include <opencv2/opencv.hpp>

int main(){
    std::cout << "opening wallpaper.png" << std::endl;
    cv::Mat image = cv::imread("wallpaper.png");
    cv::imshow("wallpaper.png", image);
    cv::waitKey(0);
    return 0;
}
