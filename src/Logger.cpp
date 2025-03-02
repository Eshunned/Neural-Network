#include "Logger.h"

Logger::Logger() {
    logFile.open("log.txt", std::ios::app);
    if (logFile.is_open()) {
        log("Logger initialized.");
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        log("Logger shutting down.");
        logFile.close();
    }
}

void Logger::log(const std::string& message) {
    if (logFile.is_open()) {
        std::time_t now = std::time(nullptr);
        logFile << "[" << std::ctime(&now) << "] " << message << std::endl;
    }
}
