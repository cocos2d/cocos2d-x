# cocos2d-x v3.5 for Tizen Release Notes #

**Table of Contents**  *generated with [DocToc](http://doctoc.herokuapp.com/)*

- [Environment requirement](#environment-requirement)
- [How to run cpp-tests on Tizen](#how-to-run-cpp-tests-on-tizen)
	- [Run on Tizen devices](#run-on-tizen-devices)
	- [Run on Tizen emulator](#run-on-tizen-emulator)
	- [Security profiles](#security-profiles)
- [How to start a new game on Tizen](#how-to-start-a-new-game-on-tizen)

Compared to `cocos2d-x v3.5`, this version added Tizen platform support.

If had the Samsung Z1 device, you can get more information from the following two links:

* [Samsung Z developer page](http://developer.samsung.com/samsung-z)
* [how to enable usb debugging option on Samsung Z1](https://developer.tizen.org/ko/forums/general-support/how-enable-usb-debugging-option-on-my-tizen-mobile-samsung-z1)


# Environment requirement

* Ubuntu 12.0.4+/Win7+/Mac OS X 10.10
* [cocos2d-x-3.5-tizen.zip](http://cdn.cocos2d-x.org/cocos2d-x-3.5-tizen.zip)
* [Tizen SDK 2.3](https://developer.tizen.org/downloads/tizen-sdk), `please select custom mode and select gcc4.8 package`

![install-sdk](https://raw.githubusercontent.com/minggo/Pictures/master/tizen/tizen-install-sdk.png)

# How to run cpp-tests on Tizen

* download Install-manager and Tizen SDK image from [here](https://developer.tizen.org/downloads/tizen-sdk)
* install Tizen SDK and `select custom mode with GCC4.8`
* open Tizen IDE

  ![open-tizen-ide](https://raw.githubusercontent.com/minggo/Pictures/master/tizen/open-tizen-ide.png)
  
* set workspace for the first launching

  ![set-workspace](https://raw.githubusercontent.com/minggo/Pictures/master/tizen/tizen-set-workspace.png)
  
* right click `Project Explorer` and select `import`

  ![import-project](https://raw.githubusercontent.com/minggo/Pictures/master/tizen/tizen-import-project.png)
  
* select `cpp-tests` and `libcocos2dx` project

  ![select-project](https://raw.githubusercontent.com/minggo/Pictures/master/tizen/tizen-select-cpp-tests.png)
  
## Run on Tizen devices

* change `ligcocos2dx` to debug mode and build it
  * right click `libcocos2dx` and select `Build Configurations->Set Active->Debug`
  * right click `libcocos2dx` and select `Build Project`
* change `cpp-tests` to debug mode and build it
  * right click `cpp-tests` and select `Build Configurations->Set Active->Debug`
  * right click `cpp-tests` and select `Build Project`
* right click `cpp-tests` and select `Run As->1 Tizen Native Application`, then cpp-tests will run on your Tizen device

If you meet `security profile` issue, you can refer to [Security profiles](#security-profiles) section to fix it.

## Run on Tizen emulator

* create an emulator, `please set RAM size to 1024`

  ![create-emulator](https://raw.githubusercontent.com/minggo/Pictures/master/tizen/tizen-generate-tizen-simulator.png)

* launch the emulator by click the arrow button and power on it

  ![power-on-emulator](https://raw.githubusercontent.com/minggo/Pictures/master/tizen/tizen-power-on-simulator.png)

* change `ligcocos2dx` to emulator mode and build it
  * right click `libcocos2dx` and select `Build Configurations->Set Active->Emulator`
  * right click `libcocos2dx` and select `Build Project`
* change `cpp-tests` to emulator mode and run it(`make sure screen is unlocked`)
  * right click `cpp-tests` and select `Build Configurations->Set Active->Emulator`
  * right click `cpp-tests` and select `Build Project`
  * right click `cpp-tests` and select `Run As->1 Tizen Native Application`
  
  ![run-cpp-tests-on-emulator](https://raw.githubusercontent.com/minggo/Pictures/master/tizen/tizen-run-cpp-tests.png)
  
## Security profiles

You may meet security profiles issue when you firstly lauching an application like this:

![security-profile](https://raw.githubusercontent.com/minggo/Pictures/master/tizen/tizen-security-profile.png)

You can resolve it by doing following steps:

* click `Preferences->Security Profiles` to add one profile and generate it, `profile name` and `key filename` can be any string

![add-profile-name](https://raw.githubusercontent.com/minggo/Pictures/master/tizen/tizen-add-profile-name.png)

![generate-certification](https://raw.githubusercontent.com/minggo/Pictures/master/tizen/tizen-generate-certification.png)

![finish-profile](https://raw.githubusercontent.com/minggo/Pictures/master/tizen/tizen-security-profile-finish.png)

# How to start a new game on Tizen

Please refer to [How to run cpp-tests on Tizen](#how-to-run-cpp-tests-on-tizen) section before reading this section.

Steps to start a new game:

* use cocos console to generate a new game project
* use Tizen IDE to import the new project
* run the game on Tizen devices or emulator

![generate-tizen-project](https://raw.githubusercontent.com/minggo/Pictures/master/tizen/tizen-generate-project.png)

Because of Tizen toolchain issue, currently you can not use cocos console to run a game on Tizen devices or emulators. You should use Tizen IDE to import a new project and run it.
