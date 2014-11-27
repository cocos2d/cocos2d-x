#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
export QUICK_V3_ROOT=`cat ~/.QUICK_V3_ROOT`
php "$QUICK_V3_ROOT/quick/bin/lib/build_apk.php" -pdir $DIR $*
