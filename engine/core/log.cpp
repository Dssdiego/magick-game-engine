//
// Created by Diego Santos Seabra on 17/01/21.
//

#include "log.h"
#include <cstdarg>
#include <cstdio>

void Log::print(const char *format, ...)
{
    char msg[MESSAGE_MAX];
    va_list ap;
    va_start(ap, format);
    vsnprintf(msg, sizeof(char) * MESSAGE_MAX, format, ap);
    va_end(ap);

    printf("%s\n", msg);
}

void Log::warn(const char *format, ...)
{
    char msg[MESSAGE_MAX];
    va_list ap;
    va_start(ap, format);
    vsnprintf(msg, sizeof(char) * MESSAGE_MAX, format, ap);
    va_end(ap);

    printf("\033[01;33mWARN:\033[0m\t%s\n", msg);
}

void Log::error(const char *format, ...)
{
    char msg[MESSAGE_MAX];
    va_list ap;
    va_start(ap, format);
    vsnprintf(msg, sizeof(char) * MESSAGE_MAX, format, ap);
    va_end(ap);

    printf("\033[1;31mERROR:\033[0m\t%s\n", msg);
}
