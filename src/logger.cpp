#include "logger.hpp"

namespace Logging {
    
#if _WIN32
    
    static char _logBuffer[LOG_BUFFER_SIZE];
    
    void Log(const char* msg, ...) {
        va_list args;
        
        va_start(args, msg);
        
        int length = vsnprintf(_logBuffer, LOG_BUFFER_SIZE, msg, args);
        
        va_end(args);
        
        OutputDebugString(msg);
    }
    
#elif __APPLE__
    
    void Log(const char* msg, ...) {
        va_list args;

        va_start(args, msg);

        vprintf(msg, args);

        va_end(args);
    }
    
#endif
    
}
