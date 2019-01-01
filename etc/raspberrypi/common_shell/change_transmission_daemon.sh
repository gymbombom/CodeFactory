#!/bin/bash


function print_usage() {
    echo "c.sh 1: transmission_daemon start";
    echo "c.sh 2: tblue start";
}

function transmission_chk()
{
        STATUS=`docker ps | grep transmission | awk '{print $1}'`;

        if [ -z $STATUS ]; then
                docker start transmission;
        fi

        PID=`docker exec transmission ps -ef | grep transmission-daemon | awk '{print $2}'`;

        if [ -z $PID ];then
                docker exec transmission service transmission-daemon start;
        fi
}

function tblue_chk()
{
        STATUS=`docker ps | grep tblue | awk '{print $1}'`;

        if [ -z $STATUS ]; then
                docker start tblue;
        fi

        PID=`docker exec tblue ps -ef | grep transmission-daemon | awk '{print $2}'`;

        if [ -z $PID ];then
                docker exec tblue service transmission-daemon start;
        fi
}



case "$1" in
1)
	docker stop tblue;
	transmission_chk
;;
2)
	docker stop transmission;
	tblue_chk
;;

*)
	print_usage
;;
esac
