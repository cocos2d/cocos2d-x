#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
export QUICK_V3_ROOT=`cat ~/.QUICK_V3_ROOT`
TEMPLATE_ROOT=`dirname "$DIR"`/templates
php "$DIR/lib/create_project.php" -t "$TEMPLATE_ROOT/lua-template-quick" $*
