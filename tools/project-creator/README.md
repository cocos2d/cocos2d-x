#create_project

First you need install python environment.

There have double ways create new cocos project.
Notice:The best of generate path is english path.
##1.UI
* Windows: double click "create_project.py" file
* Mac: ./create_project.py
* Linux: The tkinter was not installed in the linux's default python,therefore, in order to use the gui operate, you have to install the tkinter libaray manually. There is another way to create project by command line.  see below for details
##2.console
	$ cd cocos2d-x/tools/project-creator
	$ ./project-creator.py --help
	$ ./project-creator.py -n mygame -k com.your_company.mygame -l cpp -p /home/mygame
	$ cd /home/mygame