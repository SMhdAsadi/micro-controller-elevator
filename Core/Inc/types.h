#ifndef MICRO_CONTROLLER_ELEVATOR_MINI_PROJECT_TYPES_H
#define MICRO_CONTROLLER_ELEVATOR_MINI_PROJECT_TYPES_H

typedef struct {
  int values[10];
  int length;
} Queue;

// ElevatorState.MOVING => there are some selected floors available in queue and elevator is moving between them.
// ElevatorState.IDLE => queue is empty.
// ElevatorState.CONFIG => admin mode; changing elevator config params
typedef enum {MOVING, IDLE, CONFIG} ElevatorState;
typedef enum {LOW, HIGH} AlarmState;

#endif //MICRO_CONTROLLER_ELEVATOR_MINI_PROJECT_TYPES_H
