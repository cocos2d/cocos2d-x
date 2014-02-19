#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
COCOS2DX_ROOT="$DIR"/../..
COCOSFILES_CREATOR_ROOT=$COCOS2DX_ROOT/tools/project-creator/config-create
COMMITTAG="[AUTO][ci skip]"

# Exit on error
set -e

generate_cocosfiles_json()
{
    echo "Updates cocos_files.json"
    pushd "$COCOSFILES_CREATOR_ROOT"
    ./create_config.py
    popd
}

if [ "$GEN_COCOS_FILES"x != "YES"x ]; then
    generate_cocosfiles_json
    exit 0
fi

pushd "$COCOS2DX_ROOT"
#Set git user for cocos2d-x repo
git config user.email ${GH_EMAIL}
git config user.name ${GH_USER}
popd


# 1. Updates cocos_files.json
generate_cocosfiles_json

echo
echo cocos_files.json was generated successfully
echo


if [ -z "${COMMITTAG+aaa}" ]; then
# ... if COMMITTAG is not set, use this machine's hostname
    COMMITTAG=`hostname -s`
fi

echo
echo Using "'$COMMITTAG'" in the commit messages
echo

ELAPSEDSECS=`date +%s`
echo Using "$ELAPSEDSECS" in the branch names for pseudo-uniqueness


# 2. Check if there are any files that are different from the index

pushd "$COCOS2DX_ROOT"

# Run status to record the output in the log
git status

echo
echo Comparing with HEAD ...
echo

# Don't exit on non-zero return value
set +e
git diff --stat --exit-code

DIFF_RETVAL=$?
if [ $DIFF_RETVAL -eq 0 ]
then
    echo
    echo "No differences in cocos_files.json"
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

popd

COCOS_BRANCH=update_cocosfiles_"$ELAPSEDSECS"

pushd "${DIR}"

# 3. In Cocos2D-X repo, Checkout a branch named "updategeneratedsubmodule" Update the submodule reference to point to the commit with generated bindings
cd "${COCOS2DX_ROOT}"
git add .
git checkout -b "$COCOS_BRANCH"
git commit -m "$COMMITTAG : updating tools/project-creator/module/cocos_files.json"
#Set remotes
git remote add upstream https://${GH_USER}:${GH_PASSWORD}@github.com/${GH_USER}/cocos2d-x.git 2> /dev/null > /dev/null
# 4. In Cocos2D-X repo, Push the commit to cocos2d-x repository
echo "Pushing to Robot's repo ..."
git push -fq upstream "$COCOS_BRANCH" 2> /dev/null


# 5. 
echo "Sending Pull Request to base repo ..."
curl --user "${GH_USER}:${GH_PASSWORD}" --request POST --data "{ \"title\": \"$COMMITTAG : updating tools/project-creator/module/cocos_files.json\", \"body\": \"\", \"head\": \"${GH_USER}:${COCOS_BRANCH}\", \"base\": \"${TRAVIS_BRANCH}\"}" https://api.github.com/repos/cocos2d/cocos2d-x/pulls 2> /dev/null > /dev/null

popd
