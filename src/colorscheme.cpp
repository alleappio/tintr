#include <colorscheme.hpp>
#include <limits>

Colorscheme::Colorscheme(){}

Colorscheme::Colorscheme(std::string filename){
    YAML::Node config = YAML::LoadFile(filename);
    for(unsigned int i=0; i<16; i++){
        std::string hexColor = config["colorscheme"][i].as<std::string>();
        this->colors[i] = FormatConverter::HEXtoRGB(hexColor);
    }
}

Colorscheme::Colorscheme(cv::Vec3b* colorscheme){
    for(unsigned int i=0; i<16; i++){
        this->colors[i] = colorscheme[i];
    }
}

Colorscheme::Colorscheme(cv::Mat* image){
    this->extractPaletteKMeans(*image, 16);
}

void Colorscheme::applyToImage(cv::Mat& inImage, cv::Mat& outImage){
    for(unsigned int i=0; i<inImage.rows; i++){
        for(unsigned int j=0; j<inImage.cols; j++){
            cv::Vec3b newColor = this->colors[this->findClosestColor(inImage.at<cv::Vec3b>(i,j))];
            outImage.at<cv::Vec3b>(i,j) = newColor;
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

void Colorscheme::extractPaletteKMeans(cv::Mat image, int k){
    cv::Mat data = image.reshape(1, image.rows * image.cols); // Flatten to Nx3
    data.convertTo(data, CV_32F);
    
    cv::Mat labels, centers;
    cv::kmeans(data, k, labels,
               cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 10, 1.0),
               3, cv::KMEANS_PP_CENTERS, centers);
    
    centers.convertTo(centers, CV_8U);
    for(unsigned int i=0; i<k; i++){
        this->colors[i] = centers.at<cv::Vec3b>(i);
    }
}

cv::Vec3b* Colorscheme::getColorscheme(){
    return this->colors;
}
