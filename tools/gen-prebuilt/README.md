
# Generate prebuilt engine

## Purpose

The tools in `gen-prebuilt` are used for generating prebuilt engine.

## Steps

1. Generate prebuilt libs
	* First, build libs for `Mac, iOS & android`: Run `python gen_prebuilt_libs.py` on Mac.
	* Second, build libs for `Windows`: Run `python gen_prebuilt_libs.py -n` on Windows.
2. Organize the prebuilt libs with modules  
	Run command `python module_organize.py` on Windows or Mac.

## Script Details

1. gen_prebuilt_libs.py

	```
	Usage: gen_prebuilt_libs.py [options]
	
	Options:
		-c						Remove the "prebuilt" directory first.
		-n, --no-android		Not build android libs.
		-s, --strip				Enable strip when generating iOS, Mac & Android libs.
		-i, --incredibuild		Use incredibuild to build win32 projects. Only available on windows.
	```
	
	The result of the script is : A folder named `prebuilt` which contains prebuilt libs will generated.

2. module_organize.py

	```
	Usage: module_organize.py [options]
	
	Options:
		-d, --dst-root			Specify a path where to place the engine organized by modules. Default value is the same path with `module_organize.py`.
	```

	The result of the script is : A folder named `cocos2d-x` will generated in the `dst-root`.