#include <colorscheme.hpp>
#include <limits>

Colorscheme::Colorscheme(){

}

Colorscheme::Colorscheme(cv::Vec3b* colorscheme){
    for(unsigned int i=0; i<16; i++){
        this->colors[i] = colorscheme[i];
    }
}


void Colorscheme::applyToImage(cv::Mat& inImage, cv::Mat& outImage){
    for(unsigned int i=0; i<inImage.rows; i++){
        for(unsigned int j=0; j<inImage.cols; j++){
            cv::Vec3b newColor = this->colors[this->findClosestColor(inImage.at<cv::Vec3b>(i,j))];
            outImage.at<cv::Vec3b>(i,j) = newColor;
//            std::cout << "chose color " << newColor << " for color " << inImage.at<cv::Vec3b>(i,j) << std::endl; 
        }
    }
}

unsigned int Colorscheme::findClosestColor(cv::Vec3b color){
    unsigned int result = 0;
    unsigned int min_distance = 255*3;
    for(unsigned int i=0; i<16; i++){
        unsigned int distance = this->getColorDistance(this->colors[i], color);
        if(distance<min_distance){
            min_distance = distance;
            result = i;
        }
    }
    return result;
}

unsigned int Colorscheme::getColorDistance(cv::Vec3b color1, cv::Vec3b color2){
    unsigned int distance = 0;
    for(unsigned int i=0; i<3; i++){
        distance += abs(color1[i]-color2[i]);
    }
    return distance;
}
