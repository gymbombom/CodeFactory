#/bin/bash

IP=("10.0.0.5" "10.0.0.6" "10.0.0.7")
PWD=`pwd | xargs`;
FILENAME=$1;

for i in ${IP[@]}
do
    scp -r $FILENAME hes@$i:$PWD
done
