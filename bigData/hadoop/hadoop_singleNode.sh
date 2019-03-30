#!/bin/bash

function print_usage() {
    echo "start)";
    echo "stop)";
}


case "$1" in

        start)
                /home/hadoop/hadoop-2.7.2/sbin/hadoop-daemon.sh start namenode;
                /home/hadoop/hadoop-2.7.2/sbin/hadoop-daemon.sh start datanode;
        ;;
        stop)
                /home/hadoop/hadoop-2.7.2/sbin/hadoop-daemon.sh stop datanode;
                /home/hadoop/hadoop-2.7.2/sbin/hadoop-daemon.sh stop namenode;
        ;;

        *)
                print_usage
        ;;
esac
