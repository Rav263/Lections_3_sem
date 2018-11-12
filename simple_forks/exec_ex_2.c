#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    /* Используется при заранее неизвестном количестве аргументов */

    char *pv[] = {"cc", "-o", "ter", "ter.c", NULL};

    if(!fork()) execv("/bin/cc", pv);
    execlp("./ter", "./ter", 0);
}
