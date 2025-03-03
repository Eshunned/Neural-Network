#ifndef FACE_DETECTOR_H
#define FACE_DETECTOR_H

#include <vector>
#include <iostream>

class FaceDetector {
public:
    std::vector<std::vector<int>> detectFaces(const std::vector<std::vector<int>>& image) {
        std::vector<std::vector<int>> detectedFaces;

        for (size_t i = 0; i < image.size() - 10; i++) {
            for (size_t j = 0; j < image[i].size() - 10; j++) {
                int sum = 0;
                for (size_t x = 0; x < 10; x++) {
                    for (size_t y = 0; y < 10; y++) {
                        sum += image[i + x][j + y];
                    }
                }
                if (sum > 200) { // Simple thresholding
                    detectedFaces.push_back({(int)i, (int)j, 10, 10});
                }
            }
        }
        return detectedFaces;
    }
};

#endif
