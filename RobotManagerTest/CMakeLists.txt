project(robotmanagertest)

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

enable_testing()
find_package(GTest REQUIRED)
include_directories(
    ${GTEST_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}
    ../RobotManager)

find_package(Threads REQUIRED)

set(RobotManagerTest_SRCS
    main.cpp
    RobotManagerTest.cpp)

add_library(robotmanager STATIC ../RobotManager/robotsmanager.cpp)

add_executable(robotmanagertest ${RobotManagerTest_SRCS})
target_link_libraries(robotmanagertest robotmanager
    ${GTEST_LIBRARIES}
    Threads::Threads)

add_test(AllTests robotmanagertest)
