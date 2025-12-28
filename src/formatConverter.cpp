#include <formatConverter.hpp>

std::string FormatConverter::RGBtoHEX(cv::Vec3b rgbColor){
    char buffer[7];
    sprintf(buffer, "%02X%02X%02X", rgbColor[0], rgbColor[1], rgbColor[2]);
    std::string hexColor(buffer);
    return hexColor;
}

cv::Vec3b FormatConverter::HEXtoRGB(std::string hexColor){
    unsigned int r, g, b;
    cv::Vec3b rgbColor;
    sscanf(hexColor.c_str(), "#%02x%02x%02x", &r, &g, &b);
    rgbColor[0] = r;
    rgbColor[1] = g;
    rgbColor[2] = b;
    return rgbColor;
}
