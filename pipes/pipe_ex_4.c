#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_CNT 10
int target_pid, cnt;
int fd[2];
int status;

void sig_handler(int s) {
    // В обработке сигнала происходит чтение и запись
    if (cnt < MAX_CNT) {
        read(fd[0], &cnt, sizeof(cnt));
        printf("%d\n", cnt);
        
        cnt++;
        write(fd[1], &cnt, sizeof(cnt));
        
        //Посылаем другому процессу, что пора читать из канала
        kill(target_pid, SIGUSR1);
    } else if (target_pid == getppid()) {
        // Условие окончания игры проверяется потомком
        printf("Child is going to be terminated\n");
        
        close(fd[1]);
        close(fd[0]);
        //Завершается потомок
        exit(0);
    } else {
        kill(target_pid, SIGUSR1);
    }
}

int main(int argc, char *argv[]) {
    //Организуем канал
    pipe(fd);
    
    //Устанавливаем обработчик сигнала для обоих процессов
    signal(SIGUSR1, sig_handler);

    cnt = 0;

    if (target_pid = fork()) {
        // В этот момент присвание target_pid = fork() уже проработало

        write(fd[1], &cnt, sizeof(cnt)); // Старт синхронизации

        // Предку остаётся только ждать потомка
        while (wait(&status) == -1);

        close(fd[0]);
        close(fd[1]);

        return 0;
    } else {
        // Блокировка до того момента, пока присваение target_pid = fork() не проработает в отце
        
        read(fd[0], &cnt, sizeof(cnt)); // Старт синхронизации

        // Процесс потомок узнаёт pid родителя
        target_pid = getppid();
        
        //Потомок начинает ping pong
        write(fd[1], &cnt, sizeof(cnt));
        kill(target_pid, SIGUSR1);

        while(1);
    }
    return 0;
}
