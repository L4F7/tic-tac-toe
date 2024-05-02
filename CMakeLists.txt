cmake_minimum_required(VERSION 3.20)
project(Tic-Tac-Toe)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

# Specify the include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add your game source files
set(SOURCES
    src/main.cpp
    src/board.cpp
    src/bot.cpp
    src/fileManager.cpp
    src/game.cpp
    src/interface.cpp
    src/move.cpp
)

# Create game executable
add_executable(tic-tac-toe ${SOURCES})

# Link against the ncurses library
target_link_libraries(tic-tac-toe PRIVATE ncursesw)