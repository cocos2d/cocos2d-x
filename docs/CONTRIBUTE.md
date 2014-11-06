# Contributing to cocos2d-x


## For general questions


You can ask general questions by using:

-   Forum (preferred way): http://discuss.cocos2d-x.org/
-   IRC: https://webchat.freenode.net/ (Use the *cocos2d* or *cocos2d-x* channels)
-   Weibo: http://t.sina.com.cn/cocos2dx
-   Twitter: http://www.twitter.com/cocos2dx

## Reporting bugs

To report bugs, please use the [Issue Tracker](https://github.com/cocos2d/cocos2d-x/issues)

Steps to report a bug:
* Open the [url](https://github.com/cocos2d/cocos2d-x/issues/new)
* Add all the needed information to reproduce the bug


## Submitting patches

If you want to contribute code, please follow these steps:

(If you are new to git and/or GitHub, you should read [Pro Git](http://progit.org/book/) , especially the section on [Contributing to a project:Small/Large Public Project](http://progit.org/book/ch5-2.html#public_small_project) )

-   Download the latest cocos2d-x develop branch from github:

```
$ git clone git://github.com/cocos2d/cocos2d-x.git
$ cd cocos2d-x
$ git checkout v3
$ ./download-deps.py
$ git submodule update --init
```

-   Apply your changes in the recently downloaded repository
-   Commit your changes in your own repository
-   Create a new branch with your patch: `$ git checkout -b my_fix_branch`
-   Push your new branch to your public repository
-   Send a “pull request” to user “cocos2d”
-   It must be _complete_. See the definition below
-   It must follow the _Releases_ rules. See the definition below

## Only _complete_ patches will be merged

The patch must be _complete_. And by that, we mean:

-   Follow the [Cocos2d C++ Coding Style][1]
-   Describe what the patch does
-   Include test cases
-   Include unit tests if applicable
-   Must be tested in all supported platforms [*]
-   Must NOT degrade the performance
-   Must NOT break existing tests cases
-   Must NOT break the Continuous Integration build
-   Must NOT break backward compatibility
-   Must compile WITHOUT warnings
-   New APIs MUST be **easy to use**, **familiar** to cocos2d-x users
-   Code MUST be **easy to extend**
-   Must be efficient (fast / low memory needs)
-   It must not duplicate existing code, unless the new code deprecates the old one
-   Patches that refactor key components will only be merged in the next major versions.

[*]: If you don't have access to test your code in all the supported platforms, let us know.

## Releases Rules

### Backward compatibility

- Minor versions MUST be backward compatible with previous minor versions. eg: v3.2 must be backward compatible with v3.1 and v3.0.
- Major versions SHOULD be backward compatible with previous major versions. Breaking backward compatibility in Major versions is acceptable only if it is extremely well justified

### Deprecated APIs

- APIs introduced in a Major version MUST NOT be deprecated in the same Major version. eg: An API introduce in v3.1 MUST NOT be deprecated the following v3.x releases.
- Deprecated APIs can be removed only after being deprecated for more than one complete Major cycle. eg: An API deprecated in v2.2 can only be removed in v4.0, but not before.
- Deprecated APIs MUST give a compile-time warning. And MUST tell the user which is the new API that superceeds it.

### Performance tests

- Performance tests MUST be run before releasing a Release Candidate
- If performance is worse than previous version, then the Release Candidate MUST NOT be released (See Naming Conventions below)
- Results of the performance tests must be documented in the [spreadsheet](https://docs.google.com/spreadsheet/ccc?key=0AvvkdgVbWvpZdHFudzdDT3NuYTRNTHlZZzRGZWYzMmc#gid=8)


### Samples and tests

**BEFORE** releasing a new Minor or Major stable release, the following tasks MUST be done:

- All the samples and tests must be updated to use the new version. This includes:
    - The samples in [cocos2d-x-samples](https://github.com/cocos2d/cocos2d-x-samples) repository
    - The demo games [EarthWarrior3D](https://github.com/chukong/EarthWarrior3D) and [FantasyWarrior3D](https://github.com/chukong/FantasyWarrior3D)
    - All the tests bundled in cocos2d-x
    - All the templates bundled in cocos2d-x

### Documentation

**BEFORE** releasing a new Minor or Major stable release, the following tasks MUST be done:

- All documentation MUST be updated to the new version. This includes:
    - API Reference
    - Programmers Guide


### Naming conventions

#### Alpha

The product is unstable. It could have memory leaks, or crashes, or the API is unstable. The product contains little QA.
Although the product is not ready for production, the product should be testable.
Alpha versions might have Core functionality that has just been refactored, meaning that Core functionality might be unstable, but should work Ok.

As an example, for cocos2d-x, an _Alpha_ version means:

* Basic functionality works Ok (not great, but OK), like Sprites, Scenes, actions, etc.
_* But it might have memory leaks, or crashes, or the recently added features might be unfinished. The documentation might not be updated.
* As an example, the Renderer refactoring must be done in "alpha" versions (but not Beta versions).

Alpha versions are NOT feature freeze. New features might be added in future alpha and beta versions.


#### Beta

The product is more stable than _Alpha_. The product might crash, but not frequently. No major changes were made in core components.
Smaller features could be refactored in _Beta_ versions, but the core functionality is stable.
The product has more QA.
The only difference between _Alpha_ and _Beta_, is that _Beta_ is more stable than _Alpha_. And that in _Beta_ versions no new major features will be added.

As an example, for cocos2d-x it means:

* All the Core features (Sprites, Menu, Labels, Director, Transitions) are stable. Bug fixes could have been added into the Core functionality, but no major refactoring were done in the Core.
* But perhaps new features like the new Particle Engine could be unfinished, or the Cocos Studio reader might crash.
* Some cocos2d-x users might want to use a beta version for real games.

Beta versions are NOT feature freeze. __Small__ new features might be added in future _Beta_ versions. New __BIG__ features that might affect the Core functionality must only be added in _Alpha_ versions, and not in _Beta_ versions.


#### Release Candidate
Release candidate means that, unless major bugs are found, the product is ready for release.
The difference between _Release Candidate__ and _Final_ is that RC has less testing than the final version.

Many cocos2d-x users might want to try and use the RC releases for production.

RC versions ARE feature freeze. No new features, no matter how small they are, MUST be added in RC versions, because as the name implies, it is a _Release Candiate_.


#### Final

It is the new stable version.

### Number conventions

major.minor [revision | status]

#### Major
The major number is increased when there are significant jumps in functionality such as changing the framework which could cause incompatibility with interfacing systems

#### Minor:
The minor number is incremented when only minor features or significant fixes have been added.

#### Revision:
The revision number is incremented when minor bugs are fixed.

#### Status:
The status could be: alphaN, betaN or rcN.

'N' is a number, and the first MUST always be 0.

#### Examples

v2.0-alpha0:
  - New major version of cocos2d-x.
  - Unstable

v2.1.3:
   - Stable version of cocos2d-x. It is the same as v2.1 plus some bug fixes.

v2.2-beta0:
   - Similar to v2.1.3, but some new features were added, but are not stable yet.

v2.2:
   - Similar to v2.1.3, but some small features were added. The new features are stable.



# Promoting cocos2d

Help us promote cocos2d-x by using the cocos2d logo in your game, or by mentioning cocos2d in the credits.

[Logo Resources of Cocos2d-x][2]


[1]: https://github.com/cocos2d/cocos2d-x/blob/v3/docs/CODING_STYLE.md
[2]: http://www.cocos2d-x.org/wiki/Logo_Resources_of_Cocos2d-x
