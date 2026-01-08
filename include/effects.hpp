#include <opencv2/opencv.hpp>

class Effects {
    public:
        static void blur(cv::Mat& input_image, cv::Mat& output_image, unsigned int amount);

};
