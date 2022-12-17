#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "types.h"
#include "stm32f3xx.h"

extern Queue floor_queue;
extern int user_input;
extern UART_HandleTypeDef huart1;
extern int max_floor;
extern int current_floor;
extern int floor_wait_time;
extern bool alarm_led_enabled;

void printUART(char *string) {
  HAL_UART_Transmit(&huart1, (uint8_t *)string, strlen(string), 1000);
}

char *get_floor_queue() {
  char digit[3];
  char *string = (char *) malloc(40 * sizeof(char));

  strcpy(string, "Queue: ");
  for (int i = 0; i < floor_queue.length; i++) {
    sprintf(digit, "%d ", floor_queue.values[i]);
    strcat(string, digit);
  }

  return string;
}

void log_for_submit(SubmitStatus submitStatus) {
  char *queue;
  char message[100] = {0};

  switch (submitStatus) {
    case SUBMIT_SUCCESS:
      sprintf(message, "[Submit]: Added %d to queue successfully\n", user_input);
      queue = get_floor_queue();
      strcat(message, queue);
      strcat(message, "\n\n");
      free(queue);
      break;
    case SUBMIT_QUEUE_FULL:
      sprintf(message, "[submit]: Cannot add %d to queue, queue is full\n", user_input);
      queue = get_floor_queue();
      strcat(message, queue);
      strcat(message, "\n\n");
      free(queue);
      break;
    case SUBMIT_WRONG_FLOOR:
      sprintf(message, "[Submit]: Cannot add %d to queue, bad floor\n", user_input);
      queue = get_floor_queue();
      strcat(message, queue);
      strcat(message, "\n\n");
      free(queue);
      break;
    case SUBMIT_DUPLICATE_FLOOR:
      sprintf(message, "[Submit]: Didn't add %d to queue, this floor is already in queue\n", user_input);
      queue = get_floor_queue();
      strcat(message, queue);
      strcat(message, "\n\n");
      free(queue);
      break;
    case SUBMIT_CURRENT_FLOOR:
      strcpy(message, "[Submit]: Elevator is already in this floor!\n\n");
      break;
    case SUBMIT_ADMIN_MODE:
      strcpy(message, "[SUBMIT]: You cannot use elevator in admin mode\n\n");
      break;
  }

  printUART(message);
}

void log_for_login(LoginStatus loginStatus) {
  switch (loginStatus) {
    case LOGIN_CORRECT_PASSWORD:
      printUART("[LOGIN]: Logged in!\n\n");
      break;
    case LOGIN_WRONG_PASSWORD:
      printUART("[LOGIN]: Unable to login. Wrong password\n\n");
      break;
    case LOGIN_QUEUE_NOT_EMPTY:
      printUART("[LOGIN]: Oh elevator is moving, please wait...\n\n");
      break;
  }
}

void log_for_max_level(MaxLevelStatus maxLevelStatus) {
  char message[60];
  switch (maxLevelStatus) {
    case MAX_LEVEL_SUCCESS:
      sprintf(message, "[SET_MAX_LEVEL]: Successfully set max level to be %d\n\n", max_floor);
      printUART(message);
      break;
    case MAX_LEVEL_NOT_ADMIN_MODE:
      printUART("[SET_MAX_LEVEL]: Permission denied! please login first\n\n");
      break;
    case MAX_LEVEL_WRONG_INPUT:
      printUART(("[SET_MAX_LEVEL]: Please enter command in this format: SET MAX LEVEL [0-9]\n\n"));
      break;
  }
}

void log_for_level(LevelStatus levelStatus) {
  char message[90];
  switch (levelStatus) {
    case LEVEL_SUCCESS:
      sprintf(message, "[SET_LEVEL]: successfully set level to be %d\n\n", current_floor);
      printUART(message);
      break;
    case LEVEL_NOT_ADMIN_MODE:
      printUART("[SET_LEVEL]: Permission denied! please login first\n\n");
      break;
    case LEVEL_WRONG_INPUT:
      sprintf(message, "[SET_LEVEL]: Wrong input. Please enter command in this format: SET LEVEL [0-%d]\n\n", max_floor);
      printUART(message);
      break;
    case LEVEL_OUT_OF_RANGE:
      sprintf(message, "[SET_LEVEL]: Out of range. you can enter values in range (0, %d)\n\n", max_floor);
      printUART(message);
      break;
  }
}

void log_for_wait(WaitStatus waitStatus) {
  char message[90];
  switch (waitStatus) {
    case WAIT_SUCCESS:
      sprintf(message, "[SET_WAIT]: successfully set wait time to be %d\n\n", floor_wait_time);
      printUART(message);
      break;
    case WAIT_NOT_ADMIN_MODE:
      printUART("[SET_WAIT]: Permission denied! please login first\n\n");
      break;
    case WAIT_WRONG_INPUT:
      printUART("[SET_WAIT]: Wrong input. Please enter command in this format: SET WAIT [N]\n\n");
      break;
    case WAIT_OUT_OF_RANGE:
      printUART("[SET_WAIT]: Out of range. Please enter a multiple of 100 in range 500-5000\n\n");
      break;
  }
}

void log_for_led(LedStatus ledStatus) {
  char message[60];
  switch (ledStatus) {
    case LED_SUCCESS:
      sprintf(message, "[SET_LED]: successfully set LED to be %s\n\n", alarm_led_enabled ? "ON" : "OFF");
      printUART(message);
      break;
    case LED_NOT_ADMIN_MODE:
      printUART("[SET_LED]: Permission denied! please login first\n\n");
      break;
    case LED_WRONG_INPUT:
      printUART("[SET_LED]: Wrong input. Please enter command in this format: SET LED [ON/OFF]\n\n");
      break;
  }
}

void log_for_test(TestStatus testStatus) {
  char *queue;
  char message[100];

  switch (testStatus) {
    case TEST_SUCCESS:
      sprintf(message, "[TEST]: Success! added your test floors to queue and optimized it\n");
      queue = get_floor_queue();
      strcat(message, queue);
      strcat(message, "\n\n");
      printUART(message);
      free(queue);
      break;
    case TEST_NOT_ADMIN_MODE:
      printUART("[TEST]: Permission denied! please login first\n\n");
      break;
    case TEST_WRONG_INPUT:
      printUART("[TEST]: Wrong input. Please enter command in this format: TEST#{sample}\n\n");
      break;
    case TEST_OUT_OF_RANGE:
      sprintf(message, "[TEST]: Out of range. Please enter a list of numbers in range (0, %d)\n\n", max_floor);
      printUART(message);
      break;
  }
}