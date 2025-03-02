cmake_minimum_required(VERSION 3.10)
project(EmotionDetector)

find_package(OpenCV REQUIRED)

include_directories(include)

add_executable(Neural-Network 
    src/main.cpp 
    src/EmotionDetector.cpp 
    src/Logger.cpp
)

target_link_libraries(Neural-Network ${OpenCV_LIBS})
