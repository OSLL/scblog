#!/bin/sh
# $Id$
#-----------------------------------------------------------------------------------

if [ -z "$1" ]; then echo 'Class name:'; read CLASS; else CLASS=$1; fi;

UUID=`uuidgen | tr 'abcdef-' 'ABCDEF_'`
NAME=TEST_${CLASS}_H
GUID=_${NAME}_${UUID}_INCLUDED_
YEAR=`date +%Y`

FTESTCPP="Test_"$CLASS".cpp"
FTESTH="Test_"$CLASS".h"

A="cat <<EOF
`cat Test_CClass.cpp.t`
EOF"

eval "$A" >$FTESTCPP 

A="cat <<EOF
`cat Test_CClass.h.t`
EOF"

eval "$A" >$FTESTH 
