#include <signal.h>
#include <setjmp.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


jmp_buf env;

void abc(int s) {
    longjmp(env, 1);
}

int main(int argc, char *argv[]) {
    if (setjmp(env) == 0) {
        signal(SIGINT, abc);

        while (1) {
            printf("Что-то происходит\n");
            sleep(1);
        }
    } else {
        printf("Что-то произошло\n");
    }
}
