#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>


void alrm(int s) {
    signal(SIGALRM, alrm);
    printf("\nТы чё\?! Быстрее!!\n");
}


int main(int argc, char *argv[]) {
    signal(SIGALRM, alrm);
    char name[80];
    int pid = fork();

    if (pid != 0) {
        // Процесс отец
        for (;;) {
            sleep(5); // Приостанавливаем процесс на 5 секунд
            kill(pid, SIGALRM); // Отправляем сигнал SIGALRM сыну
        }
    } else {
        // Сыновий процесс
        printf("Введите имя\n");
        for (;;) {
            printf("имя:");
            if (fgets(name, 80, stdin) != NULL) {
                break;
            }
        }

        printf("Ок\n");
        kill(getppid(), SIGKILL); // Убиваем зациклившегося отца
    }
    return 0;
}
