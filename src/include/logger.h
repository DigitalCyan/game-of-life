//
// Created by DigitalCyan on 7/21/23.
//

#ifndef GAME_OF_LIFE_LOGGER_H
#define GAME_OF_LIFE_LOGGER_H

#include <stdio.h>

#define ANSI_CLEAR "\033[0m"
#define ANSI_RED "\033[0;31m"
#define ANSI_GREEN "\033[0;32m"
#define ANSI_YELLOW "\033[0;33m"

typedef enum {
    LOG_INFO = 0,
    LOG_SUCCESS,
    LOG_WARNING,
    LOG_ERROR,
} log_level_t;

void logger(log_level_t log_level, char *text);

#endif //GAME_OF_LIFE_LOGGER_H
