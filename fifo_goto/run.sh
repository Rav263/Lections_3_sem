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
        if [ "$2" == "fifo_father" ]
        then
            echo ""
            echo ""
            pause "Нажмите ENTER для печати файла клиента"
            echo "CLIENT FILE"
            cat fifo_ex_client.c
            echo ""
            echo ""
            pause "Нажмите ENTER для печати файла сервера"
            echo "SERVER FILE"
            cat fifo_ex_server.c
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
    rm fifo_ex_server fifo_ex_client fifo_father goto
    exit 0
fi

gcc -std=gnu11 fifo_ex_client.c -o fifo_ex_client
gcc -std=gnu11 fifo_ex_server.c -o fifo_ex_server
run_prog "$1" fifo_father
run_prog "$1" goto
