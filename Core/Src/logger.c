#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include "types.h"
#include "stm32f3xx.h"

extern Queue floor_queue;
extern int user_input;
extern UART_HandleTypeDef huart1;

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

char *log_submit(SubmitStatus submitStatus) {
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
      strcpy(message, "[Submit]: Elevator is already in this floor!\n\n\0");
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