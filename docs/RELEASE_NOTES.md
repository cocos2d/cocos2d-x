<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Cocos2d-x 3.17.1 Release Notes](#cocos2d-x-3171-release-notes)
  - [Highlights](#highlights)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Cocos2d-x 3.17.1 Release Notes #

The 3.17.1 release focuses on bug fixing.   

## Highlights

- Fix LUA performance drop bug introduced in 3.17
- Renderer limit glClear invoke times, reduce power consuming
- optimize CMake script，fix some linking issues
- Android use CMake as default PROP_BUILD_TYPE value
- Android upgrade gradle to 4.6, SDK 28, android gradle plugin 3.1.0 
- upgrade luajit to 2.1.0-beta3, developer reports a random crash in 3.17 LUA release mode
- upgrade libwebsockets to 2.4.2
- FileUtils improve thread safety
- limit Labels text length to fix render error
- add Downloader binding to Lua

This release contains more than 45 bugs fixed and 34 misc improvements, please refer to [ChangeLog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)
