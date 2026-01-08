#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <cxxopts.hpp>
#include <yaml-cpp/emittermanip.h>
#include <yaml-cpp/yaml.h>
#include <fstream>

#include "colorscheme.hpp"
#include "formatConverter.hpp"
#include "effects.hpp"

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

int main(int argc, char** argv) {
    cxxopts::Options options("tintr", "colorscheme utilities");
    options.add_options()
        ("a,apply", "Apply the specified colorscheme to the input image", cxxopts::value<bool>())
        ("b,blur", "Blur the input image", cxxopts::value<bool>())
        ("ba,blur_amount", "Amount of blurness", cxxopts::value<unsigned int>()->default_value("1"))
        ("e,extract", "Extract the colorscheme from the input image", cxxopts::value<bool>())
        ("i,input", "path to the input image", cxxopts::value<std::string>())
        ("c,colorscheme", "path to the colorscheme yaml file", cxxopts::value<std::string>())
        ("l,length", "number of colors to extract from the image", cxxopts::value<unsigned int>()->default_value("16"))
        ("oi,output_image", "path in which the final image will be created", cxxopts::value<std::string>()->default_value("output.png"))
        ("oc,output_colorscheme", "path in which the final colorscheme yaml file will be created", cxxopts::value<std::string>())
        ("s,show", "show results in a window", cxxopts::value<bool>())
        ("h,help", "print usage");

    auto config = options.parse(argc, argv);

    if (config.count("help") || (!config["apply"].as<bool>() && !config["extract"].as<bool>()) && !config["blur"].as<bool>()){
      std::cout << options.help() << std::endl;
      exit(0);
    }

    std::string imagePath = config["input"].as<std::string>();
    int newWidth = 1366; 
    int newHeight = 768; 

    if(config["apply"].as<bool>()){
        if(!config.count("input")){
            std::cerr << "No input image specified, exiting now" << std::endl;
            exit(1);
        }
        if(!config.count("colorscheme")){
            std::cerr << "No colorscheme specified, exiting now" << std::endl;
            exit(1);
        }
        Colorscheme colorscheme(config["colorscheme"].as<std::string>());
        std::cout << "opening " << imagePath << std::endl;
        cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);
        colorscheme.applyToImage(image, image);
        std::cout << "saving image in " << config["output_image"].as<std::string>() << std::endl;
        cv::imwrite(config["output_image"].as<std::string>(), image);
        if(config["show"].as<bool>()){
            cv::resize(image, image, cv::Size(newWidth, newHeight), cv::INTER_LINEAR);
            cv::imshow(imagePath, image);
            cv::waitKey(0);
            cv::destroyWindow(imagePath);
        }
    }

    if(config["extract"].as<bool>()){
        if(!config.count("input")){
            std::cerr << "No input image specified, exiting now" << std::endl;
            exit(1);
        }
        std::cout << "opening image " << imagePath << std::endl;
        cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);
        Colorscheme colorscheme(&image, config["length"].as<unsigned int>());
        std::vector<cv::Vec3b> palette = colorscheme.getColorscheme();
        if(!config.count("output_colorscheme")){
            std::cout << "colorscheme:" << "\n";
            std::cout << "\t[" << "\n";
            for(unsigned int i=0; i<config["length"].as<unsigned int>(); i++){
                std::cout << "\t\t\"" << FormatConverter::BGRtoHEX(palette.at(i)) << "\"," << "\n";
            }
            std::cout << "\t]" << "\n";
            std::cout << "\n";
        } else {
            std::cout << "saving colorscheme to file " << config["output_colorscheme"].as<std::string>() << std::endl; 
            saveColorschemeToFile(config["output_colorscheme"].as<std::string>(), palette);
        }

    }

    if(config["blur"].as<bool>()){
        if(!config.count("input")){
            std::cerr << "No input image specified, exiting now" << std::endl;
            exit(1);
        }

        std::cout << "opening image " << imagePath << std::endl;
        cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);
        cv::Mat blurred;

        Effects::blur(image, blurred, config["blur_amount"].as<unsigned int>());
        cv::imwrite(config["output_image"].as<std::string>(), blurred);

        if(config["show"].as<bool>()){
            cv::resize(blurred, blurred, cv::Size(newWidth, newHeight), cv::INTER_LINEAR);
            cv::imshow(imagePath, blurred);
            cv::waitKey(0);
            cv::destroyWindow(imagePath);
        }
    }
    return 0;
}
