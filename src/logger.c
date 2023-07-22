#include <logger.h>

void logger(log_level_t log_level, char *text) {
    switch (log_level) {
        case LOG_INFO:
            printf("[INFO]    | %s", text);
            break;
        case LOG_SUCCESS:
            printf(ANSI_GREEN);
            printf("[SUCCESS] | %s", text);
            break;
        case LOG_WARNING:
            printf(ANSI_YELLOW);
            printf("[WARNING] | %s", text);
            break;
        case LOG_ERROR:
            printf(ANSI_RED);
            printf("[ERROR]   | %s", text);
            break;
    }

    printf("%s\n", ANSI_CLEAR);
}