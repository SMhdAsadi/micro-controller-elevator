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

char *log_submit(int status) {
  char *queue;
  char message[100] = {0};

  switch (status) {
    case 0:
      sprintf(message, "[Submit]: Added %d to queue successfully\n", user_input);
      queue = get_floor_queue();
      strcat(message, queue);
      strcat(message, "\n\n");
      free(queue);
      break;
    case -1:
      sprintf(message, "[submit]: Cannot add %d to queue, queue is full\n", user_input);
      queue = get_floor_queue();
      strcat(message, queue);
      strcat(message, "\n\n");
      free(queue);
      break;
    case -2:
      sprintf(message, "[Submit]: Cannot add %d to queue, bad floor\n", user_input);
      queue = get_floor_queue();
      strcat(message, queue);
      strcat(message, "\n\n");
      free(queue);
      break;
    case -3:
      sprintf(message, "[Submit]: Didn't add %d to queue, this floor is already in queue\n", user_input);
      queue = get_floor_queue();
      strcat(message, queue);
      strcat(message, "\n\n");
      free(queue);
      break;
    default:
      strcpy(message, "");
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