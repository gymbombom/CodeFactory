#/bin/bash

GIT_HOME="/home/git";
GIT_REPOS_ROOT="$GIT_HOME/repo";
GIT_REPOS="$GIT_REPOS_ROOT/$1.git";
GIT=`which git |xargs`;


function usg_print()
{
	echo "<args> repository name"
}


if [ $# = 0 ]; then
	usg_print
	exit 1
fi


if [ $# = 1 -a -d $GIT_REPOS ]; then
	/bin/rm -rf $GIT_REPOS;
else
	usg_print
fi
