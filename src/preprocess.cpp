#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <opencv2/opencv.hpp>

const int IMG_SIZE = 48;

// Function to parse CSV and convert to images
void loadDataset(const std::string& filename, std::vector<std::pair<cv::Mat, int>>& data) {
    std::ifstream file(filename);
    std::string line, pixelValues;
    int label;

    if (!file.is_open()) {
        std::cerr << "Error opening dataset file!\n";
        return;
    }

    std::getline(file, line); // Skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::getline(ss, pixelValues, ',');
        label = std::stoi(pixelValues);

        std::vector<uint8_t> pixels;
        while (std::getline(ss, pixelValues, ' ')) {
            pixels.push_back(static_cast<uint8_t>(std::stoi(pixelValues)));
        }

        cv::Mat img(IMG_SIZE, IMG_SIZE, CV_8UC1, pixels.data());
        data.push_back({img, label});
    }
}

int main() {
    std::vector<std::pair<cv::Mat, int>> dataset;
    loadDataset("dataset/fer2013.csv", dataset);
    
    std::cout << "Dataset Loaded! Total samples: " << dataset.size() << std::endl;
    return 0;
}
