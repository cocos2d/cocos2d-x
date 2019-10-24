<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Cocos2d-x 4.0 Release Notes](#cocos2d-x-40-release-notes)
  - [Highlights](#highlights)
  - [Documentation](#documentation)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Cocos2d-x 4.0 Release Notes #

This version is mainly to support metal on iOS/macOS. In order to support metal, this version does a big refactor of the rendering system. And this version also remove deprecated functions, so there are some API modification.

In order to help develpers easily update to v4, we wrote some documentations. These documentations can be found [here](https://docs.cocos.com/cocos2d-x/v4/manual/en/upgradeGuide/).

## Highlights

- support metal on iOS/macOS
- use CMake for all platforms
- update GLFW to 3.3
- update minizip to 1.2
- remove deprecated functions
- remove h5 engine and JSB
- remove tiff
- remove `SimpleAudioEngine`
- remove `experimetnal` namespace
- fix bug that system font can not work correctly on macOS15
- fix lua crash issue on 64bit devices
- fix bugs for iOS13
  - UIWebView uses WKWebView instead
  - VideoPlayer uses AVPlayerController instead

## Documentation

We wrote some documentations to help developers upgrade to v4:
- [how to run tests and how to create a new project and run](https://docs.cocos2d-x.org/cocos2d-x/v4/en/installation/)
- [v4 updrade guide](https://docs.cocos2d-x.org/cocos2d-x/v4/en/upgradeGuide/)
