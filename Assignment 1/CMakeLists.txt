cmake_minimum_required(VERSION 3.14)
project(Assignment_1 C)

set(CMAKE_C_STANDARD 11)

add_executable(Assignment_1 main.c)

find_package(OpenMP REQUIRED)
target_link_libraries(${PROJECT_NAME} ${OpenMP_C_LIBRARIES})