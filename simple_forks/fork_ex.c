#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    /* Печать PID текущего процесса и PID процесса-предка */
    printf("PID=%d; PPID=%d\n", getpid(), getppid());

    /* Создание нового процесса*/
    fork();
    /* С этого момента два процесса функцианируют параллельно и независимо */

    /* Оба процесса печатают PID текущего процесса и PID процесса-предка */
    printf("PID=%d; PPID=%d\n", getpid(), getppid());
}
