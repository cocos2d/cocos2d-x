## Prerequisites:

* Android NDK
* Android SDK **OR** Eclipse ADT Bundle
* Android AVD target installed

## Building project

There are two ways of building Android projects.

1. Eclipse
2. Command Line

### Import Project in Eclipse

####Step 1: C/C++ Environment Variable `NDK_ROOT`

* Eclipse->Preferences->C/C++->Build->**Environment**.
* Click **Add** button and add a new variable `NDK_ROOT` pointing to the root NDK directory.
	![Example](https://lh3.googleusercontent.com/-AVcY8IAT0_g/UUOYltoRobI/AAAAAAAAsdM/22D2J9u3sig/s400/cocos2d-x-eclipse-ndk.png)
* Only for Windows: Add new variables **CYGWIN** with value `nodosfilewarning` and **SHELLOPTS** with value `igncr`

####Step 2: Adding and running from Eclipse

![Example](https://lh3.googleusercontent.com/-SLBOu6e3QbE/UUOcOXYaGqI/AAAAAAAAsdo/tYBY2SylOSM/s288/cocos2d-x-eclipse-project-from-code.png) ![Import](https://lh5.googleusercontent.com/-XzC9Pn65USc/UUOcOTAwizI/AAAAAAAAsdk/4b6YM-oim9Y/s400/cocos2d-x-eclipse-import-project.png)

1. File->New->Project->Android Project From Existing Code
2. **Browse** to your project directory and Add the project 
3. Click **Run as Android Application** to run on connected device or emulator.

That's all !!! 

### Running project from Command Line

    $ cd NEW_PROJECTS_DIR/MyGame
    $ cocos run -p android -j 4
