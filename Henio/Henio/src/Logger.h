#pragma once
#include <cstdio>

class Logger
{
public:
    
    template <typename... Args>
    static void LogError(Args ... args)
    {
        Log(mLogError, args ... );
    }

    template <typename... Args>
    static void LogWarning(Args ... args)
    {
        Log(mLogWarning, args ... );
    }

    template <typename... Args>
    static void LogMessage(Args ... args)
    {
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
            /* force output, i.e. for Eclipse */
            std::fflush(stdout);

        }
    }
    
    static unsigned int mLogLevel;
    static unsigned int mLogError;
    static unsigned int mLogWarning;
    static unsigned int mLogMessage;
};
