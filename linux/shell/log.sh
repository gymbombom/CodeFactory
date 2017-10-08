#!/bin/bash

LOG_DIR="/home/pi/Desktop/log/"
LOG_FILENAME="log_$(date +%Y%m%d).dat"

   echo "$(date +%Y%m%d%H%M)" >> $LOG_DIR$LOG_FILENAME
   vcgencmd measure_temp >>  $LOG_DIR$LOG_FILENAME
   free >> $LOG_DIR$LOG_FILENAME
   /usr/bin/top -n 1 -b | grep Cpu >> $LOG_DIR$LOG_FILENAME
   echo "=====================================================" >> $LOG_DIR$LOG_FILENAME
