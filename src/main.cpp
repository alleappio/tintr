#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <cxxopts.hpp>
#include <sstream>
#include <yaml-cpp/emittermanip.h>
#include <yaml-cpp/yaml.h>
#include <fstream>

#include "colorscheme.hpp"
#include "formatConverter.hpp"
#include "effects.hpp"

#define DOWNSCALE_WIDTH 1366
#define DOWNSCALE_HEIGHT 768

void helpPrint(cxxopts::Options options){
    std::cout << options.help() << "\n";
    std::cout << "currently implemented actions are:\n";
    std::cout << "\t- apply: apply a colorscheme to the image\n";
    std::cout << "\t- extract: extract a colorscheme from an image\n";
    std::cout << "\t- blur: blur an image\n" << std::endl;
}

void saveColorschemeToFile(std::string filename, std::vector<cv::Vec3b> colorscheme){
    std::ofstream fout(filename);
    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "colorscheme";
    out << YAML::BeginSeq;
    for(const auto& color : colorscheme){
        out << FormatConverter::BGRtoHEX(color);
    }
    out << YAML::EndSeq << YAML::EndMap;
    fout << out.c_str();
    fout.close();
}

void applyColorschemeToImage(std::string inputPath, std::string colorschemePath, std::string outputImagePath, bool showImage){
    Colorscheme colorscheme(colorschemePath);
    std::cout << "opening " << inputPath << std::endl;
    cv::Mat image = cv::imread(inputPath, cv::IMREAD_COLOR);
    colorscheme.applyToImage(image, image);
    std::cout << "saving image in " << outputImagePath << std::endl;
    cv::imwrite(outputImagePath, image);
    if(showImage){
        cv::resize(image, image, cv::Size(DOWNSCALE_WIDTH, DOWNSCALE_HEIGHT), cv::INTER_LINEAR);
        cv::imshow(inputPath, image);
        cv::waitKey(0);
        cv::destroyWindow(inputPath);
    }
}

void extractColorschemeFromImage(std::string inputPath, unsigned int length, bool saveColorscheme, std::string outputColorschemePath){
    std::cout << "opening image " << inputPath << std::endl;
    cv::Mat image = cv::imread(inputPath, cv::IMREAD_COLOR);
    Colorscheme colorscheme(&image, length);
    std::vector<cv::Vec3b> palette = colorscheme.getColorscheme();
    if(!saveColorscheme){
        std::cout << "colorscheme:" << "\n";
        std::cout << "\t[" << "\n";
        for(unsigned int i=0; i<length; i++){
            std::cout << "\t\t\"" << FormatConverter::BGRtoHEX(palette.at(i)) << "\"," << "\n";
        }
        std::cout << "\t]" << "\n";
        std::cout << "\n";
    } else {
        std::cout << "saving colorscheme to file " << outputColorschemePath << std::endl; 
        saveColorschemeToFile(outputColorschemePath, palette);
    }
}

void blurImage(std::string inputPath, unsigned int blurAmount, std::string outputImagePath, bool showImage){
    std::cout << "opening image " << inputPath << std::endl;
    cv::Mat image = cv::imread(inputPath, cv::IMREAD_COLOR);
    cv::Mat blurred;

    Effects::blur(image, blurred, blurAmount);
    cv::imwrite(outputImagePath, blurred);

    if(showImage){
        cv::resize(blurred, blurred, cv::Size(DOWNSCALE_WIDTH, DOWNSCALE_HEIGHT), cv::INTER_LINEAR);
        cv::imshow(inputPath, blurred);
        cv::waitKey(0);
        cv::destroyWindow(inputPath);
    }
}

int main(int argc, char** argv) {
    cxxopts::Options options("tintr", "colorscheme and images utilities");

    options.add_options()
        ("action", "action to perform", cxxopts::value<std::string>())
        ("input", "input to process", cxxopts::value<std::string>())
        ("output", "output of the action", cxxopts::value<std::string>())
        ("ba,blur_amount", "Amount of blurness", cxxopts::value<unsigned int>()->default_value("1"))
        ("c,colorscheme", "path to the colorscheme yaml file that will be applied to the image", cxxopts::value<std::string>())
        ("l,length", "number of colors to extract from the image", cxxopts::value<unsigned int>()->default_value("16"))
        ("s,show", "show results in a window", cxxopts::value<bool>())
        ("h,help", "print usage");

    options.parse_positional({"action", "input", "output"});
    std::stringstream positional_help;
    positional_help << "<action> <input> <output>\n";
    positional_help << "\n";
    positional_help << "\taction: action to perform\n";
    positional_help << "\tinput: path to the input image\n";
    positional_help << "\toutput: path to the output file\n";
    options.positional_help(positional_help.str());

    auto config = options.parse(argc, argv);
    if (config.count("action") == 0 ||
        config.count("input") == 0 ||
        config.count("output") == 0){

        helpPrint(options);
        exit(0);
    }

    std::string action({config["action"].as<std::string>()});
    std::string inputPath = config["input"].as<std::string>();
    std::string outputPath = config["output"].as<std::string>();

    if(action == "apply"){
        if(!config.count("colorscheme")){
            std::cerr << "No colorscheme specified, exiting now" << std::endl;
            exit(1);
        }

        applyColorschemeToImage(inputPath, config["colorscheme"].as<std::string>(), outputPath, config["show"].as<bool>());
    }
    else if(action == "extract"){
        extractColorschemeFromImage(inputPath, config["length"].as<unsigned int>(), true, outputPath);
    }
    else if(action == "blur"){
        blurImage(inputPath, config["blur_amount"].as<unsigned int>(), outputPath, config["show"].as<bool>());
    }
    else {
        std::cerr << "action: " << action << "not recognized" << std::endl;
    }
    return 0;
}
