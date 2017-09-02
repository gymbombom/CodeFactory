#!/bin/bash

PID=`ps -ef | grep svnserve | grep -v grep |awk '{print $2}'`;

kill -9 $PID
