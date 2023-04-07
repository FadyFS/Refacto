cmake_minimum_required(VERSION 3.8)

add_executable(${PROJECT_NAME} main.cpp Game.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE .)