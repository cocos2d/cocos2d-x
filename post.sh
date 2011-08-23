#!/bin/bash
echo  $1 $2
test -e ../Debug/lib$1.so&&  cp ../Debug/lib$1.so ../../lib/linux/Debug/lib$2.so 
test -e ../Release/lib$1.so&& cp ../Release/lib$1.so ../../lib/linux/Release/lib$2.so

test -e ../AndroidDebug/lib$1.so&& cp ../AndroidDebug/lib$1.so ../../lib/android/Debug/lib$2.so
test -e ../AndroidRelease/lib$1.so&& cp ../AndroidRelease/lib$1.so ../../lib/android/Release/lib$2.so

