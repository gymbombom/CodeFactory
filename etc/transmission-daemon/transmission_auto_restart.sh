#!/bin/bash

#transmission-daemon 자동 재실행 스크립트.. 트랜스미션이 자꾸 죽는다....-.-

while :
do
    CHECK_PROCESS=`ps -ef | grep transmission-daemon | grep -v grep | awk '{print $2}'`
    if [ -z $CHECK_PROCESS ]; then
        sudo service transmission-daemon restart
    else
        echo "success"
    fi
    sleep 600
done
