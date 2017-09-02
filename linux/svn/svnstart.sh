#!/bin/bash

SVNSERVE=`which svnserve | xargs`;

$SVNSERVE -d  -r /home/svn
