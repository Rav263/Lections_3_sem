#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>


int main(int argc, char *argv[]) {
    if (fork() == 0) { // Первый процесс-потомок
        execl("/bin/echo", "echo", "this is", "string 1", 0);
        exit(1);
    }
    if (fork() == 0) { // Второй процесс-потомок
        execl("/bin/echo", "echo", "this is", "string 2", 0);
        exit(1);
    }

    /* Процесс предок */

    printf("process-father is waiting for children\n");
    while (wait(NULL) != -1);

    printf("all children has been terminated\n");

    return 0;
}
