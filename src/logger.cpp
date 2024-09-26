#include "logger.hpp"
#include "src/plugin-support.h"

static void _log(int log_level, const char *format, va_list args)
{
    size_t length = 4 + strlen(PLUGIN_NAME) + strlen(format);

    char *templateStr = (char *)malloc(length + 1);

    snprintf(templateStr, length, "[%s] %s", PLUGIN_NAME, format);

    blogva(log_level, templateStr, args);

    free(templateStr);
}

void Logger::log(int log_level, const char *format, ...)
{
    va_list args;

    va_start(args, format);
    _log(log_level, format, args);
    va_end(args);
}

void Logger::log(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    _log(Logger::DEFAULT_LOG_LEVEL, format, args);
    va_end(args);
}

void Logger::error(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    _log(LOG_ERROR, format, args);
    va_end(args);
}

void Logger::debug(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    _log(LOG_DEBUG, format, args);
    va_end(args);
}
