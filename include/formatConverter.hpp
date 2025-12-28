#ifndef FORMATCONVERTER_HPP
#define FORMATCONVERTER_HPP
#include <opencv2/opencv.hpp>

class FormatConverter {
    public:
        static std::string RGBtoHEX(cv::Vec3b rgbColor);
        static std::string BGRtoHEX(cv::Vec3b bgrColor);
        static cv::Vec3b HEXtoRGB(std::string hexColor);
};
#endif // FORMATCONVERTER_HPP
