#!/usr/bin/env bash

ERROR=0
SUCCESS=0

log_success() {
  echo "SUCCESS:" $1
  SUCCESS=$((SUCCESS+1))
}

log_error() {
    echo "ERROR:" $1
      ERROR=$((ERROR+1))
}

assert_paths () {

  REAL=$(ls $1 2> /dev/null | wc -w )
  FAKE=$(./ft_ls $1 2> /dev/null | wc -w)

  [ "$REAL" = "$FAKE" ] && log_success "$1" || log_error "$1"
}

assert_unit () {

  REAL=$(ls $1 2> /dev/null | wc -w )
  FAKE=$(./ft_ls $1 2> /dev/null | wc -w)

  [ "$REAL" = "$FAKE" ] && log_success "$1" || log_error "$1"
}

assert_paths " -laRts"


assert_paths " -l"
assert_paths "/bin -l"
assert_paths "/dev -l"
assert_paths "/etc -l"
assert_paths "/dev -la"
assert_paths "/dev -Ra"
assert_paths "/dev /bin -Ra"

assert_unit "test_basic_dir -l"
assert_unit "test_basic_file -l"
assert_unit "test_empty -l"
assert_unit "test_symlink -l"
assert_unit "test_recursive -Rl"

echo "TOTAL ERROR: " $ERROR
echo "TOTAL SUCCESS: " $SUCCESS
