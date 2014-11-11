# Cocos2d-x Release Engineering


## Tagging

New releases must be tagged in github. The tag name must follow these rules:

    cocos2d-x-Major.Minor[.Status]

or

    cocos2d-x-Major.Minor.Revision[.Status]

Example of valid names:

* cocos2d-x-3.0rc0
* cocos2d-x-3.0
* cocos2d-x-2.1.1
* cocos2d-x-2.1.1rc0

See "Naming Conventions" below

## Branching

Each Major version will have 2 branches, `master` and `develop`.
For cocos2d-x v3, the branches names will be `v3-master` and `v3-develop`, for v4 the branches names will be `v4-master` and `v4-develop`, and so on.

* `master` is the stable branch.
* `develop` is the unstable branch. All new features, bug fixes, etc, are applied first to `develop`.

Once a new version is released (either Major, Minor or Revision), then `develop` branch must be merged into `master` branch. To be more specific, `master` only contains _stable_ releases. _Alpha_, _Beta_, and _RC_ versions MUST NOT be merged into `master`.


## Announcing

Only stable releases must be announced on:

* [Blog](http://www.cocos2d-x.org/news)

All kind of releases (alpha,beta,rc, final) must be announced on:
* [Twitter](https://twitter.com/cocos2dx)
* [Forum](http://discuss.cocos2d-x.org/)


## Download package

A download package must be available for each released version.
The package shall include the source code of cocos2d-x, and the needed scripts to download and install the 3rd party binaries.


## Release Notes and Changelog

**BEFORE** releasing a new version (either stable or unstable), the following documents must be updated:

* [CHANGELOG](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)
* [Release Notes](https://github.com/cocos2d/cocos2d-x/blob/v3/docs/RELEASE_NOTES.md)

## Documentation

**BEFORE** releasing a new Minor or Major stable release, the following tasks MUST be done:

- All documentation MUST be updated to the new version. This includes:
    - API Reference
    - Programmers Guide

## Backward compatibility

- Minor versions MUST be backward compatible with previous minor versions. eg: v3.2 must be backward compatible with v3.1 and v3.0.
- Major versions SHOULD be backward compatible with previous major versions. Breaking backward compatibility in Major versions is acceptable only if it is extremely well justified

## Deprecated APIs

- Only Major versions (eg: 4.0, 5.0) can introduce deprecated APIs. Deprecated APIs cannot be introduced in Point releases (eg: 3.5, 4.2).
- Only Major versions can remove deprecated APIs. They cannot be removed in Point versions.
- A deprecated API must live at least for the whole cycle of a Major version. Eg: if an API was deprecated in 4.0, it can be removed in 5.0, but not before. It can be removed in 6.0 or future Major releases, but it cannot be removed in Point releases, like 5.1.


## Performance tests

- Performance tests MUST be run before releasing a Release Candidate
- If performance is worse than previous stable version, then the Release Candidate MUST NOT be released (See Naming Conventions below)
- Results of the performance tests must be documented in this [spreadsheet](https://docs.google.com/spreadsheet/ccc?key=0AvvkdgVbWvpZdHFudzdDT3NuYTRNTHlZZzRGZWYzMmc#gid=8)


## Samples and tests

**BEFORE** releasing a new Minor or Major stable release, the following tasks MUST be done:

- All the samples and tests must be updated to use the new version. This includes:
    - The samples in [cocos2d-x-samples](https://github.com/cocos2d/cocos2d-x-samples) repository
    - The demo games [EarthWarrior3D](https://github.com/chukong/EarthWarrior3D) and [FantasyWarrior3D](https://github.com/chukong/FantasyWarrior3D)
    - All the tests bundled in cocos2d-x
    - All the templates bundled in cocos2d-x

## Naming conventions

### Alpha

The product is unstable. It could have memory leaks, or crashes, or the API is unstable. The product contains little QA.
Although the product is not ready for production, the product should be testable.
Alpha versions might have Core functionality that has just been refactored, meaning that Core functionality might be unstable, but should work Ok.

As an example, for cocos2d-x, an _Alpha_ version means:

* Basic functionality works Ok (not great, but OK), like Sprites, Scenes, actions, etc.
_* But it might have memory leaks, or crashes, or the recently added features might be unfinished. The documentation might not be updated.
* As an example, the Renderer refactoring must be done in "alpha" versions (but not Beta versions).

Alpha versions are NOT feature freeze. New features might be added in future alpha and beta versions.

### Beta

The product is more stable than _Alpha_. The product might crash, but not frequently. No major changes were made in core components.
Smaller features could be refactored in _Beta_ versions, but the core functionality is stable.
The product has more QA.
The only difference between _Alpha_ and _Beta_, is that _Beta_ is more stable than _Alpha_. And that in _Beta_ versions no new major features will be added.

As an example, for cocos2d-x it means:

* All the Core features (Sprites, Menu, Labels, Director, Transitions) are stable. Bug fixes could have been added into the Core functionality, but no major refactoring were done in the Core.
* But perhaps new features like the new Particle Engine could be unfinished, or the Cocos Studio reader might crash.
* Some cocos2d-x users might want to use a beta version for real games.

Beta versions are NOT feature freeze. __Small__ new features might be added in future _Beta_ versions. New __BIG__ features that might affect the Core functionality must only be added in _Alpha_ versions, and not in _Beta_ versions.


### Release Candidate
Release candidate means that, unless major bugs are found, the product is ready for release.
The difference between _Release Candidate__ and _Final_ is that RC has less testing than the final version.

Many cocos2d-x users might want to try and use the RC releases for production.

RC versions ARE feature freeze. No new features, no matter how small they are, MUST be added in RC versions, because as the name implies, it is a _Release Candiate_.


### Final

It is the new stable version.

## Number conventions

major.minor [revision | status]

### Major
The major number is increased when there are significant jumps in functionality such as changing the framework which could cause incompatibility with interfacing systems

### Minor
The minor number is incremented when only minor features or significant fixes have been added.

### Revision
The revision number is incremented when minor bugs are fixed.

### Status
The status could be: alphaN, betaN or rcN.

'N' is a number, and the first MUST always be 0.

### Examples

v2.0-alpha0:
  - New major version of cocos2d-x.
  - Unstable

v2.1.3:
   - Stable version of cocos2d-x. It is the same as v2.1 plus some bug fixes.

v2.2-beta0:
   - Similar to v2.1.3, but some new features were added, but are not stable yet.

v2.2:
   - Similar to v2.1.3, but some small features were added. The new features are stable.
