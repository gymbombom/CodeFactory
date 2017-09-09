#!/bin/bash

#input file example
#       ip          version     community       oid
####################################################
# 111.222.333.444       2       public  sysuptime

return_val=1

#usage print function
function usg_print()
{
	echo "snmp.sh <input_file_name>"
	exit 1
}


function args_check()
{
	if [ $# = 0 ]; then
		return_val=1
    	usg_print
    elif [ $# = 1 ]; then
    	return_val=0
    else
    	return_val=1
    	usg_print
    fi
}

function snmp_version_check()
{
	if [ $1 -eq "1" ]; then
		return_version="1"
	elif [ $1 -eq "2" ]; then
		return_version="2c"
	else
		#대부분 장비가 version 2이므로 인자가 없을 경우 2버전이라고 생각
		return_version="2c"
	fi
	echo "$return_version"
}

function oid_check()
{
	if [ $1 = "ifname" ]; then    #ifName
		return_oid=".1.3.6.1.2.1.31.1.1.1.1"
	elif [ $1 = "sysuptime" ]; then
		return_oid=".1.3.6.1.2.1.1.3"
    elif [ $1 = "bridge" ]; then    #dot1dtpfdbport
		return_oid=".1.3.6.1.2.1.17.4.3.1.2"
    elif [ $1 = "arp" ]; then    #ipNetToMediaPhysAddress
		return_oid=".1.3.6.1.2.1.4.22.1.2"
	else
		echo "invalid oid" >> snmp_result.log
	fi
	echo "$return_oid"
}

#run program
args_check $1

if [ $return_val -eq 0 ]; then
	cat $1 | \
	while read ip version community oid
	do
		return_version=$(snmp_version_check $version)
		echo "$ip $version $community $oid" >> snmp_result.log
		return_oid=$(oid_check $oid)
		snmpwalk -v $return_version -c $community $ip $return_oid >> snmp_result.log
		echo "===========================================================================" >> snmp_result.log
	done
fi
