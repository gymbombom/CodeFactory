#/bin/bash

#client(pwd)---scp---->server[@](client_pwd)

#server variables
SERVER_IP=("10.0.0.5" "10.0.0.6" "10.0.0.7")
SERVER_USER="user"

#client variables
CLIENT_PWD=`pwd | xargs`;
CLIENT_FILENAME=$1;

#run script
for i in ${SERVER_IP[@]}
do
    scp -r $CLIENT_FILENAME $SERVER_USER@$i:$CLIENT_PWD
done
