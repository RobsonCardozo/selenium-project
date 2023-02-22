cmake_minimum_required(VERSION 3.10)
project(selenium-project)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the required libraries
find_package(CURL REQUIRED)
find_package(dotenv-cpp REQUIRED)

# Add the include directories for the libraries
include_directories(${CURL_INCLUDE_DIR})
include_directories(${dotenv-cpp_INCLUDE_DIRS})

# Set the source files for the executable
set(SOURCES src/main.cpp)

# Add the executable target
add_executable(selenium-project ${SOURCES})

# Link the required libraries
target_link_libraries(selenium-project ${CURL_LIBRARIES})
target_link_libraries(selenium-project dotenv-cpp::dotenv-cpp)
