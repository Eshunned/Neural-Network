#ifndef EMOTIONDETECTOR_H
#define EMOTIONDETECTOR_H

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "Logger.h"

class EmotionDetector {
private:
    cv::CascadeClassifier faceCascade;
    cv::dnn::Net model;
    std::vector<std::string> emotions;
    Logger logger;

    void preprocessImage(cv::Mat& img);
    std::string predictEmotion(cv::Mat& face);

public:
    EmotionDetector(const std::string& modelPath, const std::string& cascadePath);
    void processFrame(cv::Mat& frame);
    void run();
};

#endif // EMOTIONDETECTOR_H
