#!/bin/bash
source ./header.sh

function usg_print()
{
	echo "<args> repository name"
}

if [ $# = 0 ]; then
	usg_print
	exit 1
fi

if [ $# = 1 ]; then

	# 1. repository create
	$SVNADMIN create --fs-type fsfs $SVN_REPOS;

	# 2. default conf setting
	echo "$DEFAULT_SVN_USER = $DEFAULT_SVN_USER" >> $SVN_REPOS/conf/passwd
	#cat "lik = lik" >> $SVN_REPOS/conf/svnserve.conf
	sed -i '8a\anon-access = read' $SVN_REPOS/conf/svnserve.conf | cat -n
	sed -i '9a\auth-access = write' $SVN_REPOS/conf/svnserve.conf |cat -n
	sed -i '10a\password-db = passwd' $SVN_REPOS/conf/svnserve.conf | cat -n

	# 3. default Directory create
	svn mkdir svn://127.0.0.1/$1/trunk -m "trunk Directory Create" --non-interactive --trust-server-cert --username $DEFAULT_SVN_USER --password $DEFAULT_SVN_PASSWORD
	svn mkdir svn://127.0.0.1/$1/branches -m "branches Directory Create" --non-interactive --trust-server-cert --username $DEFAULT_SVN_USER --password $DEFAULT_SVN_PASSWORD
	svn mkdir svn://127.0.0.1/$1/tags -m "tags Directory Create" --non-interactive --trust-server-cert --username $DEFAULT_SVN_USER --password $DEFAULT_SVN_PASSWORD
else
	usg_print
	exit 1
fi