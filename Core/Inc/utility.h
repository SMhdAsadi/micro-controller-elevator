#ifndef MICRO_CONTROLLER_ELEVATOR_MINI_PROJECT_UTILITY_H
#define MICRO_CONTROLLER_ELEVATOR_MINI_PROJECT_UTILITY_H

#include "types.h"

SubmitStatus add_to_floor_queue(int floor);
int peek_from_floor_queue();
int dequeue_from_floor_queue();
void parse_command(char *command);

#endif //MICRO_CONTROLLER_ELEVATOR_MINI_PROJECT_UTILITY_H
