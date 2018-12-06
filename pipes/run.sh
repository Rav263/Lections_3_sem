#! /bin/bash

function help(){
    echo "Для печати этого сообщения используйте ./run.sh  help"
    echo "Для вывода кода каждой программы перед запуском используйте ./run.sh print"
    echo "Для удаления всех ненужных бинарников используйте ./run.sh clear"
    echo ""
}


function pause(){
   read -p "$*"
}


function run_prog(){
    echo "Пример на сигналы для самостоятельного запуска используйте ./$2"
    if [ "$1" == "print" ]
    then
        echo ""
        echo ""
        cat $2.c
        echo ""
        echo ""
        pause "Нажмите ENTER для запуска"
    fi

    gcc -std=gnu11 $2.c -o $2
    echo ""
    echo ""
    ./$2
    echo ""
    echo ""
    pause "Нажмите ENTER для продолжения"
}


if [ "$1" == "help" ]
then
    help
fi

if [ "$1" == "clear" ]
then
    rm pipe_ex_1 pipe_ex_2 pipe_ex_3 pipe_ex_4 pipe_ex_5
    exit 0
fi

run_prog "$1" pipe_ex_1
run_prog "$1" pipe_ex_2
run_prog "$1" pipe_ex_3
run_prog "$1" pipe_ex_4
run_prog "$1" pipe_ex_5

