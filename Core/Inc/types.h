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

typedef enum submit_status {
  SUBMIT_SUCCESS, // successfully added user input to floor queue
  SUBMIT_QUEUE_FULL, // queue is full
  SUBMIT_WRONG_FLOOR, // floor number is wrong, should be between 0 and max floor
  SUBMIT_DUPLICATE_FLOOR, // this floor is already in queue, no need to add
  SUBMIT_CURRENT_FLOOR, // elevator is already in this floor
  SUBMIT_ADMIN_MODE
} SubmitStatus;

typedef enum login_status {LOGIN_CORRECT_PASSWORD, LOGIN_WRONG_PASSWORD, LOGIN_QUEUE_NOT_EMPTY} LoginStatus;
typedef enum set_max_level_status {MAX_LEVEL_SUCCESS, MAX_LEVEL_NOT_ADMIN_MODE, MAX_LEVEL_WRONG_INPUT} MaxLevelStatus;
typedef enum set_level_status {LEVEL_SUCCESS, LEVEL_NOT_ADMIN_MODE, LEVEL_WRONG_INPUT, LEVEL_OUT_OF_RANGE} LevelStatus;
typedef enum set_wait_status {WAIT_SUCCESS, WAIT_NOT_ADMIN_MODE, WAIT_WRONG_INPUT, WAIT_OUT_OF_RANGE} WaitStatus;
typedef enum set_led_status {LED_SUCCESS, LED_NOT_ADMIN_MODE, LED_WRONG_INPUT} LedStatus;
typedef enum test_status {TEST_SUCCESS, TEST_NOT_ADMIN_MODE, TEST_WRONG_INPUT, TEST_OUT_OF_RANGE} TestStatus;

#endif //MICRO_CONTROLLER_ELEVATOR_MINI_PROJECT_TYPES_H
