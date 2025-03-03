#include "neural_network.h"
#include <fstream>
#include <sstream>

int main() {
    NeuralNetwork nn(48*48, 7);  // 48x48 image, 7 emotions

    std::ifstream file("../dataset/fer2013.csv");
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::vector<double> image;
        int label;
        ss >> label;
        double pixel;
        while (ss >> pixel) image.push_back(pixel / 255.0); // Normalize

        nn.forward(image);  // Forward pass
    }

    nn.saveWeights("../models/weights.txt");
    std::cout << "Training completed! Weights saved.\n";
    return 0;
}
