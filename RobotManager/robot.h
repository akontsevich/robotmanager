#ifndef ROBOT_H
#define ROBOT_H

#include "irobot.h"

/**
 * @brief The Robot class basic mockup class
 */
class Robot : public IRobot
{
public:
    // Send commands to robot (perform some hardware activity)
    virtual void Move(double /*distance*/) override { }
    virtual void Turn(double /*angle*/) override { }
    virtual void Beep() override { }
};

#endif // ROBOT_H
