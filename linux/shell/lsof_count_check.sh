#!/bin/bash
#lsof count check script

while :
do
    PID=`ps -ef | grep transmission-daemon | grep -v grep | awk '{print $2}'`;
    date >> tranmission_`date '+%Y%m%d'`;
    ls -l /proc/$PID/fd/ | wc -l >> tranmission_`date '+%Y%m%d'`;
    echo "=================================================" >> tranmission_`date '+%Y%m%d'`;
    sleep 600;
done
