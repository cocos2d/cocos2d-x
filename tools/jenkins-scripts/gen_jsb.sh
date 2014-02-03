#!/bin/bash

# Generate JS and Lua bindings for Cocos2D-X
# ... using Android NDK system headers
# ... and automatically update submodule references
# ... and push these changes to remote repos

# Dependencies
#
# For bindings generator:
# (see ../../../tojs/genbindings.sh and ../../../tolua/genbindings.sh
# ... for the defaults used if the environment is not customized)
#
#  * $PYTHON_BIN
#  * $CLANG_ROOT
#  * $NDK_ROOT
#
echo "[test]start generate js binding..."
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
COCOS2DX_ROOT="$DIR"/../..
TOJS_ROOT=$COCOS2DX_ROOT/tools/tojs
TOLUA_ROOT=$COCOS2DX_ROOT/tools/tolua
GENERATED_WORKTREE="$COCOS2DX_ROOT"/cocos/scripting/auto-generated


# Exit on error
set -e

generate_bindings_glue_codes()
{
    echo "Create auto-generated jsbinding glue codes."
    pushd "$TOJS_ROOT"
    ./genbindings.sh
    popd

    echo "Create auto-generated luabinding glue codes."
    pushd "$TOLUA_ROOT"
    ./genbindings.sh
    popd
}

# Update submodule of auto-gen Binding repo.
pushd "$GENERATED_WORKTREE"

echo "Delete all directories and files except '.git' and 'README.md'."
ls -a | grep -E -v ^\[.\]\{1,2\}$ | grep -E -v ^\.git$ | grep -E -v ^README\.md$ | xargs -I{} rm -rf {}
popd



# 1. Generate JS bindings
generate_bindings_glue_codes

echo
echo Bindings generated successfully
echo


