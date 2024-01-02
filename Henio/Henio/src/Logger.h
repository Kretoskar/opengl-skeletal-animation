#pragma once
#include <cstdio>
#include <ostream>

enum LogVerbosity
{
    Error = 1,
    Warning = 2,
    Message = 3,
};

#define LOG_ERROR(...) \
    system("Color 4"); \
    std::printf("[Error] [%s] ", __FUNCTION__); \
    Logger::Log(LogVerbosity::Error, __VA_ARGS__);

#define LOG_WARNING(...) \
    system("Color 6"); \
    std::printf("[Warning] [%s] ", __FUNCTION__); \
    Logger::Log(LogVerbosity::Warning, args ... );

#define LOG_MESSAGE(...) \
    system("Color 7"); \
    std::printf("[Message] [%s] ", __FUNCTION__); \
    Logger::Log(LogVerbosity::Message, __VA_ARGS__);

class Logger
{
public:
    /* log if input log level is equal or smaller to log level set */
    template <typename... Args>
    static void Log(unsigned int logLevel, Args ... args)
    {
        if (logLevel <= logLevel) {
            std::printf(args ...);
            std::printf("\n");
            /* force output, i.e. for Eclipse */
            std::fflush(stdout);

        }
    }
    
    static void SetLogLevel(unsigned int inLogLevel)
    {
        inLogLevel <= 9 ? logLevel = inLogLevel :
        logLevel = 9;
    }
    
    static unsigned int logLevel;
    static unsigned int logError;
    static unsigned int logWarning;
    static unsigned int logMessage;
};
