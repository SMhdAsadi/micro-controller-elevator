#ifndef MICRO_CONTROLLER_ELEVATOR_MINI_PROJECT_TYPES_H
#define MICRO_CONTROLLER_ELEVATOR_MINI_PROJECT_TYPES_H

typedef struct {
  int values[10];
  int length;
} Queue;

// ElevatorState.MOVING => there are some selected floors available in queue and elevator is moving between them.
// ElevatorState.IDLE => queue is empty.
// ElevatorState.CONFIG => admin mode; changing elevator config params
typedef enum {LOW, HIGH} AlarmState;

typedef enum login_status {LOGIN_CORRECT_PASSWORD, LOGIN_WRONG_PASSWORD, LOGIN_QUEUE_NOT_EMPTY} LoginStatus;

#endif //MICRO_CONTROLLER_ELEVATOR_MINI_PROJECT_TYPES_H
