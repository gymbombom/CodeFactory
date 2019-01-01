#!/bin/bash

function vsftpd_chk()
{
	STATUS=`docker ps | grep vsftpd | awk '{print $1}'`;

	if [ -z $STATUS ]; then
		docker start vsftpd;
	fi

	PID=`docker exec vsftpd ps -ef | grep vsftpd | awk '{print $2}'`;

	if [ -z $PID ];then
		docker exec vsftpd service vsftpd restart;
	fi
}

function transmission_chk()
{
	STATUS=`docker ps | grep transmission | awk '{print $1}'`;

	if [ -z $STATUS ]; then
		docker start transmission;
	fi

	PID=`docker exec transmission ps -ef | grep transmission-daemon | awk '{print $2}'`;

	if [ -z $PID ];then
		docker exec transmission service transmission-daemon start;
	fi
}

function node_kgs_chk()
{
        STATUS=`docker ps | grep node_kgs | awk '{print $1}'`;

        if [ -z $STATUS ]; then
                docker start node_kgs;
        fi

        PID=`docker exec node_kgs ps -ef | grep express.js | awk '{print $2}'`;

        if [ -z $PID ];then
			docker exec node_kgs nohup /home/node/node_kgs/nodestart.sh &
        fi
}

function svn_chk()
{
        STATUS=`docker ps | grep svn | awk '{print $1}'`;

        if [ -z $STATUS ]; then
                docker start svn;
        fi

        PID=`docker exec svn ps -ef | grep svnserve | awk '{print $2}'`;

        if [ -z $PID ];then
			docker exec svn svnserve -d -r /home/svn/repos
        fi
}

function git_chk()
{
        STATUS=`docker ps | grep git | awk '{print $1}'`;

        if [ -z $STATUS ]; then
                docker start git;
        fi

        PID=`docker exec git ps -ef | grep sshd | awk '{print $2}'`;

        if [ -z $PID ];then
			docker exec git /usr/sbin/sshd
        fi
}

function tblue_chk()
{
        STATUS=`docker ps | grep tblue | awk '{print $1}'`;

        if [ -z $STATUS ]; then
                docker start tblue;
        fi

        PID=`docker exec tblue ps -ef | grep transmission-daemon | awk '{print $2}'`;

        if [ -z $PID ];then
                docker exec tblue service transmission-daemon start;
        fi
}



function multi_transmission_chk()
{
        TRANSMISSION_STATUS=`docker ps | grep transmission  | awk '{print $1}'`;
        TBLUE_STATUS=`docker ps | grep tblue  | awk '{print $1}'`;


        if [ -z $TRANSMISSION_STATUS ]; then

                if [ -z $TBLUE_STATUS ]; then
                        transmission_chk
                else
                        tblue_chk
                fi
        else
                if [ -z $TBLUE_STATUS ]; then
                        transmission_chk
                else
                        docker stop tblue;
                        transmision_chk
                fi
        fi
}


vsftpd_chk
node_kgs_chk
svn_chk
git_chk
multi_transmission_chk
