#ifndef FORMATCONVERTER_HPP
#define FORMATCONVERTER_HPP
#include <opencv2/opencv.hpp>

class FormatConverter {
    public:
        static std::string RGBtoHEX(cv::Vec3b rgbColor);
        static cv::Vec3b HEXtoRGB(std::string hexColor);
};
#endif // FORMATCONVERTER_HPP
