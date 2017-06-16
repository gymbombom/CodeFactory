#!/bin/bash

SVN_HOME="/home/svn";
SVN_REPOS_ROOT="$SVN_HOME";
SVN_REPOS="$SVN_HOME/$1";
SVN_DEFAULT_CONF="$SVN_HOME/default";

function usg_print(){
 echo "<args> repository name"
}

if [ $# = 0 ]; then
  usg_print
  exit 1
fi

if [ $# = 1 -a -d $SVN_REPOS ]; then

 /bin/rm -rf  $SVN_REPOS

else
  usg_print
  exit 1
fi