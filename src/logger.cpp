#include "logger.hpp"

namespace Logging {
    
#if _WIN32
    
#include <debugapi.h>
#include <windows.h>
    
    static char[LOG_BUFFER_SIZE] const _logBuffer;
    
    void Log(const char* msg, ...) {
        va_list args;
        
        va_start(args, msg);
        
        int length = vsnprintf(_logBuffer, LOG_BUFFER_SIZE, text, args_copy);
        
        if (length >= LOG_BUFFER_SIZE) {
            printf("Message longer than log buffer\n");
            if (_logBuffer[LOG_BUFFER_SIZE - 1] != NULL) {
                printf("vsnprintf does not return null terminated string if buffer is not large enough");
                _logBuffer[LOG_BUFFER_SIZE - 1] = NULL;
            }
        }
        
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
