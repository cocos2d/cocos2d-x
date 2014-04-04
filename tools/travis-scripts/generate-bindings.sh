#!/bin/bash

# Generate Lua bindings for Cocos2D-X
# ... using Android NDK system headers
# ... and push these changes to remote repos

# Dependencies
#
# For bindings generator:
# (see tools/tolua/genbindings.py for the defaults used if the environment is not customized)
#
#  * $PYTHON_BIN
#  * $CLANG_ROOT
#  * $NDK_ROOT
#

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PROJECT_ROOT="$DIR/../.."
TOLUA_ROOT="$PROJECT_ROOT/tools/tolua"
AUTO_GENERATED_DIR="$PROJECT_ROOT/cocos/scripting/lua-bindings/auto"
COMMITTAG="[AUTO]: updating luabinding automatically"
ELAPSEDSECS=`date +%s`
COCOS_BRANCH="update_lua_bindings_$ELAPSEDSECS"
COCOS_ROBOT_REMOTE="https://${GH_USER}:${GH_PASSWORD}@github.com/${GH_USER}/cocos2d-x.git"
PULL_REQUEST_REPO="https://api.github.com/repos/cocos2d/cocos2d-x/pulls"
FETCH_REMOTE_BRANCH="develop"
COMMIT_PATH="cocos/scripting/lua-bindings/auto"

# Exit on error
set -e

if [ "$PLATFORM"x = "ios"x ]; then
    mkdir -p $HOME/bin
    pushd $HOME/bin
    curl -O http://pyyaml.org/download/pyyaml/PyYAML-3.10.zip
    unzip PyYAML-3.10.zip 2> /dev/null > /dev/null
    cd PyYAML-3.10
    sudo python setup.py install 2> /dev/null > /dev/null
    cd ..
    curl -O https://pypi.python.org/packages/source/C/Cheetah/Cheetah-2.4.4.tar.gz
    tar xzf Cheetah-2.4.4.tar.gz
    cd Cheetah-2.4.4
    sudo python setup.py install 2> /dev/null > /dev/null
    popd
elif [ $(command -v apt-get) ]; then
    sudo apt-get --force-yes --yes install python-yaml python-cheetah
fi

generate_bindings_glue_codes()
{
    echo "Create auto-generated luabinding glue codes."
    pushd "$TOLUA_ROOT"
    ./genbindings.py
    popd
}

if [ "$GEN_BINDING"x != "YES"x ]; then
    generate_bindings_glue_codes
    exit 0
fi

pushd "$PROJECT_ROOT"
#Set git user for cocos2d-lua repo
git config user.email ${GH_EMAIL}
git config user.name ${GH_USER}
popd

rm -rf "$AUTO_GENERATED_DIR"
mkdir "$AUTO_GENERATED_DIR"

# 1. Generate LUA bindings
generate_bindings_glue_codes

echo
echo Bindings generated successfully
echo

echo
echo Using "'$COMMITTAG'" in the commit messages
echo


echo Using "$ELAPSEDSECS" in the branch names for pseudo-uniqueness

# 2. In Bindings repo, Check if there are any files that are different from the index

pushd "$PROJECT_ROOT"

# Run status to record the output in the log
git status

echo
echo Comparing with origin HEAD ...
echo

git fetch origin ${FETCH_REMOTE_BRANCH}

# Don't exit on non-zero return value
set +e
git diff FETCH_HEAD --stat --exit-code ${COMMIT_PATH}

DIFF_RETVAL=$?
if [ $DIFF_RETVAL -eq 0 ]
then
    echo
    echo "No differences in generated files"
    echo "Exiting with success."
    echo
    exit 0
else
    echo
    echo "Generated files differ from HEAD. Continuing."
    echo
fi

# Exit on error
set -e

git add -f --all "$AUTO_GENERATED_DIR"
git checkout -b "$COCOS_BRANCH"
git commit -m "$COMMITTAG"

#Set remotes
git remote add upstream "$COCOS_ROBOT_REMOTE" 2> /dev/null > /dev/null

echo "Pushing to Robot's repo ..."
git push -fq upstream "$COCOS_BRANCH" 2> /dev/null

# 7. 
echo "Sending Pull Request to base repo ..."
curl --user "${GH_USER}:${GH_PASSWORD}" --request POST --data "{ \"title\": \"$COMMITTAG\", \"body\": \"\", \"head\": \"${GH_USER}:${COCOS_BRANCH}\", \"base\": \"${TRAVIS_BRANCH}\"}" "${PULL_REQUEST_REPO}" 2> /dev/null > /dev/null

popd
