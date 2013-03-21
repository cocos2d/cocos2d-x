## Prerequisites:

* Android NDK
* Android SDK **OR** Eclipse ADT Bundle
* Android AVD target installed

## Building project

There are two ways of building Android projects.

1. Eclipse
2. Command Line

### Import Project in Eclipse

#### Features:

1. Complete workflow from Eclipse, including:
	* Build C++.
	* Clean C++.
	* Build and Run whole project.
	* Logcat view.
	* Debug Java code.
	* Javascript editor.
	* Project management.
2. True C++ editing, including:
	* Code completion. 
	* Jump to definition.
	* Refactoring tools etc. 
	* Quick open C++ files.


#### Setup Eclipse Environment (only once)


**NOTE:** This step needs to be done only once to setup the Eclipse environment for cocos2d-x projects. Skip this section if you've done this before.

1. Download Eclipse ADT bundle from [Google ADT homepage](http://developer.android.com/sdk/index.html)

   **OR**

   Install Eclipse with Java. Add ADT and CDT plugins.

2. Only for Windows
    1. Install [Cygwin](http://www.cygwin.com/) with make (select make package from the list during the install).
    2. Add `Cygwin\bin` directory to system PATH variable.
    3. Add this line `none /cygdrive cygdrive binary,noacl,posix=0,user 0 0` to `Cygwin\etc\fstab` file.
   
3. Set up Variables: 
	1. Path Variable `COCOS2DX`: 
		* Eclipse->Preferences->General->Workspace->**Linked Resources**
		* Click **New** button to add a Path Variable `COCOS2DX` pointing to the root cocos2d-x directory.
		![Example](https://lh5.googleusercontent.com/-oPpk9kg3e5w/UUOYlq8n7aI/AAAAAAAAsdQ/zLA4eghBH9U/s400/cocos2d-x-eclipse-vars.png)

	2. C/C++ Environment Variable `NDK_ROOT`: 
		* Eclipse->Preferences->C/C++->Build->**Environment**.
		* Click **Add** button and add a new variable `NDK_ROOT` pointing to the root NDK directory.
		![Example](https://lh3.googleusercontent.com/-AVcY8IAT0_g/UUOYltoRobI/AAAAAAAAsdM/22D2J9u3sig/s400/cocos2d-x-eclipse-ndk.png)
		* Only for Windows: Add new variables **CYGWIN** with value `nodosfilewarning` and **SHELLOPTS** with value `igncr`
		
4. Import libcocos2dx library project:
	1. File->New->Project->Android Project From Existing Code.
	2. Click **Browse** button and open `cocos2d-x/cocos2dx/platform/android/java` directory.
	3. Click **Finish** to add project.
	
#### Adding and running from Eclipse

![Example](https://lh3.googleusercontent.com/-SLBOu6e3QbE/UUOcOXYaGqI/AAAAAAAAsdo/tYBY2SylOSM/s288/cocos2d-x-eclipse-project-from-code.png) ![Import](https://lh5.googleusercontent.com/-XzC9Pn65USc/UUOcOTAwizI/AAAAAAAAsdk/4b6YM-oim9Y/s400/cocos2d-x-eclipse-import-project.png)

1. File->New->Project->Android Project From Existing Code
2. **Browse** to your project directory. eg: `cocos2d-x/cocos2dx/samples/Cpp/TestCpp/proj.android/`
3. Add the project 
4. Click **Run** or **Debug** to compile C++ followed by Java and to run on connected device or emulator.


### Running project from Command Line

    $ cd cocos2d-x/samples/Cpp/TestCpp/proj.android/
    $ export NDK_ROOT=/path/to/ndk
    $ ./build_native.sh
    $ ant debug install

If the last command results in sdk.dir missing error then do: 

    $ android list target
    $ android update project -p . -t (id from step 6)
    $ android update project -p cocos2d-x/cocos2dx/platform/android/java/ -t (id from step 6)
