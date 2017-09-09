#!/bin/bash

#client<----server

#server variables
SERVER_ADDRESS="111.222.333.444"
SERVER_PORT="21"

FTP_USER="user"
FTP_PASSWORD="password"

SERVER_DIR="/home/server/dir"
SERVER_TARGET_FILE="get_file_name"

#client variables
CLIENT_DIR="/home/client/dir"
FTP_LOGFILE_NAME="logfile_name"

cd $CLIENT_DIR

ftp -n $SERVER_ADDRESS $SERVER_PORT << End-Of-Session > $FTP_LOGFILE_NAME
    user $FTP_USER $FTP_PASSWORD
    bin
    cd $SERVER_DIR
    get $SERVER_TARGET_FILE
    bye
End-Of-Session

exit 0
