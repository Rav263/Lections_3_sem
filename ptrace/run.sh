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
        if [ "$2" == "ptrace_ex_2_main" ]
        then
            echo ""
            echo ""
            pause "Нажмите ENTER для печати файла клиента"
            echo "TRASSING_FILE"
            cat ptrace_ex_2_tr.c
        fi
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
    rm ptrace_ex_1 ptrace_ex_2_tr ptrace_ex_2_main
    exit 0
fi

gcc -std=gnu11 ptrace_ex_2_tr.c -o ptrace_ex_2_tr
run_prog "$1" ptrace_ex_1
run_prog "$1" ptrace_ex_2_main
