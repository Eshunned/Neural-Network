#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>

class NeuralNetwork {
private:
    std::vector<std::vector<double>> weights;
    std::vector<double> biases;

public:
    NeuralNetwork(int inputSize, int outputSize) {
        weights.resize(outputSize, std::vector<double>(inputSize, 0.1));
        biases.resize(outputSize, 0.1);
    }

    std::vector<double> forward(const std::vector<double>& input) {
        std::vector<double> output(weights.size());
        for (size_t i = 0; i < weights.size(); ++i) {
            double sum = biases[i];
            for (size_t j = 0; j < input.size(); ++j) {
                sum += input[j] * weights[i][j];
            }
            output[i] = 1 / (1 + exp(-sum)); // Sigmoid activation
        }
        return output;
    }

    void saveWeights(const std::string& filename) {
        std::ofstream file(filename);
        for (const auto& w : weights) {
            for (double val : w) file << val << " ";
            file << "\n";
        }
        for (double b : biases) file << b << " ";
    }

    void loadWeights(const std::string& filename) {
        std::ifstream file(filename);
        for (auto& w : weights) 
            for (double& val : w) file >> val;
        for (double& b : biases) file >> b;
    }
};

#endif
