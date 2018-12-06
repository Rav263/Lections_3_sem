#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *s = "channel";
    char buffer[80];

    int pipes[2];

    pipe(pipes); // Создаём неименованный канал
   
    write(pipes[1], s, strlen(s) + 1); // пишем туда
    read(pipes[0], buffer, strlen(s) + 1); // Читаем от туда
    
    close(pipes[0]); // Закрываем
    close(pipes[1]);

    printf("%s\n", buffer);

    return 0;
}
