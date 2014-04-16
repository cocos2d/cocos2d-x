#!/bin/sh
calfile=$1
remotefile=$2

sftp $FTP_HOME << EOF
put $localfile $remotefile
bye
EOF
echo "upload finished"
