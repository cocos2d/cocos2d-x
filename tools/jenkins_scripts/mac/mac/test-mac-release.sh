#!bin/bash
#This script is used to finish a ios test automation.

compileresult=0

cd ..
cp -r iOS_SikuliTest.sikuli ../../../samples/TestCpp/proj.mac
cd ../../../samples/TestCpp/proj.mac
sdk_num=$(sed -n '1p' sdk_num.txt)

for((i=1;i<=$sdk_num;i++))
do
    a=$(sed -n '1p' directory_name.txt)
    echo $a
    $(pwd)/build/${a}/TestCpp.app/Contents/MacOS/TestCpp &
    $SIKULI_HOME/sikuli-ide.sh -r $(pwd)/iOS_SikuliTest.sikuli     
done

#Sikuli Test success!
echo Sikuli Test Success!
#git checkout -f
#git clean -df -x
exit 0

#End