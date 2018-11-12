#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    execl("/bin/ls", "ls", "-l", NULL);
    /* Или execlp("ls", "ls", "-l", NULL); */

    printf("Это будет напечатано в случае неудачного обращения к предыдущей функции\n");
    return 0;
}
