#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <iostream>
#include <fstream>
#include <ncurses.h>
#include <string>
#include <vector>

class FileManager {
public:
    FileManager();
    ~FileManager();

    std::vector<std::pair<int, int>> readExecutionTimes(std::string fileName);
    int writeExecutionTimes(std::string fileName, std::vector<std::string> lines);
    void clearExecutionTimes(std::string fileName);
};

#endif // FILE_MANAGER_H
