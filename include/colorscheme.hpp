#ifndef COLORSCHEME_HPP
#define COLORSCHEME_HPP
#include <opencv2/opencv.hpp>
#include <vector>
#include <yaml-cpp/yaml.h>
#include <formatConverter.hpp>

class Colorscheme {
    private:
    std::vector<cv::Vec3b> colors;
    public: 
        Colorscheme();
        Colorscheme(std::vector<cv::Vec3b> colorscheme);
        Colorscheme(std::string filename);
        Colorscheme(cv::Mat* image);
        void applyToImage(cv::Mat& inImage, cv::Mat& outImage);
        unsigned int findClosestColor(cv::Vec3b color);
        unsigned int getColorDistance(cv::Vec3b color1, cv::Vec3b color2);
        void extractPaletteKMeans(cv::Mat image, int k);
        std::vector<cv::Vec3b> getColorscheme();  
};
#endif // COLORSCHEME_HPP
