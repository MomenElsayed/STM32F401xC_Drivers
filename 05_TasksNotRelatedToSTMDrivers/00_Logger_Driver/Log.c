#include <time.h>
#include "Log.h"


LogOutputChannel currentOutputChannel = log_out_console;
const char* requieredfilepath = NULL;

void log_setOutputChannel(LogOutputChannel channel)
{
	currentOutputChannel = channel;
}


void log_fileCfg(const char *filepath)
{
	requieredfilepath = filepath;
    FILE *file = fopen(requieredfilepath, "a");
    if (file != NULL) {
        fclose(file);
    }
}

void log_general(const char *color, const char *name,const char *format_string, va_list *arg)
{
	va_list argCopy;
	va_copy(argCopy, *arg);
	int len = vsnprintf(NULL, 0, format_string, argCopy);
	va_end(argCopy);
	char buf[len + 1];
	len = vsnprintf(buf, sizeof buf, format_string, *arg);
    time_t t = time(NULL);
    if (t == -1)
    {
      return;
    }
    struct tm *tm = localtime(&t);
    if (tm == NULL)
    {
      return;
    }
    printf("%02d:%02d:%02d ", tm->tm_hour, tm->tm_min, tm->tm_sec);
    printf("\033[0m\033[%sm[%s]\033[0m %s\n", color, name, buf);
}



void log_write(LogCriticalityLevel level,const char* format_string,...)
{
	va_list args;
	va_start(args,format_string);
	const char *color;
	const char *logLevelName;
	switch(level)
	{
		case log_critical:
			color = "1;31";
			logLevelName = "CRITICAL";
			break;
		case log_error:
			color = "1;35";
			logLevelName = "ERROR";
			break;
		case log_warning:
			color = "1;33";
			logLevelName = "WARNING";
			break;
		case log_info:
			color = "1;34";
			logLevelName = "INFO";
			break;
	}

	if (currentOutputChannel == log_out_console)
	{
		log_general(color, logLevelName, format_string, &args);
	}
	else if (currentOutputChannel == log_out_file)
	{
		if (requieredfilepath != NULL)
		{
			FILE *file = fopen(requieredfilepath,"a"); /*a means Append*/
			if (file != NULL)
			{
				time_t t = time(NULL);
				if(t != -1)
				{
					struct tm* tm_info = localtime(&t);
					if(tm_info != NULL)
					{
						fprintf(file, "%02d:%02d:%02d [%s] ", tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec, logLevelName);
					}
				}
				vfprintf(file, format_string, args);
				fprintf(file,"\n");
				fclose(file);
			}
		}

	}
	va_end(args);
}




