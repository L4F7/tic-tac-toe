cmake_minimum_required(VERSION 3.10)
project(MyCppProject)

# Specify the include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add your source files
set(SOURCES
    src/main.cpp
    src/board.cpp
    src/bot.cpp
)

# Create executable from sources
add_executable(my_cpp_executable ${SOURCES})
