#ifndef _LOG_HPP_
#define _LOG_HPP_

#include <boost/cstdint.hpp>
#include <iostream>
#include <cstdio>

#include "Flags.hpp"

using namespace boost;

enum LogLevel
{
    LOG_LEVEL_BASIC = 1,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_NOTICE,
    LOG_LEVEL_DEBUG,
};

enum LogFilters
{
    LOG_FILTER_MEMLEAK = 0x01,
    LOG_FILTER_INPUT   = 0x02,
};

class Log
{
    public:
        static void setLogLevel(uint8_t level) { _logLevel = level; }
        static void setFilters(uint8_t filters) { _logFilters += filters; }
        static uint8_t getLogLevel() { return _logLevel; }

        static void outBasic(const char* str, ...);

        static void outError(const char* str, ...);
        static void outErrorFilter(uint8_t f, const char* str, ...);

        static void outNotice(const char* str, ...);
        static void outNoticeFilter(uint8_t f, const char* str, ...);

        static void outDebug(const char* str, ...);
        static void outDebugFilter(uint8_t f, const char* str, ...);

        static void out(const char* type, const char* str, va_list args);

        static uint8_t _logLevel;
        static Flags _logFilters;
    private:

};

#endif //_LOG_HPP_
