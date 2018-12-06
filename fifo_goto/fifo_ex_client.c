#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int fd;

    int pid = getpid();
    fd = open("fifo", O_RDWR);

    if (fd < 0) {
        fprintf(stderr, "No SERVER found\n");
    }


    write(fd, &pid, sizeof(pid));
    close(fd);

    return 0;
}
