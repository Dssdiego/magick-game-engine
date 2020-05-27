//
// Created by Diego Santos Seabra on 24/05/20.
//

#include "Log.h"

void Log::Message(string message)
{
    Line("INFO", BLACK, message);
}

void Log::Warning(string warning)
{
    Line("WARN", YELLOW, warning);
}

void Log::Error(string error)
{
    Line("FAIL", RED, error);
}

void Log::Line(string subtitle, string colour, string message)
{
    cout << BLUE;
    Append("MAGICK", true);
    cout << colour;
    Append(":" + subtitle + ": " + message, true);
    cout << endl;
}

void Log::Append(string text, bool consoleOnly)
{
    if(printToConsole) {
        cout << text;
    }
}
