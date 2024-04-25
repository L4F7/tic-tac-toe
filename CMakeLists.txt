cmake_minimum_required(VERSION 3.20)
project(Tic-Tac-Toe)

# Specify the include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add your source files
set(SOURCES
    src/main.cpp
    src/board.cpp
    src/bot.cpp
    src/game.cpp
    src/interface.cpp
    src/move.cpp
)

# Create executable from sources
add_executable(tic-tac-toe ${SOURCES})

# Link against the ncurses library
target_link_libraries(tic-tac-toe PRIVATE ncursesw)