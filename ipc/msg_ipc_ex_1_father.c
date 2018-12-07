#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int pid_1 = fork();

    if (pid_1 == 0) {
        sleep(1);
        printf("Сыновья запущены\n");
        int pid_2 = fork();
        if (pid_2 == 0) execl("./msg_ipc_ex_1_son", "msg_ipc_ex_1_son", "1", NULL);
        else execl("./msg_ipc_ex_1_son", "msg_ipc_ex_1_son", "2", NULL);
        printf("YOU ARE LOX\n");
    } else {
        printf("Отец запущен\n");
        execl("./msg_ipc_ex_1_main", "msg_ipc_ex_1_main", NULL);
    }
}
