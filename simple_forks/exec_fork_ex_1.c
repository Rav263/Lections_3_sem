#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    if (fork() == 0) {
        execl("/bin/echo", "echo", "это", "сообщение один", NULL);
        fprintf(stderr, "ошибка\n");
    }
    if (fork() == 0) {
        execl("/bin/echo", "echo", "это", "сообщение два", NULL);
        fprintf(stderr, "ошибка\n");
    }
    if (fork() == 0) {
        execl("/bin/echo", "echo", "это", "сообщение три", NULL);
        fprintf(stderr, "ошибка\n");
    }

    printf("Процесс предок завершился\n");
}
