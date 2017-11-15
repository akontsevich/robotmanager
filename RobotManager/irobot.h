#ifndef IROBOT_H
#define IROBOT_H

/**
 * @brief The IRobot class - abstract robot interface defined in 3rd party SDK
 */
class IRobot
{
public:
    virtual void Move(double distance) = 0;
    virtual void Turn(double angle) = 0;
    virtual void Beep() = 0;
};

#endif // IROBOT_H
