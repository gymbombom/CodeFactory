#/bin/bash

GIT_HOME="/home/git";
GIT_REPOS_ROOT="$GIT_HOME/repo";
GIT_REPOS="$GIT_REPOS_ROOT/$1.git";
GIT=`which git |xargs`;


function usg_print(){
 echo "<args> repository name"
}


if [ $# = 0 ]; then
  usg_print
  exit 1
fi


if [ $# = 1 ]; then

  /bin/mkdir $GIT_REPOS;
  /bin/chmod 755 $GIT_REPOS;
  cd $GIT_REPOS;
  $GIT init --bare --shared;

else
  usg_print
fi