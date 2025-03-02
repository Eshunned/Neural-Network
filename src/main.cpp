#include "EmotionDetector.h"

int main() {
    EmotionDetector detector("models/emotion_model.onnx", "models/haarcascade_frontalface_default.xml");
    detector.run();
    return 0;
}
cv::dnn::Net model;
try {
    model = cv::dnn::readNetFromONNX(modelPath);
} catch (const cv::Exception& e) {
    std::cerr << "Error loading ONNX model: " << e.what() << std::endl;
    exit(EXIT_FAILURE);
}
