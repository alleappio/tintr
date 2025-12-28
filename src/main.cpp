#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <colorscheme.hpp>


int main(){
    cv::Vec3b colorscheme[] = {
        cv::Vec3b(26, 27, 38),      // 0: background dark (#1a1b26)
        cv::Vec3b(36, 40, 59),      // 1: background (#24283b)
        cv::Vec3b(68, 75, 108),     // 2: comment (#414868)
        cv::Vec3b(169, 177, 214),   // 3: foreground (#a9b1d6)
        cv::Vec3b(125, 207, 255),   // 4: cyan (#7dcfff)
        cv::Vec3b(125, 214, 255),   // 5: blue (#7aa2f7)
        cv::Vec3b(187, 154, 247),   // 6: purple (#bb9af7)
        cv::Vec3b(158, 206, 106),   // 7: green (#9ece6a)
        cv::Vec3b(224, 175, 104),   // 8: yellow (#e0af68)
        cv::Vec3b(255, 158, 100),   // 9: orange (#ff9e64)
        cv::Vec3b(247, 118, 142),   // 10: red (#f7768e)
        cv::Vec3b(255, 117, 127),   // 11: red2 (#ff757f)
        cv::Vec3b(192, 202, 245),   // 12: blue0 (#c0caf5)
        cv::Vec3b(115, 218, 202),   // 13: teal (#73daca)
        cv::Vec3b(217, 224, 238),   // 14: foreground light (#d9e0ee)
        cv::Vec3b(192, 202, 245)    // 15: terminal white (#c0caf5)
    };
    int newWidth = 1366; 
    int newHeight = 768; 

    Colorscheme onedark(colorscheme);
    std::cout << "opening wallpaper2.jpg" << std::endl;
    cv::Mat image = cv::imread("images/wallpaper2.jpg", cv::IMREAD_COLOR);
    //cv::cvtColor(image, image, cv::COLOR_BGR2RGB);  // Convert to RGB
    cv::resize(image, image, cv::Size(newWidth, newHeight), cv::INTER_LINEAR);
    onedark.applyToImage(image, image);
    cv::imshow("images/wallpaper2.jpg", image);
    cv::waitKey(0);
    return 0;
}
