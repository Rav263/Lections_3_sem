#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_CNT 10
volatile int target_pid;
int cnt;
int fd[2];
int status;

void sig_handler(int s) {
    if (cnt < MAX_CNT) {
        read(fd[0], &cnt, sizeof(cnt));
        
        printf("pid = %d cnt = %d\n", target_pid, cnt);
        
        cnt++;
        write(fd[1], &cnt, sizeof(cnt));
        
        kill(target_pid, SIGUSR1);
    } else {
        if (target_pid == getppid()) {
            printf("Child ig going to be terminated\n");
            
            close(fd[0]);
            close(fd[1]);

            exit(0);
        } else {
            kill(target_pid, SIGUSR1);
        }
    }
}

void init(int s) {
    target_pid = getppid();
    printf("target_pig: %d\n", target_pid);


    write(fd[1], &cnt, sizeof(cnt));
    kill(target_pid, SIGUSR1);
}


int main(int argc, char *argv[]) {
    pipe(fd);

    signal(SIGUSR2, init);
    signal(SIGUSR1, sig_handler);

    cnt = 0;

    if ((target_pid = fork()) > 0) {
        // В этот момент присваение target_pid = fork() уже проработало
        // Отсылаем сыну сигнал для старта
        
        kill(target_pid, SIGUSR2);
        while (wait(&status) == -1);

        printf("Parent is going to be terminated\n");
        close(fd[1]);
        close(fd[0]);

        return 0;
    } else {
        target_pid = getppid(); // БЕЗ ЭТОЙ СТРОЧКИ target_pid ПОЛУЧАЕМЫЙ СЫНОМ В init НЕ СОХРАНЯЛСЯ 
        for(;;);
    }
}
