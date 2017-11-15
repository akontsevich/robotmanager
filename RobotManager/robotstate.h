#ifndef ROBOTSTATE_H
#define ROBOTSTATE_H

#include <cmath>
#include "irobot.h"

/**
 * @brief The RobotState class - Adapter (Wrapper) pattern class for the IRobot
*/
class RobotState : public IRobot
{
public:
    /**
     * @brief RobotState constructor
     * @param robot controlled robot
     */
    RobotState(IRobot *robot) : robot_(robot) {}
    /**
     * @brief RobotState
     * @param robot controlled robot
     * @param x horizontal coordinate
     * @param y vertical coordinate
     * @param angle move direction
     */
    RobotState(IRobot *robot, double x, double y, double angle)
        : robot_(robot)
        , x_(x)
        , y_(y)
        , angle_(angle) {}

    // Getters
    double x() const { return x_; }
    double y() const { return y_; }
    double angle() const { return angle_; }

protected:
    // Classes moved to protected section to be invisible for RobotsManager consumers
    friend class RobotsManager;

    void Move(double distance) override {
        robot_->Move(distance);         // Move robot
        x_ += distance * cos(angle_);   // Keep robot coordinates
        y_ += distance * sin(angle_);
    }
    void Turn(double angle) override {
        robot_->Turn(angle);    // Turn robot
        angle_ += angle;        // Keep robot direction
    }
    void Beep() override { robot_->Beep(); }

private:
    IRobot *robot_;
    double x_ = 0, y_ = 0, angle_ = 0;
};

#endif // ROBOTSTATE_H
