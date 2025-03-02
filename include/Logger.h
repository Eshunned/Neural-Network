#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

class Logger {
private:
    std::ofstream logFile;
public:
    Logger();
    ~Logger();
    void log(const std::string& message);
};

#endif // LOGGER_H
