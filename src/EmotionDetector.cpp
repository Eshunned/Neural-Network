#include "EmotionDetector.h"

EmotionDetector::EmotionDetector(const std::string& modelPath, const std::string& cascadePath) {
    logger.log("Initializing EmotionDetector...");

    model = cv::dnn::readNetFromONNX(modelPath);
    if (!faceCascade.load(cascadePath)) {
        logger.log("Error loading face cascade.");
        exit(EXIT_FAILURE);
    }

    emotions = { "Angry", "Disgust", "Fear", "Happy", "Neutral", "Sad", "Surprise" };
    logger.log("EmotionDetector initialized successfully.");
}

void EmotionDetector::preprocessImage(cv::Mat& img) {
    logger.log("Preprocessing image...");
    cv::equalizeHist(img, img);
    cv::GaussianBlur(img, img, cv::Size(3, 3), 0);
    logger.log("Image preprocessing complete.");
}

std::string EmotionDetector::predictEmotion(cv::Mat& face) {
    preprocessImage(face);

    cv::Mat blob = cv::dnn::blobFromImage(face, 1.0 / 255, cv::Size(48, 48), cv::Scalar(0), true, false);
    model.setInput(blob);
    cv::Mat output = model.forward();

    cv::Point maxLoc;
    double maxVal;
    minMaxLoc(output, nullptr, &maxVal, nullptr, &maxLoc);

    logger.log("Predicted emotion: " + emotions[maxLoc.x]);
    return emotions[maxLoc.x];
}

void EmotionDetector::processFrame(cv::Mat& frame) {
    std::vector<cv::Rect> faces;
    cv::Mat gray;

    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    faceCascade.detectMultiScale(gray, faces, 1.3, 5, 0, cv::Size(48, 48));

    if (faces.empty()) {
        logger.log("No faces detected.");
    }

    for (const auto& face : faces) {
        cv::Mat faceROI = gray(face);
        std::string emotion = predictEmotion(faceROI);

        cv::rectangle(frame, face, cv::Scalar(255, 0, 0), 2);
        cv::putText(frame, emotion, cv::Point(face.x, face.y - 10), 
                    cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 255, 0), 2);
    }
}

void EmotionDetector::run() {
    logger.log("Starting video capture...");
    cv::VideoCapture cap(0);

    if (!cap.isOpened()) {
        logger.log("Error opening webcam.");
        return;
    }

    while (true) {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty()) break;

        processFrame(frame);
        cv::imshow("Emotion Detector", frame);

        int key = cv::waitKey(10);
        if (key == 'q') break;
    }

    cap.release();
    cv::destroyAllWindows();
    logger.log("Video capture ended.");
}
