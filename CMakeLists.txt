cmake_minimum_required(VERSION 2.8)

project(Module1)

file(GLOB Module1_src
    "*.h"
    "*.cpp"
    "*.hpp"
)

add_executable(${PROJECT_NAME} ${Module1_src})
