#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int pid_server = fork();
    if (pid_server == 0) {
        execlp("./fifo_ex_server", "fifo_ex_server", NULL);
    }
    for (int i = 0; i < 10; i++) {
        if (!fork()) execlp("./fifo_ex_client", "fifo_ex_client", NULL);
        wait(NULL);
    }

    int fd = open("fifo", O_RDWR);
    int some = -1;

    write(fd, &some, sizeof(some));

    close(fd);

    waitpid(pid_server, NULL, 0);

    return 0;
}
