#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

/* Данную программу необходимо запускать командой ./a.out ./print1 ./print2 ./print3 */


int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        int status;

        if (fork() > 0) {
            /* процесс-предок ожидает сообщения от процесса-потомка о завершении */

            wait(&status);

            /* печатаем статусзавершения процесса-потомка */
            printf("process-father: exit status: %d\n", status);
            continue;
        }

        execlp(argv[i], argv[i], 0);
        exit(1);
    }
}
