#!/bin/bash

#prog=./sort_hello
prog="$1"

if [ -z "${prog}" ]; then
  echo "USAGE: $0 prog_name"
  exit 1
fi

set -e 

for i in $(seq 99); do

  echo -ne "test: $i ... " 
  seq  10 $i | gshuf | $prog | sort -c -n
  echo " OK"
done

