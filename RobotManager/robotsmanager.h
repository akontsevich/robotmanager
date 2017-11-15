#ifndef ROBOTSMANAGER_H
#define ROBOTSMANAGER_H

#include <functional>
#include <map>
#include <set>
#include <vector>
#include <exception>
#include <memory>

#include "robotstate.h"

enum class CommandType
{
    Move,
    Turn,
    Beep
};

typedef std::pair<CommandType, double> Command;
typedef std::vector<Command> CommandsQueue;
typedef std::map<int, CommandsQueue> CommandsMap;

/**
 * @brief The RobotsManager class - Facade design pattern class
 * where subsytem classes know nothing about facade. Class addresses clients
 * commands to subsytem classes - IRobots classes.
 */
class RobotsManager
{
public:
    RobotsManager() = default;

    /// @brief add robot to control
    int addRobot(IRobot *rob) noexcept;
    /// @brief remove robot from control
    void removeRobot(int index) noexcept;
    /**
     * @brief sendCommand sends command to the robot with given index
     * @param index robot index
     * @param type command type
     * @param double value for move and turn commands
     */
    void sendCommand(int index, CommandType type, double value = 0);
    /**
     * @brief sendCommand sends commands queue to the robot with given index
     * @param index robot index
     * @param queue commands queue
     */
    void sendCommand(int index, const CommandsQueue & queue);
    /// @brief Gets robot state (position and direction)
    RobotState const * robotState(const int &id) { return robots_[id].get(); }
    /// @brief Returns commands queue for robot of given index
    const CommandsQueue & getRobotCommands(int index) noexcept(false);
    /// @brief Managed robots count
    const size_t count() const { return robots_.size(); }

private:
    std::map<int, std::unique_ptr<RobotState>> robots_;
    std::set<IRobot*> set_;
    CommandsMap commands_;

    int index_ = 0;
};

#endif // ROBOTSMANAGER_H
