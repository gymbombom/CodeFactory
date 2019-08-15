#!/bin/bash

HADAAOP_HOME="/home/hadoop/hadoop-2.7.2";

function print_usage() {
    echo "start)";
    echo "stop)";
}


case "$1" in

        start)
                $HADOOP_HOME/sbin/hadoop-daemon.sh start namenode;
                $HADOOP_HOME/sbin/hadoop-daemon.sh start datanode;
        ;;
        stop)
                $HADOOP_HOME/sbin/hadoop-daemon.sh stop datanode;
                $HADOOP_HOME/sbin/hadoop-daemon.sh stop namenode;
        ;;

        *)
                print_usage
        ;;
esac
