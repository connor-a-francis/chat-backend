cmake_minimum_required(VERSION 3.10)

# Set the project name
project(MyCrowApp)

# Set C++ standard to C++17 (Crow requires C++17 or newer)
set(CMAKE_CXX_STANDARD 17)

# Define the path to Crow's include directory
set(CROW_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/crow/include)

# Define the path to ASIO's include directory
set(ASIO_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/asio/asio/include)

# Add Crow and ASIO include directories
include_directories(${CROW_INCLUDE_DIR} ${ASIO_INCLUDE_DIR})

find_package(SQLite3 REQUIRED)

# Your source files
set(SOURCES
    main.cpp
)

# Create the executable from your source
add_executable(MyCrowApp ${SOURCES})

# Link pthread (Crow may need it for threading)
target_link_libraries(MyCrowApp SQLite3 pthread)

# If Crow is a submodule, ensure that it's added as a subdirectory
# add_subdirectory(external/crow)

