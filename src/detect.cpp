#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm> // Required for std::max_element
#include <chrono>
#include <thread>
#include "face_detector.h"
#include "neural_network.h"

#ifdef USE_WEBCAM
    #include <opencv2/opencv.hpp>  // Only used if running locally with OpenCV
#endif

// Simulate camera capture for Codespaces
void captureImage(std::vector<std::vector<int>>& image) {
    for (int i = 0; i < 48; i++) {
        std::vector<int> row;
        for (int j = 0; j < 48; j++) {
            row.push_back(rand() % 256); // Random grayscale pixels
        }
        image.push_back(row);
    }
}

int main() {
    FaceDetector detector;
    NeuralNetwork model(48 * 48, 7);
    model.loadWeights("../models/weights.txt");

    std::vector<std::string> emotionLabels = {
        "Angry", "Disgust", "Fear", "Happy", "Neutral", "Sad", "Surprise"
    };

    while (true) {
        std::vector<std::vector<int>> frame;

        #ifdef USE_WEBCAM
            // Capture from real webcam (only if running locally)
            cv::VideoCapture cap(0);
            if (!cap.isOpened()) {
                std::cerr << "Error: Cannot open webcam!\n";
                return -1;
            }

            cv::Mat img;
            cap >> img; // Capture frame

            // Convert image to grayscale manually
            std::vector<std::vector<int>> grayscaleImage(48, std::vector<int>(48, 0));
            for (int i = 0; i < 48; i++) {
                for (int j = 0; j < 48; j++) {
                    int pixel = (img.at<cv::Vec3b>(i, j)[0] + img.at<cv::Vec3b>(i, j)[1] + img.at<cv::Vec3b>(i, j)[2]) / 3;
                    grayscaleImage[i][j] = pixel;
                }
            }
            frame = grayscaleImage;
        #else
            // Simulate webcam image (for Codespaces)
            captureImage(frame);
        #endif

        std::vector<std::vector<int>> faces = detector.detectFaces(frame);

        for (const auto& face : faces) {
            std::vector<double> input;
            for (int i = face[0]; i < face[0] + face[2]; ++i) {
                for (int j = face[1]; j < face[1] + face[3]; ++j) {
                    input.push_back(frame[i][j] / 255.0); // Normalize
                }
            }

            auto result = model.forward(input);
            int emotionIndex = std::distance(result.begin(), std::max_element(result.begin(), result.end()));

            std::cout << "Detected Emotion: " << emotionLabels[emotionIndex] << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Reduce CPU usage
    }

    return 0;
}
