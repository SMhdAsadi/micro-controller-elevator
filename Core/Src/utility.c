#include <stdbool.h>
#include "types.h"

extern Queue floor_queue;
extern int max_floor;

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