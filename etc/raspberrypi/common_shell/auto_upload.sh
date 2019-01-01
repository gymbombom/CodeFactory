#!/bin/bash

#client variables
CLIENT_PATH="/home/pi/client/*";
CLIENT_BACKUP_PATH="/home/pi/clinet_bk";

#server variables
SERVER_ADDRESS="aaa@111.111.111.111";
SERVER_PORT="22";
SERVER_PATH="/data/svr_path";


scp -P $SERVER_PORT -r $CLIENT_PATH $SERVER_ADDRESS:$SERVER_PATH

mv $CLIENT_PATH $CLIENT_BACKUP_PATH
