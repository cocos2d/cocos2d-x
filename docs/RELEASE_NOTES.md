# cocos2d-x v3.5.1 Release Notes #

Compared to `cocos2d-x v3.5`, this version added Tizen platform support.

## Environment requirement

* Ubuntu 12.0.4+/Win7+/Mac OS X 10.10
* [cocos2d-x-3.5.1.zip](http://cdn.cocos2d-x.org/cocos2d-x-3.5.zip)
* [Tizen SDK 2.3](https://developer.tizen.org/downloads/tizen-sdk), `please select custom mode and select gcc4.8 package`

# How to cpp-tests on Tizen

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

* right click `libcocos2dx` and select `Build Project`
* right click `cpp-tests` and select `Build Project`
* right click `cpp-tests` and select `Run As->1 Tizen Native Application`, then cpp-tests will run on your Tizen device

You may meet `Security Profiles` issue `TBD`

## Run on Tizen emulator

* create a eimulator, `please set RAM size to 1024`

  ![create-emulator](https://raw.githubusercontent.com/minggo/Pictures/master/tizen/tizen-generate-tizen-simulator.png)

* launch the eimulator by click the arrow button and power on it

  ![power-on-emulator](https://raw.githubusercontent.com/minggo/Pictures/master/tizen/tizen-power-on-simulator.png)

* change `ligcocos2dx` to eimulator mode and build it
  * right click `libcocos2dx` and select `Build Configurations->Set Active->Emulator`
  * right click `libcocos2dx` and select `Build Project`
* change `cpp-tests` to emulator mode and run it(`make sure screen is unlocked`)
  * right click `cpp-tests` and select `Build Configurations->Set Active->Emulator`
  * right click `cpp-tests` and select `Build Project`
  * right click `cpp-tests` and select `Run As->1 Tizen Native Application`
  
  ![run-cpp-tests-on-emulator](https://raw.githubusercontent.com/minggo/Pictures/master/tizen/tizen-run-cpp-tests.png)