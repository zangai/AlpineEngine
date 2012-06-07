#include "Log.hpp"
#include <cstdio>
#include <cstdarg>

using namespace std;

uint8_t Log::_logLevel = 0;
Flags Log::_logFilters(0);

void Log::outBasic(const char* str, ...)
{
    if(!str || _logLevel < LOG_LEVEL_BASIC)
        return;

    va_list ap;
    va_start(ap, str);
    out("BASIC", str, ap);
    va_end(ap);
}

void Log::outError(const char* str, ...)
{
    if(!str || _logLevel < LOG_LEVEL_ERROR)
        return;

    va_list ap;
    va_start(ap, str);
    out("ERROR", str, ap);
    va_end(ap);
}
void Log::outErrorFilter(uint8_t f, const char* str, ...)
{
    if (Log::_logFilters != f || !str || _logLevel < LOG_LEVEL_ERROR)
        return;

    va_list ap;
    va_start(ap, str);
    out("ERROR", str, ap);
    va_end(ap);
}

void Log::outNotice(const char* str, ...)
{
    if(!str || _logLevel < LOG_LEVEL_NOTICE)
        return;

    va_list ap;
    va_start(ap, str);
    out("NOTICE", str, ap);
    va_end(ap);
}
void Log::outNoticeFilter(uint8_t f, const char* str, ...)
{
    if (Log::_logFilters != f || !str || _logLevel < LOG_LEVEL_NOTICE)
        return;

    va_list ap;
    va_start(ap, str);
    out("NOTICE", str, ap);
    va_end(ap);
}

void Log::outDebug(const char* str, ...)
{
    if(!str || _logLevel < LOG_LEVEL_DEBUG)
        return;

    va_list ap;
    va_start(ap, str);
    out("DEBUG", str, ap);
    va_end(ap);
}
void Log::outDebugFilter(uint8_t f, const char* str, ...)
{
    if (Log::_logFilters != f || !str || _logLevel < LOG_LEVEL_DEBUG)
        return;

    va_list ap;
    va_start(ap, str);
    out("DEBUG", str, ap);
    va_end(ap);
}

void Log::out(const char* type, const char* str, va_list args)
{
    cout << type << "> ";
    vprintf(str, args);
    cout << endl;
}
