#include "apue.h"
#include <fcntl.h>

int main(int argc, char** argv) {
    if (rename("tempfile", "renamefile") < 0) {
        err_sys("rename error");
    }
    exit(0);
}

