#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <colorscheme.hpp>
#include <formatConverter.hpp>

int main(int argc, char** argv) {
    std::string imagePath = std::string(argv[1]);

    cv::Vec3b colorscheme[] = {
        FormatConverter::HEXtoRGB("#1a1b26"),   // 0: background dark (#1a1b26)
        FormatConverter::HEXtoRGB("#24283b"),   // 1: background (#24283b)
        FormatConverter::HEXtoRGB("#414868"),   // 2: comment (#414868)
        FormatConverter::HEXtoRGB("#a9b1d6"),   // 3: foreground (#a9b1d6)
        FormatConverter::HEXtoRGB("#7dcfff"),   // 4: cyan (#7dcfff)
        FormatConverter::HEXtoRGB("#7aa2f7"),   // 5: blue (#7aa2f7)
        FormatConverter::HEXtoRGB("#bb9af7"),   // 6: purple (#bb9af7)
        FormatConverter::HEXtoRGB("#9ece6a"),   // 7: green (#9ece6a)
        FormatConverter::HEXtoRGB("#e0af68"),   // 8: yellow (#e0af68)
        FormatConverter::HEXtoRGB("#ff9e64"),   // 9: orange (#ff9e64)
        FormatConverter::HEXtoRGB("#f7768e"),   // 10: red (#f7768e)
        FormatConverter::HEXtoRGB("#ff757f"),   // 11: red2 (#ff757f)
        FormatConverter::HEXtoRGB("#c0caf5"),   // 12: blue0 (#c0caf5)
        FormatConverter::HEXtoRGB("#73daca"),   // 13: teal (#73daca)
        FormatConverter::HEXtoRGB("#d9e0ee"),   // 14: foreground light (#d9e0ee)
        FormatConverter::HEXtoRGB("#c0caf5")   // 15: terminal white (#c0caf5)
    };
    int newWidth = 1366; 
    int newHeight = 768; 

    Colorscheme onedark("colorschemes/tokyonight.yaml");
    std::cout << "opening " << imagePath << std::endl;
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);
    onedark.applyToImage(image, image);
    cv::imwrite("output.png", image);
    cv::resize(image, image, cv::Size(newWidth, newHeight), cv::INTER_LINEAR);
    cv::imshow(imagePath, image);
    cv::waitKey(0);
    cv::destroyWindow(imagePath);
    return 0;
}
