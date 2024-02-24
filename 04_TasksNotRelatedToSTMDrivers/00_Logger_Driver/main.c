#include <stdio.h>
#include "Log.h"



int main()
{
	log_setOutputChannel(log_out_console);
	log_fileCfg("./Trail.txt");
	log_write(log_critical,"%s", "RUN!");
	log_write(log_error,"%s","Error Message TAKE CARE");
	log_write(log_warning,"%s","It is Just a warning don't panic");
	log_write(log_info,"%s","It is Just an Info");
}
