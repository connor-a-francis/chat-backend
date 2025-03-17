cmake_minimum_required(VERSION 3.10)
project(ChatBackend)

set(CMAKE_CXX_STANDARD 17)

set(CROW_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/crow/include)
set(ASIO_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/asio/asio/include)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CROW_INCLUDE_DIR} ${ASIO_INCLUDE_DIR})

# Manually find SQLite3
find_path(SQLITE3_INCLUDE_DIR sqlite3.h)
find_library(SQLITE3_LIBRARY sqlite3)

if(NOT SQLITE3_INCLUDE_DIR)
    message(FATAL_ERROR "SQLite3 include directory not found")
endif()

if(NOT SQLITE3_LIBRARY)
    message(FATAL_ERROR "SQLite3 library not found")
endif()

include_directories(${SQLITE3_INCLUDE_DIR})

set(SOURCES
    main.cpp
)

add_executable(ChatBackend ${SOURCES})

# Link against the SQLite3 library
target_link_libraries(ChatBackend ${SQLITE3_LIBRARY} pthread)
