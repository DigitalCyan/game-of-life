#include <logger.h>

void logger(log_level_t log_level, char *text) {
    switch (log_level) {
        case INFO:
            printf("[INFO]    | %s\n", text);
            break;
        case WARNING:
            printf("[WARNING] | %s\n", text);
            break;
        case ERROR:
            printf("[ERROR]   | %s\n", text);
            break;
    }
}