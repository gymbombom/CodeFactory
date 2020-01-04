#!/bin/bash

function vsftpd_chk()
{
	STATUS=`docker ps | grep vsftpd | awk '{print $1}'`;

	if [ -z $STATUS ]; then
		docker start vsftpd;
	fi

	PID=`docker exec vsftpd ps -ef | grep vsftpd | grep -v grep | awk '{print $1}'`;

	if [ -z $PID ];then
#		docker exec vsftpd nohup /usr/sbin/vsftpd  /home/vsftpd/share/conf/vsftpd.conf > /home/vsftpd/share/logs/vsftpd.log &;
		echo "develomenting..."
	fi
}

function transmission_chk()
{
	STATUS=`docker ps | grep transmission | awk '{print $1}'`;

	if [ -z $STATUS ]; then
		docker start transmission;
	fi

	PID=`docker exec transmission ps -ef | grep transmission-daemon | grep -v grep | awk '{print $1}'`;

	if [ -z $PID ];then
		docker exec transmission /usr/bin/transmission-daemon -g /home/transmission/share/conf;
	fi
}

function node_kgs_chk()
{
        STATUS=`docker ps | grep node_kgs | awk '{print $1}'`;

        if [ -z $STATUS ]; then
                docker start node_kgs;
        fi

        PID=`docker exec node_kgs ps -ef | grep express.js | grep -v grep  | awk '{print $1}'`;

        if [ -z $PID ];then
			docker exec node_kgs /home/node_kgs/src/shell/nodestart.sh
        fi
}

function svn_chk()
{
        STATUS=`docker ps | grep svn | awk '{print $1}'`;

        if [ -z $STATUS ]; then
                docker start svn;
        fi

        PID=`docker exec svn ps -ef | grep svnserve | grep -v grep | awk '{print $1}'`;

        if [ -z $PID ];then
			docker exec svn svnserve -d -r /home/svn/share/repos
        fi
}

function git_chk()
{
        STATUS=`docker ps | grep git | awk '{print $1}'`;

        if [ -z $STATUS ]; then
                docker start git;
        fi

        PID=`docker exec git ps -ef | grep sshd | grep -v grep |  awk '{print $1}'`;

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

function snmpd_chk()
{
        STATUS=`docker ps | grep snmp_test | awk '{print $1}'`;

        if [ -z $STATUS ]; then
                docker start snmp_test;
        fi

        PID=`docker exec snmp_test ps -ef | grep snmpd | awk '{print $2}'`;

        if [ -z $PID ];then
                #docker exec vsftpd service vsftpd restart;
                docker exec snmp_test /usr/sbin/snmpd
        fi
}


vsftpd_chk
transmission_chk
node_kgs_chk
svn_chk
git_chk
#multi_transmission_chk
#snmpd_chk
