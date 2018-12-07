#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// Декларация структуры сообщения
struct 
{
    long mtype;
    char data[256];
} Message;

int main(int argc, char *argv[]) {
    key_t key;
    int msgid;
    char str[256];

    // Получаем уникальный ключб однозначно определяющий доступ к ресурсу данного типа
    key = ftok("/usr/bin/wc", 's');
    
    // Создаём новую очередь сообщений с 0666 -- правами доступа
    msgid = msgget(key, 0666 | IPC_CREAT | IPC_EXCL);
    
    // запускаем вечный кайф (цикл)
    while (1) {
        fgets(str, 256, stdin); // Читаем строку из стандартного потока ввода

        strcpy(Message.data, str); // Копируем её в буффер сообщения

        // анализируем первый прочитанный символ
        // Дисклеймер Так как автор данного кода не признаёт switch он был изменён на конструкцию if else
        if (str[0] == 'a' || str[0] == 'A') {
            // Устанавливаем тип 1 для процесса А
            Message.mtype = 1;
            
            // Посылаем сообщение в очередь
            msgsnd(msgid, (struct msgbuf *) (&Message), strlen(str) + 1, 0);
        } else if (str[0] == 'b' || str[0] == 'B') {
            // Устанавливаем тип 2 для процесса B
            Message.mtype = 2;
            
            // Посылаем сообщение в очередь
            msgsnd(msgid, (struct msgbuf *) (&Message), strlen(str) + 1, 0);
        } else if (str[0] == 'q' || str[0] == 'Q') {
            Message.mtype = 1;
            msgsnd(msgid, (struct msgbuf *) (&Message), strlen(str) + 1, 0);
            Message.mtype = 2;
            msgsnd(msgid, (struct msgbuf *) (&Message), strlen(str) + 1, 0);
        
            // Ждём получения сообщения процессами
            sleep(2);

            // Уничтожаем очередь
            msgctl(msgid, IPC_RMID, NULL);
            exit(0);
        }
    }
}
