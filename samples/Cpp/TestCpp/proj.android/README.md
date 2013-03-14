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
	a. Build C++.
	b. Clean C++.
	c. Build and Run whole project.
	d. Logcat view.
	e. Debug Java code.
	f. Javascript editor.
	g. Project management.
2. True C++ editing, including:
	a. Code completion. 
	b. Jump to definition.
	c. Refactoring tools etc. 
	d. Quick open C++ files.


#### Setup Eclipse Environment


**NOTE:** This step needs to be done only once to setup the Eclipse environment for cocos2d-x projects. Skip this section if you've done this before.

1. Download Eclipse ADT bundle from [Google](http://developer.android.com/sdk/index.html)

   **OR**

   Install Eclipse with Java. Add ADT and CDT plugins.
   
2. Set up Variables:
	1. Path Variable **COCOS2DX**:
		A. Eclipse->Preferences->General->Workspace->**Linked Resources**
		B. Click **New** button to add a Path Variable **COCOS2DX** pointing to the root cocos2d-x directory (Directory containing cocos2dx/ external/ tools/ scripting/ etc.).
		
	2. C/C++ Environment Variable **NDK_ROOT**: 
		A. Eclipse->Preferences->General->C/C++->Build->**Environment**.
		B. Click **Add** button and add a new variable **NDK_ROOT** pointing to the root NDK directory.
		
3. Import libcocos2dx library project:
	1. File->new->Project..->Android Project From Existing Code.
	2. Click **Browse** button and open cocos2d-x/cocos2dx/platform/android/java directory.
	3. Click **Finish** to add project.
	
	

#### Adding and running from Eclipse


1. File->new->Project..->Android Project From Existing Code
2. **Browse** to cocos2d-x/cocos2dx/samples/Cpp/TestCpp/proj.android/ directory. 
3. Add the project 
4. Click **Run** or **Debug** to compile C++ followed by Java and to run on connected device or emulator.


### Running project from Command Line

1. `cd cocos2d-x/samples/Cpp/TestCpp/proj.android/`
2. `export NDK_ROOT=/path/to/ndk`
3. `./build_native.sh`
4. `ant debug install`
5. If step 4 results in sdk.dir missing error then follow step 6-8.
6. `android list target`
7. `android update project -p . -t (id from step 6)`
8. `android update project -p cocos2d-x/cocos2dx/platform/android/java/ -t (id from step 6)`




