#include "apue.h"
#include <setjmp.h>
#include <errno.h>
#include <time.h>

static void sig_usr1(int);
static void sig_alrm(int);
static sigjmp_buf jmpbuf;
static volatile sig_atomic_t canjump;

static void my_pr_mask(const char *, sigset_t *);

int main(void) {
	if (signal(SIGUSR1, sig_usr1) == SIG_ERR) {
		err_sys("signal(SIGUSR1) error");
	}
	if (signal(SIGALRM, sig_alrm) == SIG_ERR) {
		err_sys("signal(SIGALRM) error");
	}
	
	my_pr_mask("starting main: ", NULL);
	
	if (sigsetjmp(jmpbuf, 1)) {
		my_pr_mask("ending main: ", NULL);
	}
	canjump = 1;

	for (;;) {
		pause();
	}
}

static void sig_usr1(int signo) {
	time_t starttime;

	/* unexpected signal, ignore */
	if (canjump == 0) {
		return;
	}
	
	my_pr_mask("starting sig_usr1: ", NULL);

	alarm(3);
	starttime = time(NULL);
	for (;;) {
		if (time(NULL) > starttime + 5) {
			break;
		}
	}

	my_pr_mask("finisning sig_usr1: ", NULL);

	canjump = 0;
	/* jump to main, don't return */
	siglongjmp(jmpbuf, 1);
}

static void sig_alrm(int signo) {
	my_pr_mask("in s