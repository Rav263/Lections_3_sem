#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <time.h>


#define N 5 //Количество философов
#define LEFT (i-1)%N
#define RIGHT (i+1)%N


//Состояния философа
#define THINKING 0 // Думает
#define HUNGRY 1   // Голоден
#define EATING 2   // Ест


typedef int semaphore; // Определяем тип семафора

int state[N]; // Массив состояний философов

semaphore mutex = 1; // Семафор для доступа  в критическую секцию

semaphore s[N]; // Массив семафоров по одному на каждого философа


void Think(int);
void TakeForks(int);
void Eat(int);
void PutForks(int);
void Test(int);

void up(semaphore *sem) { // Так как нормальная реализация семафоров будет рассказaна
                          // на лекциях позже, это моя кривая неоптимизированная версия
                          // Не принимать за истину в последней инстанции.
    *sem += 1;
}

void down(semaphore *sem) {
    while (*sem <= 0) {
        usleep(1000000);
    }

    *sem -= 1;
}



void Philosopher(int i) {
    while (1) {
        Think(i);
        TakeForks(i);
        Eat(i);
        PutForks(i);
    }
}

void TakeForks(int i){
    down(&mutex);
    
    state[i] = HUNGRY;
    Test(i);
    
    up(&mutex);
    down(&(s[i]));
}


void Eat(int i) {
    printf("Philosopher %d eating\n", i);
    fflush(stdout);
    usleep(rand() % 1000000);
}

void Think(int i) {
    printf("Philosopher %d thinking\n", i);
    fflush(stdout);
    usleep(rand() % 1000000);
}


void PutForks(int i) {
    down(&mutex);

    state[i] = THINKING;

    Test(LEFT);
    Test(RIGHT);

    up(&mutex);
}


void Test(int i) {
    if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[i] = EATING;
        usleep(100000);
        up(&s[i]);
    }
}


int main(void) {
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        if (!fork()) {
            Philosopher(i);
            return 0;
        }
    }

    for (int i = 0; i < N; i++) {
        wait(NULL);
    }
}   
