#Creating A Project

First you need to install the Python environment.

There are two ways to create a new cocos project.
Notice: The best project path is an English path without spaces.
##1.UI
* Windows: double click the "create_project.py" file
* Mac: use `./create_project.py`
* Linux: The Tkinter library was not installed automatically in Linux, therefore, in order to use the GUI to operate, you have to install Tkinter manually (see http://tkinter.unpythonic.net/wiki/How_to_install_Tkinter). There is another way to create projects by command line. See below for details.

##2.console
To use this, open the terminal and type:
```
	$ cd cocos2d-x/tools/project-creator
	$ ./create_project.py --help
	$ ./create_project.py -n mygame -k com.your_company.mygame -l cpp -p /home/mygame
	$ cd /home/mygame
```
