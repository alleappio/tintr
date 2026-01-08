#include "effects.hpp"
#include <opencv2/imgproc.hpp>

void Effects::blur(cv::Mat& input_image, cv::Mat& output_image, unsigned int amount){
    if(amount%2==0)
        amount+=1;
    cv::GaussianBlur(input_image, output_image, cv::Size(amount, amount), 5);
}
