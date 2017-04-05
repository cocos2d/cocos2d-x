How to Use bindings-generator
==================

On Windows:
------------

* Make sure that you have installed `android-ndk-r10c` or later.
* Download python2.7.3 (32bit) from (http://www.python.org/ftp/python/2.7.3/python-2.7.3.msi).
* Add the installed path of python (e.g. C:\Python27) to windows environment variable named 'PATH'.
* Download pyyaml from http://pyyaml.org/download/pyyaml/PyYAML-3.11.win32-py2.7.exe and install it.
* Download pyCheetah from https://raw.github.com/dumganhar/my_old_cocos2d-x_backup/download/downloads/Cheetah.zip, unzip it to "C:\Python27\Lib\site-packages"
* Set environment variables `NDK_ROOT` and `PYTHON_BIN`
* Go to "cocos2d-x/tools/tolua" folder, and run "genbindings.py". The generated codes will be under "cocos\scripting\auto-generated\lua-bindings".


On MAC:
----------

* The OSX 10.10 has a built-in python2.7 and if your os don't have python2.7 then use [Homebrew](http://brew.sh/) to install the python and use pip install the python dependencies.
<pre>
	brew install python
</pre>

* Install python dependices by pip.
<pre>
    sudo easy_install pip
    sudo pip install PyYAML
	sudo pip install Cheetah
</pre>
    
* Download NDK 64bit r10c or later from [Android Ndk](https://developer.android.com/ndk/downloads/index.html)
* Run
<pre>
	export NDK_ROOT=/path/to/android-ndk-10c
    ./genbindings.py
</pre>


On Ubuntu Linux 12.04 64bit
------------

* Install python
<pre>
	sudo apt-get install python2.7
</pre>
* Install python dependices by pip.
<pre>
	sudo apt-get install python-pip
	sudo pip install PyYAML
	sudo pip install Cheetah
</pre>
* Download NDK 64bit r10c or later from [Android Ndk](https://developer.android.com/ndk/downloads/index.html)
* Go to "cocos2d-x/tools/tolua", Run
<pre>
	export NDK_ROOT=/path/to/android-ndk-r10c
    ./genbindings.py
</pre>
