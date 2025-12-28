#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <colorscheme.hpp>
#include <formatConverter.hpp>
#include <cxxopts.hpp>

int main(int argc, char** argv) {
    cxxopts::Options options("colorscheme_util", "colorscheme utilities");
    options.add_options()
        ("i,input", "path to the input image", cxxopts::value<std::string>())
        ("c,colorscheme", "path to the colorscheme yaml file", cxxopts::value<std::string>())
        ("o,output", "path in which the final image will be created", cxxopts::value<std::string>()->default_value("output.png"))
        ("s,show", "show results in a window", cxxopts::value<bool>())
        ("h,help", "print usage");

    auto config = options.parse(argc, argv);

    if (config.count("help") || !config.count("input") || !config.count("colorscheme")){
      std::cout << options.help() << std::endl;
      exit(0);
    }

    std::string imagePath = config["input"].as<std::string>();
    int newWidth = 1366; 
    int newHeight = 768; 

    Colorscheme colorscheme(config["colorscheme"].as<std::string>());
    std::cout << "opening " << imagePath << std::endl;
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);
    colorscheme.applyToImage(image, image);
    std::cout << "saving image in " << config["output"].as<std::string>() << std::endl;
    cv::imwrite(config["output"].as<std::string>(), image);
    if(config["show"].as<bool>()){
        cv::resize(image, image, cv::Size(newWidth, newHeight), cv::INTER_LINEAR);
        cv::imshow(imagePath, image);
        cv::waitKey(0);
        cv::destroyWindow(imagePath);
    }
    return 0;
}
