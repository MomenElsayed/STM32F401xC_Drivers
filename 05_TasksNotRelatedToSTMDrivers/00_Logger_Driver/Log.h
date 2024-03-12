#ifndef LOG_H_
#define LOG_H_


#include <stdarg.h>
#include <stdio.h>



typedef enum {
    log_out_console,
    log_out_file
} LogOutputChannel;

typedef enum {
    log_critical,
    log_error,
    log_warning,
    log_info
} LogCriticalityLevel;

void log_setOutputChannel(LogOutputChannel channel);
void log_fileCfg(const char *filepath);
void log_general(const char *color, const char *name,const char *format_string, va_list *arg);
void log_write(LogCriticalityLevel level,const char* format_string,...);




#endif /*LOG_H_*/
