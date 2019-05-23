#!/bin/bash

function usg_print()
{
	echo "find.sh [find String];";
	exit 0;
}

if [ $# = 0 ]; then
	usg_print
fi


find . -name "*" | xargs grep -rn  $1 2> /dev/null;
