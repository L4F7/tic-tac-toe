cmake_minimum_required(VERSION 3.20)
project(Tic-Tac-Toe)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

# Fetch the Google Test package
include(FetchContent)
FetchContent_Declare(gtest
    QUIET
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.11.0 # specify the version you need
)

# Enable testing
enable_testing()

# Specify the include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add your game source files
set(SOURCES
    src/main.cpp
    src/board.cpp
    src/bot.cpp
    src/game.cpp
    src/interface.cpp
    src/move.cpp
)

# Add your test source files
set(TEST_SOURCES
    test/test.cpp
    src/board.cpp
    src/bot.cpp
    src/game.cpp
    src/interface.cpp
    src/move.cpp
)

# Create game executable
add_executable(tic-tac-toe ${SOURCES})

# Link against the ncurses library
target_link_libraries(tic-tac-toe PRIVATE ncursesw)

# configure build of googletest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)

# Create test executable
add_executable(unit_tests ${TEST_SOURCES})

# Link against the Google Test library and ncurses
target_link_libraries(unit_tests PRIVATE ncurses gtest_main)

# Automatic discovery of unit tests
include(GoogleTest)
gtest_discover_tests(unit_tests
  PROPERTIES
    LABELS "unit"
  DISCOVERY_TIMEOUT  # how long to wait (in seconds) before crashing
    240
  )
  