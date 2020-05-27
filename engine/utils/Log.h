//
// Created by Diego Santos Seabra on 24/05/20.
//

#ifndef MAGICK_GAME_ENGINE_LOG_H
#define MAGICK_GAME_ENGINE_LOG_H

#include <cstdio>
#include <cstdlib>
#include <iostream>

#define RESET   "\033[0m"
#define WHITE   "\033[30m"    /* Black */
#define RED     "\033[31m"    /* Red */
#define GREEN   "\033[32m"    /* Green */
#define YELLOW  "\033[33m"    /* Yellow */
#define BLUE    "\033[34m"    /* Blue */
#define MAGENTA "\033[35m"    /* Magenta */
#define CYAN    "\033[36m"    /* Cyan */
#define BLACK   "\033[37m"    /* White */

using namespace std;

class Log
{
public:
    constexpr static bool printToConsole = true;

    static void Message(string message);
    static void Warning(string warning);
    static void Error(string error);

private:
    static void Line(string subtitle, string colour, string message);
    static void Append(string text, bool consoleOnly = false);
};


#endif //MAGICK_GAME_ENGINE_LOG_H
