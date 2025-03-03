#include <iostream>
#include <opencv2/opencv.hpp>

void detectEmotion(cv::Mat& frame) {
    cv::CascadeClassifier faceCascade;
    faceCascade.load("haarcascade_frontalface_default.xml");

    std::vector<cv::Rect> faces;
    cv::Mat gray;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    faceCascade.detectMultiScale(gray, faces);

    for (const auto& face : faces) {
        cv::rectangle(frame, face, cv::Scalar(255, 0, 0), 2);
        cv::putText(frame, "Happy", cv::Point(face.x, face.y - 10),
                    cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 255, 0), 2);
    }
}

int main() {
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) return -1;

    while (true) {
        cv::Mat frame;
        cap >> frame;
        detectEmotion(frame);

        cv::imshow("Emotion Detector", frame);
        if (cv::waitKey(10) == 'q') break;
    }

    return 0;
}
