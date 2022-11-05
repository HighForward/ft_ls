#!/usr/bin/env bash

ERROR=0
SUCCESS=0

log_success() {
  echo "SUCCESS: " $1
  SUCCESS=$((SUCCESS+1))
}

log_error() {
    echo "ERROR: " $1
      ERROR=$((ERROR+1))
}

assert_cmd () {

  REAL=$(ls $1 | wc -l)
  FAKE=$(./ft_ls $1 | wc -l)

  [[ $REAL -eq $FAKE ]] && log_success $1 || log_error $1
}


assert_cmd "/bin -l"


echo "TOTAL ERROR: " $ERROR
echo "TOTAL SUCCESS: " $SUCCESS

#if [ $(ls -l | wc -l) == $(./ft_ls -l | wc -l) ]; then
#	echo "OK"
#else
#	echo "NOT OK"
#fi