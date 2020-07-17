#include <apue.h>
#include <sys/wait.h>

#define DEF_PAGER "/bin/more"

int main(int argc, char** argv) {
	int n;
	int fd[2];
	pid_t pid;
	char *pager, *argv0;
	char line[MAXLINE];
	FILE *fp;

	if (argc != 2) {
		err_quit("usage : a.out <pathname>");
	}
	printf("argv[1]=%s\n", argv[1]); 
	if ((fp = fopen(argv[1], "r")) == NULL) {
		err_sys("can’t open %s", argv[1]);
	}
	if (pipe(fd) < 0) {
		err_sys("pipe error");
	}

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid > 0) {
		close(fd[0]); /* close read end */
		/* parent copies argv[1] to pipe */
		int i = 0;
		while (fgets(line, MAXLINE, fp) != NULL) {
			printf("i = %d, line = %s", i++, line);
			n = strlen(line);
			if (write(fd[1], line, n) != n) {
				err_sys("write error to pipe");
			}
		}
		if (ferror(fp)) {
			err_sys("fgets error");
		}
		close(fd[1]);
		/* close write end of pipe for reader */

		if (waitpid(pid, NULL, 0) < 0) {
			err_sys("waitpid error");
		}
		exit(0);
	} else {
		/* child */
		close(fd[1]);
		if (fd[0] != STDIN_FILENO) {
			if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO) {
				err_sys("dup2 error to stdin");
			}
			close(fd[0]);
		}
		/* get arguments for excel() */
		if ((pager = getenv("PAGER"))== NULL) {
			pager = DEF_PAGER;
		}
		if ((argv0 = strrchr(pager, '/')) != NULL) {
			argv0++;
		} else {
			argv0 = pager;
		}
		printf("pager=%s\n", pager);
		printf("argv0=%s\n", argv0);
		if (execl(pager, argv0, (char*)0) < 0) {
			err_sys("execl error for %s", pager);
		}
	}
	exit(0);
}
 
