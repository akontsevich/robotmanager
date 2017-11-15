cmake_minimum_required(VERSION 3.0)
project(robotmanager)

#Build the library
add_library(${PROJECT_NAME} STATIC robotsmanager.cpp)
include_directories("${PROJECT_SOURCE_DIR}")

#install(TARGETS robotmanager ARCHIVE DESTINATION bin)
