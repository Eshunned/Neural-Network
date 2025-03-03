#ifndef EMOTION_DETECTOR_H
#define EMOTION_DETECTOR_H

#include "neural_network.h"
#include <opencv2/opencv.hpp>

class EmotionDetector {
private:
    NeuralNetwork model;
    cv::CascadeClassifier faceCascade;
    std::vector<std::string> emotions;

public:
    EmotionDetector() : model(48*48, 7) {
        model.loadWeights("../models/weights.txt");
        faceCascade.load("../haarcascade/haarcascade_frontalface_default.xml");
        emotions = {"Angry", "Disgust", "Fear", "Happy", "Neutral", "Sad", "Surprise"};
    }

    void detectEmotion(cv::Mat& frame);
};

#endif
