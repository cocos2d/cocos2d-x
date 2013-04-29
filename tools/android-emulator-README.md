# Run cocos2d-x successfully on the Android emulator

## Problem and solution

For a few years the only option was to run the Android emulator by emulating the ARM instruction set on a x86 host machine. While this is still possible, it has two problems
 * it is very, very slow
 * GPU support and OpenGL ES 2.0 is not well supported

So cocos2d-x does not run correctly.

The fix is to use virtualization with the x86 version of Android and enable GPU acceleration. With these options enabled, you can successfully use the emulator to develop with cocos2d-x!

## How-to

 1. Download and create an Android emulator using the x86 system image
 2. Enable virtualization (with CPU's that support VT-X) on  Windows/Linux/OSX
 3. Build cocos2d-x libraries for the x86 architecture too
 4. Run the emulator with the correct library path and options
 5. Success!

### Download and create an Android emulator using the x86 system image

 * Run the android emulator manager :

`
<android-sdk>/tools/android
`

Ensure that "Intel x86 Atom System Image" is selected, downloaded and installed for the Android version you are using.

 * Open the menu item

    "Tools"->"Manage AVDs"

 * Create a new Android Virtual Device
 * Make sure to select the "x86" option in the CPU/ABI dropdown
 * Make sure to select the "Use Host GPU" checkbox

### Enable virtualization (with CPU's that support VT-X) on  Windows/Linux/OSX

Please follow intel's instructions here on downloading/enabling virtualization for the Android emulator
http://software.intel.com/en-us/articles/intel-hardware-accelerated-execution-manager/

### Build cocos2d-x libraries for the x86 architecture too

In your app's Application.mk, add x86 to the supported ABI's by adding/editing this line

`
APP_ABI := armeabi x86
`

### Run the emulator with the correct library path and options

Make sure to 
 * Set the library path to the directory containing the Open GL library for the emulator (LD_LIBRARY_PATH=...)
 * Run the x86 version of the emulator (run <android-sdk>/tools/emulator-x86)
 * Enable GPU use (Use the option "-gpu on")
 * Also, you need to specify the name of the Android Virtual Device to use (Use the option "-avd <android virtual device name>")

On OS X the command line looks like this

`
LD_LIBRARY_PATH=~/bin/android-sdk/tools/lib ~/bin/android-sdk/tools/emulator-x86 -verbose -avd android17x86 -gpu on
`
