#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

void preprocessDataset(const std::string& inputFile) {
    std::ifstream file(inputFile);
    std::string line;
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::vector<double> image;
        int label;
        ss >> label;
        double pixel;
        while (ss >> pixel) image.push_back(pixel / 255.0); // Normalize
    }

    std::cout << "Dataset Preprocessing Complete!\n";
}

int main() {
    preprocessDataset("../dataset/fer2013.csv");
    return 0;
}
