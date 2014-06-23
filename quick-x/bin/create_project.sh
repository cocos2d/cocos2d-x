#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
TEMPLATE_ROOT=`dirname "$DIR"`/template
php "$DIR/lib/create_project.php" -t "$TEMPLATE_ROOT/PROJECT_TEMPLATE_01" $*
