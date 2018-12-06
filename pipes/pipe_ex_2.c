#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int fd[2];

    pipe(fd);

    if (fork()) {
        close(fd[0]);
        char buffer[81];
        
        printf("введите строку длинной не более 80 символов: ");
        scanf("%s", buffer);
        
        printf("Эта строка будет отправлена сыну\n");
        
        write(fd[1], buffer, strlen(buffer) + 1);
        close(fd[1]);
    } else {
        close(fd[1]);

        char buffer[81];
        
        while (read(fd[0], buffer, 81)) {
            printf("Сын: %s\n", buffer);
        }

        close(fd[0]);
    }

    return 0;
}
