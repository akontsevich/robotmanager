#include <gtest/gtest.h>
#include <cmath>

#include "robotsmanager.h"
#include "robot.h"

TEST(RobotManagerTest, AddRobotTest) {
    Robot *rob = new Robot();
    RobotsManager manager;
    EXPECT_EQ(manager.count(), 0);
    EXPECT_NE(manager.addRobot(rob), -1);
    EXPECT_EQ(manager.count(), 1);
}

TEST(RobotManagerTest, TestNoThrow) {
    RobotsManager manager;
    EXPECT_NO_THROW(manager.addRobot(0));
    EXPECT_NO_THROW(manager.addRobot((IRobot*)12874847));
    EXPECT_NO_THROW(manager.removeRobot(-1));
}

TEST(RobotManagerTest, TestCorrectMove) {
    Robot *rob = new Robot();
    RobotsManager manager;
    int id = manager.addRobot(rob);
    manager.sendCommand(id, CommandType::Move, 123);
    EXPECT_DOUBLE_EQ(manager.robotState(id)->x(), 123);
}

TEST(RobotManagerTest, TestCommandQueue) {
    // Create robots
    Robot *rob1 = new Robot();
    Robot *rob2 = new Robot();
    RobotsManager manager;
    int id1 = manager.addRobot(rob1);
    int id2 = manager.addRobot(rob2);

    // Send commands to first robot
    manager.sendCommand(id1, CommandType::Turn, M_PI_4);
    manager.sendCommand(id1, CommandType::Move, 120);
    manager.sendCommand(id1, CommandType::Beep);
    manager.sendCommand(id1, CommandType::Turn, M_PI_4);
    manager.sendCommand(id1, CommandType::Move, 120);
    manager.sendCommand(id1, CommandType::Beep);
    manager.sendCommand(id1, CommandType::Turn, M_PI_4);
    manager.sendCommand(id1, CommandType::Move, 120);
    manager.sendCommand(id1, CommandType::Beep);
    manager.sendCommand(id1, CommandType::Turn, M_PI_4);
    manager.sendCommand(id1, CommandType::Move, 120);
    manager.sendCommand(id1, CommandType::Beep);

    // Repeat same commands to 2nd
    manager.sendCommand(id2, manager.getRobotCommands(id1));

    // Check robots states
    EXPECT_DOUBLE_EQ(manager.robotState(id1)->x(), manager.robotState(id2)->x());
    EXPECT_DOUBLE_EQ(manager.robotState(id1)->y(), manager.robotState(id2)->y());
    EXPECT_DOUBLE_EQ(manager.robotState(id1)->angle(), manager.robotState(id2)->angle());
}
