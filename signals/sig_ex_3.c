#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void alrm(int s) {
    signal(SIGALRM, alrm);
    printf("ГДЕ ИМЯ ПОДОНОК\?\?!!!\n");
    alarm(5);
}

int main(int argc, char *argv[]) {
    char s[80];

    signal(SIGALRM, alrm);

    alarm(5);

    printf("Введите имя: \n");

    for (;;) {
        printf("имя: ");
        if (fgets(s, 80, stdin) != NULL) break;
    }

    printf("OK\n");

    return 0;
}
