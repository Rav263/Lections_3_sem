#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

struct
{
    long mtype;
    char data[256];
} Message;

int main(int argc, char *argv[]) {
    int type = atoi(argv[1]);
    
    key_t key;
    int msgid;
    
    // получаем ключ по тем же параметрам
    key = ftok("/usr/bin/wc", 's');
    
    // Подключаемся к очереди сообщений
    msgid = msgget(key, 0666);

    // Запускаем вечный цикл
    while (1) {
        // Читаем сообщения с типом 1 для процесса А
        msgrcv(msgid, (struct msgbuf *) (&Message), 256, type, 0);
        printf("son %d: %s", type, Message.data + 1);

        if (Message.data[0] == 'q' || Message.data[0] == 'Q') {
            break;
        }
    }

    return 0;
}
