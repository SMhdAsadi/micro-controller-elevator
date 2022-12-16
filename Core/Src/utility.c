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

bool floor_queue_includes(int number) {
  for (int i = 0; i < floor_queue.length; i++) {
    if (floor_queue.values[i] == number) {
      return true;
    }
  }
  return false;
}

int add_to_floor_queue(int floor) {
  if (floor_queue_includes(floor)) return -3; // no need to add
  if (floor_queue.length > max_floor) return -1; // queue is full
  if (floor > max_floor || floor < 0) return -2; // floor is wrong

  enqueue_to_floor_queue(floor);
  return 0;
}

void login(char* password) {
  if (strcmp(password, admin_password) == 0) {
    is_admin_mode = true;
    log_for_login(true);
  } else {
    log_for_login(false);
  }
}

void set_max_floor(int n) {}
void set_floor(int n) {}
void set_wait(int ms) {}
/* value: ON | OFF */
void toggle_led(char* value) {}
void test(int floors[]) {}

void parse_command(char* command) {
  if(strstr(command, "ADMIN#")) {
    char password[5] = {0};
    slice(command, password, 6, 10);
    login(password);
  } else if(strstr(command, "SET MAX LEVEL")) {
    int n = 0;
    sprintf(command, "SET MAX LEVEL %d", n);
    set_max_floor(n);
  } else if(strstr(command, "SET LEVEL")) {
    int n = 0;
    sprintf(command, "SET LEVEL %d", n);
    set_floor(n);
  } else if(strstr(command, "SET WAIT")) {
    int ms = 0;
    sprintf(command, "SET WAIT %d", ms);
    set_wait(ms);
  } else if(strstr(command, "SET LED")) {
    char *value = NULL;
    sprintf(command, "SET LED %s", value);
    toggle_led(value);
  } else if(strstr(command, "TEST#")) {
    char *str_value = NULL;
    sprintf(command, "TEST#%s", str_value);
    unsigned int size = strlen(str_value);
    int values[size];
    for(int i = 0; i < size; i++)
      values[i] = str_value[i] - 48;
    test(values);
  }
}