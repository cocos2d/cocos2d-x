ABOUT:
Chipmunk is a simple, lightweight and fast 2D rigid body physics library written in C. It's licensed under the unrestrictive, OSI approved MIT license. My aim is to give 2D developers access the same quality of physics you find in newer 3D games. I hope you enjoy using Chipmunk, and please consider donating to help make it worth our time to continue to support Chipmunk with great new features.

CONTRACTING:
Howling Moon Software (my company) is available for contracting if you want to make the physics in your game really stand out. Given our unique experience with the library, we can help you use Chipmunk to it's fullest potential. Feel free to contact us through our webpage: http://howlingmoonsoftware.com/contracting.php

BUILDING:
Mac OS X: There is an included XCode project file for building the static library and demo application. Alteratively you could use the CMake files.

iPhone: The XCode project can build a static library with all the proper compiler settings. Additionally, if you run the iphonestatic.sh script in the macosx/ directory, it will build you a fat library compiled as release for the device and debug for the simulator. After building that, just copy the static lib and include/chipmunk/ directory to your project.

UNIX: A forum user was kind enough to make a set of CMake files for Chipmunk. This will require you to have CMake installed. To build run 'cmake .' then 'make'. This should build a dynamic library, a static library, and the demo application.

Windows: There is an included MSVC project for building the library and demo application. I do not personally maintain the MSVC project and it apparently hasn't worked for a while. If you are a MSVC whiz, consider lending a hand.

Ruby: I've been using maintaining a Ruby extension for Chipmunk, but at this time is not up to date with all the latest changes. A forum member has been working on an FFI based extention, and that may be a better way to take advantage of Chipmunk from Ruby. Another forum user has offered to maintain the non-FFI version of the extension. Stay tuned.

GETTING STARTED:
First of all, you can find the C API documentation here: http://code.google.com/p/chipmunk-physics/wiki/Documentation

A good starting point is to take a look at the included Demo application. The demos all just set up a Chipmunk simulation space and the demo app draws the graphics directly out of that. This makes it easy to see how the Chipmunk API works without worrying about the graphics code. You are free to use the demo drawing routines in your own projects, though it is certainly not the recommended way of drawing Chipmunk objects as it pokes around at the undocumented parts of Chipmunk.

FORUM:
http://www.slembcke.net/forums

CONTACT:
slembcke@gmail.com (also on Google Talk)

CHANGES SINCE 5.0.0:
* Fixed a NaN issue where raycasts for horizontal or vertical lines would end up in an infinite loop.
* Fixed a number of memory leaks.
* Fixed a number of warnings for various compiler/OS combinations.
* Fixed a number of API issues:
  * Rejecting a collision from a begin() callback permanently rejects the collision until separation.
  * Erroneous collision type parameterns removed from cpSpaceDefaulteCollisionHandler().
* Moved FFI declarations of inlined functions into their own header.
* Rearranged the project structure to separate out the header files into a separate include/ directory.
* Added a static library target for the iPhone.
* Type changes when building on the iPhone to make it friendlier to other APIs.
* Added an AABB query to complement point and segment queries.
* Added CP_NO_GROUP and CP_ALL_LAYERS constants.

CHANGES SINCE 4.x:
* Brand new Joint/Constraint API: New constraints can be added easily and are much more flexible than the old joint system
* Efficient Segment Queries - Like raycasting, but with line segments.
* Brand new collision callback API: Collision begin/separate events, API for removal of objects within callbacks, more programable control over collision handling.