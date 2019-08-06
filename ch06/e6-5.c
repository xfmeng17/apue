#include "apue.h"
#include <time.h>

int main(int argc, char **argv) {
	time_t caltime;
	struct tm *tm;
	char line[MAXLINE];
	
	if ((caltime = time(NULL)) == -1) {
		err_sys("time error");
	}
	if ((tm = localtime(&caltime)) == NULL) {
		err_sys("localtime error");
	}
	if (strftime(line, MAXLINE, "%a %b %d %X %Z %Y\n", tm) == 0) {
		err_sys("strftime error");
	}
	fputs(line, stdout);
	
	return 0;
}

/*
 * TZ=Asia/Shanghai ./a.out
 */

