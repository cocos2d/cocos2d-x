#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
source $DIR/_setenv.sh
TEMPLATE_ROOT=`dirname "$DIR"`/templates
php "$DIR/lib/create_project.php" -t "$TEMPLATE_ROOT/lua-template-quick" $*
