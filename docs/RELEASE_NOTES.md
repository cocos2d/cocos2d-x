<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Cocos2d-x 3.13.1 Release Notes](#cocos2d-x-3131-release-notes)
- [Misc Information](#misc-information)
- [v3.13.1](#v3131)
  - [Bug fixed](#bug-fixed)
  - [Cocos command modification](#cocos-command-modification)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Cocos2d-x 3.13.1 Release Notes #

# Misc Information

* [Full Changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)

# v3.13.1

## Bug fixed

* Label color broken
* application will crash in debug mode if don't specify a design resolution
* may crash if coming from background by clicking application icon on Android
* AudioEngine can not play audio if the audio lies outside APK on Android
* AudioEngine::stop() will trigger `finish` callback on Android
* application will crash if using SimpleAudioEngine or new AudioEngine to play audio on Android 2.3.x
* object.setString() has not effect if passing a number on JSB

## Cocos command modification

In previous, cocos command will find an Android API level >= specified Android API level to build source codes on Android. For example, if the content of `APP_ROOT/proj.android/project.properties` is

```
target=android-13 // the default android api level
android.library.reference.1=../../../cocos/platform/android/java
```
then cocos command will find `android-13` in `ANDROID_SDK_ROOT/platforms`, if not found then it will find `android-14`, if `android-14` is not found, then it will find `android-15` and so on until it found one.

This algorithm has a problem that if you only download Android 21, then application will be built with Android 21 though the default API level is 13. If the application runs on a device with lower Android OS(such as Android 4.0), then the application may crash. Building with high API level Android SDK can not make sure run on devices with low Android OS. It is reasonable,  an applicatoin build with iOS 9 can not make sure run on iOS 8.

Since v3.13.1, cocos command will stop if it can not find specific API level(default is android-13). If you want to build with high level Android SDK, you should explicitely specify it like this:

```
cocos compile -p android --ap android-19
```

Keep in mind that, after running this command, content of `APP_ROOT/proj.android/project.properties` will be changed, `android-19` will be the default API level.

There is a map between Android API level and Android OS version, can refer to [this documentation](https://developer.android.com/guide/topics/manifest/uses-sdk-element.html) for detail information.

Can refer to [here](https://github.com/cocos2d/cocos2d-x/milestone/33) for detail information about these issues.