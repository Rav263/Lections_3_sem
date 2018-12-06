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

    if [ "$2" != "sig_ex_5" ]
    then 
        gcc -std=gnu11 $2.c -o $2
        echo ""
        echo ""
        ./$2
        echo ""
        echo ""
    fi
    pause "Нажмите ENTER для продолжения"
}


if [ "$1" == "help" ]
then
    help
fi

if [ "$1" == "clear" ]
then
    rm sig_ex_1 sig_ex_2 sig_ex_3 sig_ex_4 pos_sig_ex_1 pos_sig_ex_2
    exit 0
fi

run_prog "$1" sig_ex_1
run_prog "$1" sig_ex_2
run_prog "$1" sig_ex_3
run_prog "$1" sig_ex_4
run_prog "$1" sig_ex_5
run_prog "$1" pos_sig_ex_1
run_prog "$1" pos_sig_ex_2


