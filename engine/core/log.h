//
// Created by Diego Santos Seabra on 17/01/21.
//

#ifndef MAGICK_ENGINE_LOG_H
#define MAGICK_ENGINE_LOG_H

#define MESSAGE_MAX 1024

namespace Log
{
    void print(const char *format, ...);
    void warn(const char *format, ...);
    void error(const char *format, ...);
}

#endif //MAGICK_ENGINE_LOG_H
