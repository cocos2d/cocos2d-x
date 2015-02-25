
# Generate prebuilt engine

## Purpose

The tools in `gen-prebuilt` are used for generating prebuilt engine.

## Steps

* First, build libs for `Mac, iOS & android`: Run `python gen_prebuilt_libs.py -c` on Mac.
* Second, build libs for `Windows`: Run `python gen_prebuilt_libs.py -n` on Windows.

## Script Details

gen_prebuilt_libs.py

	```
	Usage: gen_prebuilt_libs.py [options]
	
	Options:
		-h, --help           	Show this help message and exit
		-c						Remove the "prebuilt" directory first.
		-n, --no-android		Not build android libs.
		-d, --disable-strip		Disable the strip of the generated libs.
	```
		
The result of the script is : A folder named `prebuilt` which contains prebuilt libs will generated.