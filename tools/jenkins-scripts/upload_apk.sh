#!/bin/sh

localfile=$1
remotefile=$2

sftp redmine@10.10.11.15 << EOF
put $localfile $remotefile
bye
EOF
echo "upload finished"