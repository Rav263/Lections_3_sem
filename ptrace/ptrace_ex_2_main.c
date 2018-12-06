#include <stdio.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    int status;
    struct user_regs_struct REG;

    if ((pid = fork()) == 0) {
        // Находимся в процессе потомке, разрешаем трассировку
        ptrace(PTRACE_TRACEME, 0, 0, 0);

        // Замещаем тело процесса
        execl("./ptrace_ex_2_tr", "ptrace_ex_2_tr", NULL);
        // Здесь процесс потомок будет остановлен с сигналом SIG_TRAP,
        // ожидая команды для продолжения от управляющего процесса
    }
    // В процессе родителе
    while (1) {
        // Ждём, когда отлаживаемый процесс приостановится
        wait(&status);
        
        // Читаем содержимое регистров отлаживаемого процесса
        ptrace(PTRACE_GETREGS, pid, &REG, &REG);

        // Выводим статус отлаживаемого процесса, номер сигнала, котороый его остановил
        // И значение прочитанных регистров
        //
        // Здесь используются регистры и они зависят от вашей системы и архитектуры, 
        // так что программа может не собираться
        printf("signal = %d, status = %#x, RDI=%#x, RSP=%#x\n", WSTOPSIG(status), status, REG.rdi, REG.rsp);

        if (WSTOPSIG(status) != SIGTRAP) {
            if (!WIFEXITED(status)) {
                // Завершаем выполнение трассируемого процесса
                ptrace(PTRACE_KILL, pid, 0, 0);
            }

            break;
        }

        // Разрешаем выполнение трассируемому процессу
        ptrace(PTRACE_CONT, pid, 0, 0);
    }

}
