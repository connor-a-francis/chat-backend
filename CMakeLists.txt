cmake_minimum_required(VERSION 3.10)
project(ChatBackend)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

###########################
#                         #
#        LIBRARIES        #
#                         #
###########################
###########################
#         SQLITE          #
###########################
find_path(SQLITE3_INCLUDE_DIR sqlite3.h)
find_library(SQLITE3_LIBRARY sqlite3)

if(NOT SQLITE3_INCLUDE_DIR)
    message(FATAL_ERROR "SQLite3 include directory not found")
endif()

if(NOT SQLITE3_LIBRARY)
    message(FATAL_ERROR "SQLite3 library not found")
endif()
###########################
#        SUBMODULES       #
###########################
set(CROW_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/crow/include)
set(ASIO_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/asio/asio/include)
###########################
#         LIBRARY         #
###########################
set(LIBRARY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/lib)
include_directories(${CROW_INCLUDE_DIR} ${ASIO_INCLUDE_DIR} ${LIBRARY_INCLUDE_DIR} ${SQLITE3_INCLUDE_DIR})
set(SOURCES
    main.cpp
    ${LIBRARY_INCLUDE_DIR}/app.cpp
    ${LIBRARY_INCLUDE_DIR}/database.cpp
    ${LIBRARY_INCLUDE_DIR}/http_handlers.cpp
    ${LIBRARY_INCLUDE_DIR}/websocket_handlers.cpp
)
###########################
#                         #
#          BUILD          #
#                         #
###########################
add_executable(ChatBackend ${SOURCES})
target_link_libraries(ChatBackend ${SQLITE3_LIBRARY} pthread)
###########################
#                         #
#          TEST           #
#                         #
###########################
###########################
#       TEST FILES        #
###########################
add_executable(tests
    test/api.cc
    ${LIBRARY_INCLUDE_DIR}/app.cpp
    ${LIBRARY_INCLUDE_DIR}/database.cpp
    ${LIBRARY_INCLUDE_DIR}/http_handlers.cpp
    ${LIBRARY_INCLUDE_DIR}/websocket_handlers.cpp
)
###########################
#       GOOGLE TEST       #
###########################
include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
###########################
#       TEST BUILD        #
###########################
target_link_libraries(tests GTest::gtest_main ${SQLITE3_LIBRARY} pthread)
enable_testing()
include(GoogleTest)
gtest_discover_tests(tests)
