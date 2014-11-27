#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
export NDK_DEBUG=1
$DIR/build_native_release.sh