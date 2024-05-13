#include "fileManager.h"

FileManager::FileManager() {}

FileManager::~FileManager() {}

/**
 * @brief Reads execution times from a file and returns them as a vector of pairs. 
 */
std::vector<std::pair<int, int>> FileManager::readExecutionTimes(std::string fileName) {

    std::vector<std::string> lines;
    std::vector<std::pair<int, int>> executionTimes;

    try {
        std::ifstream file(fileName);

        // Check if the file is open
        if (!file.is_open()) {
            return {};
        }
        std::string line;
        std::getline(file, line); // Skip the first line
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        file.close();

        // Parse the lines and store them as pairs
        for (const std::string& line : lines) {
            std::string mode = line.substr(0, line.find(","));
            std::string time = line.substr(line.find(",") + 1);
            executionTimes.push_back(std::make_pair(std::stoi(mode), std::stoi(time)));
        }

        return executionTimes;

    } catch (std::exception e) {
        return {};
    }
}

/**
 * @brief Writes execution times to a file.
 */
int FileManager::writeExecutionTimes(std::string fileName, std::vector<std::string> lines) {
    try {
        std::ofstream file(fileName, std::ios::app); // Open file in append mode
        if (!file.is_open()) {
            file.open(fileName, std::ios::out); // Create the file if it doesn't exist
        }
        for (const std::string& line : lines) {
            file << line << std::endl;
        }
        file.close();
        return 0;
    } catch (const std::exception& e) {
        return 1;
    }
}

/**
 * @brief Clears execution times from a file.
 */
void FileManager::clearExecutionTimes(std::string fileName) {
    try{
        // Clear the file by opening it in out mode
        std::ofstream file(fileName, std::ios::out);
        file.close();
    } catch (const std::exception& e) {
        return;
    }
}