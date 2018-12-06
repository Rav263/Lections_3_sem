#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int count = 0;

void sig_handler(int s) { /* Обработчик сигнала */
    printf("\n I have got SIGINT %d time(s)\n", ++count);
    if (count == 5) {
        signal(SIGINT, SIG_DFL); // Ставим обработчик сигнала по умолчанию
        exit(1); // Нужно для корректной работы скрипта
    } else {
        signal(SIGINT, sig_handler); // Восстанавливаем наш обработчик сигнала
    }
}


int main(int argc, char *argv[]) {
    printf("Используйте CTRL-C для отправки сигнала SIGINT\n");
    signal(SIGINT, sig_handler); // Установка нашего обработчика сигнала

    while(1) {
        pause();
    }

    return 0;
}
