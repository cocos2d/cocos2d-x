#!/bin/bash

# exit this script if any commmand fails
set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PROJECT_ROOT="$DIR"/../..

shopt -s dotglob

echo_all_files() {
    for file in $1/*
    do
        if [ -d "$file" ]; then
            echo_all_files "$file"
        else
            relative_path="${file##*${PROJECT_ROOT}/}"
            prefix=${relative_path:0:5}
            if [ "$prefix"x != ".git/"x ]; then
                echo "\"$relative_path\","
            fi
        fi
    done
}

echo "["
echo_all_files ${PROJECT_ROOT}
echo "]"

