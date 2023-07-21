//
// Created by DigitalCyan on 7/21/23.
//

#ifndef GAME_OF_LIFE_LOGGER_H
#define GAME_OF_LIFE_LOGGER_H

#include <stdio.h>

typedef enum {
    INFO = 0,
    WARNING,
    ERROR,
} log_level_t;

void logger(log_level_t log_level, char *text);

#endif //GAME_OF_LIFE_LOGGER_H
