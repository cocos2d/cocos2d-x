<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Cocos2d-x 3.14.1 Release Notes](#cocos2d-x-3141-release-notes)
- [Misc Information](#misc-information)
- [v3.14.1](#v3141)
  - [Bug fixed](#bug-fixed)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Cocos2d-x 3.14.1 Release Notes #

# Misc Information

* [Full Changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)

# v3.14.1

## Bug fixed

* May crash if using `Scene::createWithPhysics()` to create a scene and physics3d camera is not set
* May have link error because of glfw conflict on Linux
* Sprite: created from sprite frame with polygon information can not work correctly
* Lua: link error with VS2015
* Lua: compiling error if using `cocos compile/run -p android --android-studio` on Android   

Can refer to [v3.14.1 milestone](https://github.com/cocos2d/cocos2d-x/milestone/36?closed=1) for detail informations of all PRs/issues.