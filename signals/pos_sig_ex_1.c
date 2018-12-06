#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    printf("Рекомендуюзапустить программу несколько раз\n");
    sigset_t sigset;
    int f1;

    sigemptyset(&sigset);

    printf("Добавить SIGINT к текущей маске? (yes = 1, no = 0)\n");
    scanf("%d", &f1);

    if (f1) {
        sigaddset(&sigset, SIGINT);
        sigprocmask(SIG_BLOCK, &sigset, NULL);
    }
    printf("Послать SIGINT? (yes = 1, no = 0) \n");
    scanf("%d", &f1);

    if (f1) {
        kill(getpid(), SIGINT);
    }
    // Получаем сигнальную маску процесса. Так как второй аргумент NULL
    // то первый будет игнорироваться
    
    if (sigprocmask(SIG_BLOCK, NULL, &sigset) == -1) {
        fprintf(stderr, "Ошибка при вызове sigprocmask()\n");
        return -1;
    } else if (sigismember(&sigset, SIGINT)) { // Проверяем наличие сигнала в маске
        printf("Сигнад SIGINT заблокирован!\n");
        sigemptyset(&sigset);
        if (sigpending(&sigset) == -1) { // Узнаём сигналы ожидающие доставки
            fprintf(stderr, "Ошибка при вызове sigpending()\n");
            return -1;
        }

        printf("Сигнал SIGINT %s\n", sigismember(&sigset, SIGINT) ? "ожидает доставки" : "не ожидает доставки");
        // Проверяем наличие сигнала SIGINT в маске
    } else {
        printf("Сигнал SIGINT не заблокирован\n");
    }

    return 0;
}
