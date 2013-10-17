#!/bin/bash
#This script is used to finish a mac automated compiler.

compileresult=0
cd ../../../../samples/Cpp
#List simulator sdks
xcodebuild -showsdks > tmp.txt

#Get sdk's numbers
sdk_num=`grep "Mac OS X 10" tmp.txt|wc -l`
grep "Mac OS X 10" tmp.txt > tmp1.txt
sed 's/Mac OS X 10.[0-9]//' tmp1.txt> tmp.txt

#Use a for circulation to build each version of sdks
cp tmp.txt $(pwd)/TestCpp/proj.mac
cd TestCpp/proj.mac
echo $sdk_num > sdk_num.txt
for((i=1;i<=$sdk_num;i++))
do
    a=$(sed -n '1p' tmp.txt)
    echo $a
    
#Build debug version
    xcodebuild -configuration Debug $a
    compileresult=$[$compileresult+$?]
    if [ $? == 0 ]; then
        var1=build/Debug
        var2=${a:(-4):4}
        var3=${var1}${var2}
        echo 'Debug'${var2} >> directory_name.txt
        mv build/Debug $var3
    fi
    sed -i '' '1d' tmp.txt
done

cd ../..
#Use a for circulation to build each version of sdks
cp tmp.txt $(pwd)/HelloCpp/proj.mac
cd HelloCpp/proj.mac
for((i=1;i<=$sdk_num;i++))
do
    a=$(sed -n '1p' tmp.txt)
    echo $a
    
#Build debug version
    xcodebuild -configuration Debug $a
    compileresult=$[$compileresult+$?]
    sed -i '' '1d' tmp.txt
done

#return the compileresult.
cd ../../..
if [ $compileresult != 0 ]; then
    echo Error.
    echo $compilesult
#    git checkout -f
#    git clean -df -x
    exit 1
else
    echo Success.
    echo $compileresult
#    git checkout -f
#    git clean -df -x
fi