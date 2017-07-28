#include "robot_simulator.h"

RobotGridStatus_t robot_init(void) {
    return robot_init_with_position(Heading_North, 0, 0);
}

RobotGridStatus_t robot_init_with_position(int bearing, int x, int y) {
    RobotCoordinates_t grid = { .x_position = x, .y_position = y };
    RobotGridStatus_t status = { 
        .grid = grid, 
        .bearing = 0 <= bearing && bearing < Heading_Max ? bearing : 0};
    return status;
}

void robot_turn_right(RobotGridStatus_t * robot) {
    robot->bearing = (robot->bearing + 1) % Heading_Max;
}

void robot_turn_left(RobotGridStatus_t * robot) {
    robot->bearing = (robot->bearing - 1 + Heading_Max) % Heading_Max;
}

void robot_advance(RobotGridStatus_t * robot) {
    switch(robot->bearing) {
        case Heading_North:
            robot->grid.y_position++;
            return;
        case Heading_South:
            robot->grid.y_position--;
            return;
        case Heading_East:
            robot->grid.x_position++;
            return;
        case Heading_West:
            robot->grid.x_position--;
            return;
        default:
            return;
    }
}

void robot_simulator(RobotGridStatus_t * robot, const char *commands) {
    for(char *c = (char *)commands; *c; c++) {
        switch(*c) {
            case Command_Left:
                robot_turn_left(robot);
                break;
            case Command_Right:
                robot_turn_right(robot);
                break;
            case Command_Advance:
                robot_advance(robot);
                break;
        }
    }
}
