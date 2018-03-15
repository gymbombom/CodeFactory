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

if [ $# = 1 -a -d $SVN_REPOS ]; then
    /bin/rm -rf  $SVN_REPOS
else
    usg_print
    exit 1
fi