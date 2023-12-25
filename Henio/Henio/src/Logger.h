#pragma once
#include <cstdio>
#include <ostream>

#define LOG_ERROR(...) Logger::LogError(__VA_ARGS__);
#define LOG_WARNING(...) Logger::LogWarning(__VA_ARGS__);
#define LOG_MESSAGE(...) Logger::LogMessage(__VA_ARGS__);

class Logger
{
public:
    
    template <typename... Args>
    static void LogError(Args ... args)
    {
        system("Color 4");
        std::printf("[Error] %s: ", __FUNCTION__);
        Log(mLogError, args ... );
    }

    template <typename... Args>
    static void LogWarning(Args ... args)
    {
        system("Color 6");
        std::printf("[Warning] %s: ", __FUNCTION__);
        Log(mLogWarning, args ... );
    }

    template <typename... Args>
    static void LogMessage(Args ... args)
    {
        system("Color 7");
        std::printf("[Message] %s: ", __FUNCTION__);
        Log(mLogMessage, args ... );
    }
    
    static void SetLogLevel(unsigned int inLogLevel)
    {
        inLogLevel <= 9 ? mLogLevel = inLogLevel :
        mLogLevel = 9;
    }

    
    
private:
    /* log if input log level is equal or smaller to log level set */
    template <typename... Args>
    static void Log(unsigned int logLevel, Args ... args)
    {
        if (logLevel <= mLogLevel) {
            std::printf(args ...);
            std::printf("\n");
            /* force output, i.e. for Eclipse */
            std::fflush(stdout);

        }
    }
    
    static unsigned int mLogLevel;
    static unsigned int mLogError;
    static unsigned int mLogWarning;
    static unsigned int mLogMessage;
};
