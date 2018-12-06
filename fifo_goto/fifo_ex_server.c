#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // Создаём специальный файл FIFO с открытыми для всех правами доступа
    mkfifo("fifo", S_IFIFO | 0666);

    // Открываем канал на чтение
    int fd = open("fifo", O_RDONLY);

    int pid;
    while (1) {
        if (read(fd, &pid, sizeof(pid)) == sizeof(pid)) {
            if (pid == -1) {
                break;
            }
            printf("Server %d got message from %d!\n", getpid(), pid);
        }
    }
    close(fd);

    unlink("fifo");

    return 0;
}
