#/bin/bash
USAGE="Usage: $0 dir"
sh_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
old_pwd=$PWD
if [ $# -lt 1 ] 
then
	echo $USAGE
	exit 1
fi
if [ ! -d $1 ]
then
	echo "Invalid directory: $1" 
	exit 1
fi
script_dir=$1
ok_count=0
error_count=0
# check shell directory first
cmd="$sh_dir/jsbcc"
if [ ! -f $cmd ]
then
# not found in shell directory, check global
    type "jsbcc"
    if [ 0 -eq $? ]
    then
        cmd="jsbcc"
    else
        echo "jsbcc execuable NOT found"
        exit 1
    fi
fi
cd $script_dir
for file in *.js
do
	[ -f "$file" ] || continue
	$cmd $file
	ret=$?
	if [ "$ret" == 0 ] 
	then
		ok_count=`expr $ok_count + 1`
	else
		error_count=`expr $error_count + 1`
	fi
done
cd $old_pwd
echo "$ok_count file(s) compiled, $error_count file(s) failed"
