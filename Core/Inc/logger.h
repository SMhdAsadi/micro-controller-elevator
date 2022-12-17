#ifndef MICRO_CONTROLLER_ELEVATOR_MINI_PROJECT_LOGGER_H
#define MICRO_CONTROLLER_ELEVATOR_MINI_PROJECT_LOGGER_H

void printUART(char *string);
void log_for_submit(SubmitStatus submitStatus);
void log_for_login(LoginStatus loginStatus);
void log_for_max_level(MaxLevelStatus maxLevelStatus);
void log_for_level(LevelStatus levelStatus);
void log_for_wait(WaitStatus waitStatus);

#endif //MICRO_CONTROLLER_ELEVATOR_MINI_PROJECT_LOGGER_H
