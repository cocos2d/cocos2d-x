# Performance Test Data Convertor

## Overview

Performance Test Data Convertor is used for converting the json files to excel files. The json files are generated from project `tests/performance-tests`.

## Requirement

* Python 2.7 is required. (Python 2.7.5 is well tested)
* [xlwt](https://pypi.python.org/pypi/xlwt/) for python to write excel files.

## Generate test data

1. Change the device name in the tests source code.  
Now you should modify the device name in `tests/performance-tests/Classes/Profile.cpp` before running the tests. Sample code:

	```
	// For different device & os, change these values
	// TODO : get device info automatically
	#define DEVICE_NAME         "TheDeviceName"
	#define OS_VERSION          "SystemVersion"
	```

2. Run the performance-tests project on devices.  
Once the project started, you will see a scene like this:
![test-scene][test-scene.jpg]

3. Click the menu `Start AutoTest`. Then the performance tests will running automatically.  Once the scene stopped at the scene again. It's mean the autotesting is end.

## Get the generated json files

After the test data generated, you can get the json file from the device.  
The json file will be named with format : `PerformanceLog-[DEVICE_NAME]-[TIMESTAMP].json`.  

For different OS, you can get the json files by different steps:

### From iOS devices

The json files will generated in the `Document` folder of the app. So you can get the json files by iTunes by steps:
![itunes][itunes.jpg]

### From Android devices

The json files will be generated in the path `/mnt/sdcard/PerfTest`. So you can get the json files by commands like this:

* Windows System

	Run the command in cmd:  
	```
	%ANDROID_SDK_ROOT%\platform-tools\adb pull /mnt/sdcard/PerfTest C:\Users\USER_NAME\MY_LOG_FOLDER
	```

* Mac System

	Run the command in terminal:  
	```
	$ANDROID_SDK_ROOT/platform-tools/adb pull /mnt/sdcard/PerfTest ~/MY_LOG_FOLDER
	```

### From Mac devices

The json files will be generated in the path `~/Document`.

### From Win32 devices

The json files will be generated in the AppData path. For different system versions, it will be different path.  
The path will be `C:\Users\USER_NAME\AppData\Local\performance-tests` on Win8.1.

## Convert json files to excel files

When the json files are ready, you can convert the json files to excel files by `tools/performance-analyze/convertor.py`.  
The usage of the tool:

```
usage: convertor.py [-h] -s SRC_PATH [-o OUTPUT_PATH]

Performance test data convertor.

optional arguments:
  -h, --help      show this help message and exit
  -s SRC_PATH     Specify the json file path or the folder path of json files.
  -o OUTPUT_PATH  Specify the output path of excel files.
```

Tips:

* The value of `-s` can be a json file or a folder which contains many json files. If it's a folder, then the json files in the folder will be converted to excel files one by one.


* You can specify the output path by `-o`. If it's not specified, the excel files will be placed in the same folder of json files.


* Each json file will generate an excel file. The excel file name will be same with the json file. For example:  
`python convertor.py -s PerformanceLog-iphone4s-2015-09-11-1745.json` will generate a `PerformanceLog-iphone4s-2015-09-11-1745.xls` file.


* The format of the excel file will be looks like this:

	![excel format][excel.jpg]

	1. Each sheet shows the result of a test case.
	2. The cells with GREEN background color are the conditions of the test case.
	3. The cells with YELLOW background color are the result data of the test case.

[test-scene.jpg]: http://i60.tinypic.com/ou86bs.jpg
[itunes.jpg]: http://i60.tinypic.com/33z4r53.jpg
[excel.jpg]: http://i57.tinypic.com/wvx500.jpg