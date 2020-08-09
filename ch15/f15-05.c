#include <apue.h>

int main(void) {
  int n;
  int fd[2];
  pid_t pid;
  char line[MAXLINE];

  if (pipe(fd) < 0) {
    err_sys("pipe error");
  }
  printf("fd[0]=%d, fd[1]=%d\n", fd[0], fd[1]);
  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid > 0) {
    close(fd[0]);
    write(fd[1], "hello world my boy\n", 18);
    sleep(20);
  } else {
    close(fd[1]);
    sleep(10);
    n = read(fd[0], line, MAXLINE);
    write(STDOUT_FILENO, line, n);
  }

  exit(0);
}
