sh ~/Documents/quick-cocos2d-x/bin/compile_scripts.sh -i ~/Documents/quick-cocos2d-x/samples/2048android/scripts -o update.zip
python mkflist.py update.zip $1
python -m SimpleHTTPServer 8080
