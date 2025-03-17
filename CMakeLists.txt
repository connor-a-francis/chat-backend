cmake_minimum_required(VERSION 3.10)
project(ChatBackend)

set(CMAKE_CXX_STANDARD 17)

set(CROW_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/crow/include)
set(ASIO_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/asio/asio/include)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CROW_INCLUDE_DIR} ${ASIO_INCLUDE_DIR})

find_package(SQLite3 REQUIRED)

set(SOURCES
    main.cpp
)

add_executable(ChatBackend ${SOURCES})
target_link_libraries(ChatBackend SQLite3 pthread)
