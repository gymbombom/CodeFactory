#!/bin/bash

#define variables
SVN_HOME="/home/svn";
SVN_REPOS_ROOT="$SVN_HOME";
SVN_REPOS="$SVN_HOME/$1";
SVN_DEFAULT_CONF="$SVN_HOME/default";
SVNADMIN=`which svnadmin |xargs`;

#usage print function
function usg_print()
{
	echo "<args> repository name"
}


if [ $# = 0 ]; then
	usg_print
  	exit 1
fi

if [ $# = 1 ]; then
	#1. repository create
   	#/usr/bin/svnadmin create --fs-type fsfs /home/svn/repos/$1
  	$SVNADMIN create --fs-type fsfs $SVN_REPOS;

  	#2. backup config
  	/bin/mkdir $SVN_REPOS/conf/backup

  	/bin/cp $SVN_REPOS/conf/authz $SVN_REPOS/conf/backup/authz_backup
  	/bin/cp $SVN_REPOS/conf/passwd $SVN_REPOS/conf/backup/passwd_backup
  	/bin/cp $SVN_REPOS/conf/svnserve.conf $SVN_REPOS/conf/backup/svnserve.conf_backup

  	#3. default file setting
  	/bin/cp $SVN_DEFAULT_CONF/authz $SVN_REPOS/conf/authz
  	/bin/cp $SVN_DEFAULT_CONF/passwd $SVN_REPOS/conf/passwd
  	/bin/cp $SVN_DEFAULT_CONF/svnserve.conf $SVN_REPOS/conf/svnserve.conf

   	# 4.config file value change
else
	usg_print
  	exit 1
fi
