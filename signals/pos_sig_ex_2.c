#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int count = 1;
struct sigaction action, sa;

void sig_handler(int s) {
    printf("\nI got SIGINT %d time(s)\n", count++);
    if (count == 5) {
        action.sa_handler = SIG_DFL; // Изменяем указатель на стандартную функцию обработчик
        sigaction(SIGINT, &action, &sa);
    
        exit(1); //Необходимо для корректной работы скрипта
    } 
}


int main(int argc, char *argv[]) {
    printf("Используйте CTRL-C для отправки сигнала SIGINT\n");
    sigset_t sigset;
    sigemptyset(&sigset); // Инициализируем набор сигналов
    sigaddset(&sigset, SIGINT); // Добавляем в набор сигналов бит соответствующий сигналу SIGINT
    if (sigprocmask(SIG_UNBLOCK, &sigset, NULL) == -1) {
        fprintf(stderr, "sigprocmask() error\n");
        return -1;
    }
    // Инициализируем указатель на функуию обработчик сигнала
    action.sa_handler = sig_handler;

    // Изменяем обработчик по умолчанию для сигнала SIGINT
    sigaction(SIGINT, &action, &sa);

    while (1) {
        pause();
    }
    return 0;
}
