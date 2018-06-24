#include "queen_attack.h"
#include <stdlib.h>

int valid(position_t queen) {
    return 0<=queen.row && queen.row<8 && 0<=queen.column && queen.column<8;
}

attack_status_t can_attack(position_t queen_1, position_t queen_2) {
    int row_diff = abs(queen_1.row - queen_2.row);
    int column_diff = abs(queen_1.column - queen_2.column);
    if((row_diff == 0 && column_diff == 0) || !valid(queen_1) || !valid(queen_2))
        return INVALID_POSITION;
    if(row_diff == 0 || column_diff == 0 || row_diff == column_diff)
        return CAN_ATTACK;
    else
        return CAN_NOT_ATTACK;
}
