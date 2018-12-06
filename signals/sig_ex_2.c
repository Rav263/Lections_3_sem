#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


const char *tmp_file = "abc";

void sig_handler(int s) {
    unlink(tmp_file);
    printf("Удаление временного файла из-за получения сигнала SIGINT\n");
    exit(1);
    // Удаление временного файла при получении сигнала SIGINT
    // В случае отсутствия временнного файлы unlink вернёт -1
}

int main(int argc, char *argv[]) {
    printf("Создаётся временный файл используется и удаляется за 15 секунд,\n");
    printf("при отправки SIGINT временный файл преждевременно удаляется\n");
    signal(SIGINT, sig_handler);

    // Создание временного файла
    printf("Создаём временный файл\n");
    creat(tmp_file, 0666);
    sleep(5);
    printf("Использование временного файла\n");
    sleep(10);
    printf("При нормальном исполнении программы удаление временного файла\n");
    unlink(tmp_file);
    return 0;
}
