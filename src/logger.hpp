#pragma once

#include <obs-module.h>

namespace Logger {
static const int DEFAULT_LOG_LEVEL = LOG_INFO;

void log(int log_level, const char *format, ...);
void log(const char *format, ...);

void error(const char *format, ...);
void debug(const char *format, ...);
} // namespace Logger
