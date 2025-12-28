#ifndef COLORSCHEME_HPP
#define COLORSCHEME_HPP
#include <opencv2/opencv.hpp>
#include <yaml-cpp/yaml.h>
#include <formatConverter.hpp>

class Colorscheme {
    private:
        cv::Vec3b colors[16];
    public: 
        Colorscheme();
        Colorscheme(cv::Vec3b* colorscheme);
        Colorscheme(std::string filename);
        void applyToImage(cv::Mat& inImage, cv::Mat& outImage);
        unsigned int findClosestColor(cv::Vec3b color);
        unsigned int getColorDistance(cv::Vec3b color1, cv::Vec3b color2);
};
#endif // COLORSCHEME_HPP
