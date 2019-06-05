#include "apue.h"

int main(int argc, char** argv) {
    printf("%s\n", "Hello!World!");
    err_sys("test err_sys! %s", "xxx");
    return 0;
}

