#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "types.h"
#include "logger.h"

extern AlarmState alarm_state;

extern int seven_segment_digit_controller;
extern int timer_counter;

extern int current_floor;
extern int max_floor;
extern int moving_delay;

extern Queue floor_queue;

extern int user_input;

extern bool alarm_led_enabled;
extern bool alarm_enabled;
extern bool is_admin_mode;
extern bool is_idle;
extern char *admin_password;

void slice(const char *str, char *result, size_t start, size_t end) {
  strncpy(result, str + start, end - start);
}

int enqueue_to_floor_queue(int number) {
  if (floor_queue.length >= 10 || floor_queue.length < 0) return -1;

  floor_queue.values[floor_queue.length] = number;
  floor_queue.length++;
  return 0;
}

int dequeue_from_floor_queue() {
  if (floor_queue.length <= 0) return -1;

  int output = floor_queue.values[0];

  for (int i = 0; i < floor_queue.length - 1; i++) {
    floor_queue.values[i] = floor_queue.values[i + 1];
  }

  floor_queue.length--;
  return output;
}

int peek_from_floor_queue() {
  if (floor_queue.length <= 0) return -1;

  return floor_queue.values[0];
}

void clear_floor_queue() {
  floor_queue.length = 0;
}

bool floor_queue_includes(int number) {
  for (int i = 0; i < floor_queue.length; i++) {
    if (floor_queue.values[i] == number) {
      return true;
    }
  }
  return false;
}

bool is_floor_queue_empty() {
  return floor_queue.length == 0;
}

SubmitStatus add_to_floor_queue(int floor) {
  if (floor_queue_includes(floor)) return SUBMIT_DUPLICATE_FLOOR;
  if (floor_queue.length > max_floor) return SUBMIT_QUEUE_FULL;
  if (floor > max_floor || floor < 0) return SUBMIT_WRONG_FLOOR;

  enqueue_to_floor_queue(floor);
  return SUBMIT_SUCCESS;
}

void login(char* password) {
  if (strcmp(password, admin_password) == 0) {
    is_admin_mode = true;
    log_for_login(LOGIN_CORRECT_PASSWORD);
  } else {
    log_for_login(LOGIN_WRONG_PASSWORD);
  }
}

void parse_admin_command(char *command) {
  if (!is_floor_queue_empty()) {
    log_for_login(LOGIN_QUEUE_NOT_EMPTY);
    return;
  }
  char password[5] = {0};
  slice(command, password, 6, 10);
  login(password);
}

void parse_max_level_command(char *command) {
  if (!is_admin_mode) {
    log_for_max_level(MAX_LEVEL_NOT_ADMIN_MODE);
    return;
  }
  int length = strlen(command) - strlen("SET MAX LEVEL ");
  if (length > 1) {
    log_for_max_level(MAX_LEVEL_WRONG_INPUT);
    return;
  }

  char max_level[2] = {0};
  slice(command, max_level, 14, 15);
  int ascii_code = max_level[0] - 48;
  if (ascii_code > 9 || ascii_code < 0) {
    log_for_max_level(MAX_LEVEL_WRONG_INPUT);
    return;
  }

  max_floor = ascii_code;
  if (current_floor > max_floor) {
    current_floor = max_floor;
  }
  clear_floor_queue();
  log_for_max_level(MAX_LEVEL_SUCCESS);
}

void parse_level_command(char *command) {
  if (!is_admin_mode) {
    log_for_level(LEVEL_NOT_ADMIN_MODE);
    return;
  }

  int length = strlen(command) - strlen("SET LEVEL ");
  if (length > 1) {
    log_for_level(LEVEL_WRONG_INPUT);
    return;
  }

  char level[2] = {0};
  slice(command, level, 10, 11);
  int ascii_code = level[0] - 48;
  if (ascii_code >= max_floor || ascii_code < 0) {
    log_for_level(LEVEL_OUT_OF_RANGE);
    return;
  }

  current_floor = ascii_code;
  clear_floor_queue();
  log_for_level(LEVEL_SUCCESS);
}

void parse_command(char* command) {
  if(strstr(command, "ADMIN#")) {
    parse_admin_command(command);
  } else if(strstr(command, "SET MAX LEVEL")) {
    parse_max_level_command(command);
  } else if(strstr(command, "SET LEVEL")) {
    parse_level_command(command);
  } else if(strstr(command, "SET WAIT")) {
    int ms = 0;
    sprintf(command, "SET WAIT %d", ms);
  } else if(strstr(command, "SET LED")) {
    char *value = NULL;
    sprintf(command, "SET LED %s", value);
  } else if(strstr(command, "TEST#")) {
    char *str_value = NULL;
    sprintf(command, "TEST#%s", str_value);
    unsigned int size = strlen(str_value);
    int values[size];
    for(int i = 0; i < size; i++)
      values[i] = str_value[i] - 48;
  } else if (strstr(command, "Start")) {
    //
  }
}