<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Cocos2d-x 3.13.1 Release Notes](#cocos2d-x-3131-release-notes)
- [Misc Information](#misc-information)
- [v3.13.1](#v3131)
  - [Bug fixed](#bug-fixed)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Cocos2d-x 3.13.1 Release Notes #

# Misc Information

* [Full Changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)

# v3.13.1

## Bug fixed

* Label color broken, [github issue](https://github.com/cocos2d/cocos2d-x/issues/16471)
* may crash if coming from background by clicking application icon on Android, [github issue](https://github.com/cocos2d/cocos2d-x/issues/16520)
* object.setString() has not effect if passing a number on JSB, [github issue](https://github.com/cocos2d/cocos2d-x/issues/16459)
* AudioEngine can not play audio if the audio lies outside APK on Android, [github issue](https://github.com/cocos2d/cocos2d-x/issues/16473)
* AudioEngine::stop() will trigger `finish` callback on Android, [github issue](https://github.com/cocos2d/cocos2d-x/issues/16490)