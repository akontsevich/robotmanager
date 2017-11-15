#include "robotsmanager.h"

int RobotsManager::addRobot(IRobot *rob) noexcept
{
    if(set_.find(rob) == set_.end() && dynamic_cast<IRobot*>(rob)) {
        robots_[index_] = std::unique_ptr<RobotState>(new RobotState(rob));
        commands_[index_] = CommandsQueue();    // add empty command queue for the robot
        set_.emplace(rob);                      // add robot to the set
        return index_++;
    } else {
        return -1;
    }
}

void RobotsManager::removeRobot(int index) noexcept
{
    if(robots_.find(index) != robots_.end()) {
        IRobot *rob = robots_[index].get();
        set_.erase(rob);
        robots_.erase(index);
        commands_.erase(index);
    }
}

const CommandsQueue & RobotsManager::getRobotCommands(int index) noexcept(false)
{
    if(robots_.find(index) != robots_.end()) {
        return commands_[index];
    } else {
        throw new std::out_of_range("Index out of range error: no such robot!");
    }
}

void RobotsManager::sendCommand(int index, CommandType type, double value) noexcept(false)
{
    if(robots_.find(index) == robots_.end())
        throw new std::out_of_range("Index out of range error: no such robot!");

    switch (type) {
    case CommandType::Move:
        robots_[index]->Move(value);
        break;
    case CommandType::Turn:
        robots_[index]->Turn(value);
        break;
    case CommandType::Beep:
        robots_[index]->Beep();
        break;
    }
    commands_[index].push_back(Command(type, value));
}

void RobotsManager::sendCommand(int index, const CommandsQueue & queue) noexcept(false)
{
    for(Command command : queue)
        sendCommand(index, command.first, command.second);
}
