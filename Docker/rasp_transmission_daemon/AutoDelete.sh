#!/bin/sh

ID="pi";
PASSWORD="";
PORT="9091";

SERVER="-p $PORT -n $ID:$PASSWORD"
TORRENTLIST=`transmission-remote $SERVER -l | sed -e '1d;$d;s/^ *//' | sed '/Sum/d' | awk '{print $1}'`

#SERVER="$PORT --auth $ID:$PASSWORD"
#TORRENTLIST=`transmission-remote $SERVER --list | sed -e '1d;$d;s/^ *//' | cut --only-delimited --delimiter=" " --fields=1`

for TORRENTID in $TORRENTLIST
do
    DL_COMPLETED=`transmission-remote $SERVER --torrent $TORRENTID --info | grep "Percent Done: 100%"`
    STATE_STOPPED=`transmission-remote $SERVER --torrent $TORRENTID --info | grep "State: Seeding\|Stopped\|Finished\|Idle"`
    if [ "$DL_COMPLETED" ] && [ "$STATE_STOPPED" ]; then
        transmission-remote $SERVER --torrent $TORRENTID --remove
    fi
done 
