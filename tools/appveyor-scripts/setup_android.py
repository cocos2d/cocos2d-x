#!/usr/bin/env python
'''
aaa
'''
import os
import urllib
import zipfile
import platform
import sys
import subprocess
import tempfile
import argparse
from retry import retry

DIR_PATH = os.path.dirname(os.path.realpath(__file__))

COCOS2D_X = os.path.abspath(os.path.join(DIR_PATH, "../.."))
# ROOT_DIR/cocos2d-x
ROOT_DIR = os.path.abspath(os.path.join(COCOS2D_X, ".."))

ANDROID_NDK = os.path.join(ROOT_DIR, "android-ndk-r16b")
ANDROID_SDK = os.path.join(ROOT_DIR, "android-sdk")
SDK_MANAGER = os.path.join(ROOT_DIR, "sdk_tools/tools/bin/sdkmanager")
SYSTEM = platform.system().lower()
if SYSTEM == "windows":
    SDK_MANAGER = SDK_MANAGER + ".bat"


def run(command):
    print("=" * 80)
    print(command)
    subprocess.check_call(command.split())


def run_with_yes(command):
    print("=" * 80)
    print("yes|" + command)
    f = tempfile.TemporaryFile("w")
    repeat_yes = 50
    f.write("y\n" * repeat_yes)
    f.seek(0)
    subprocess.check_call(command.split(), stdin=f)


def unzip(zip_file, directory):
    print("=" * 80)
    print("Unzip: " + zip_file + " to " + directory)
    if SYSTEM == "windows":
        zipfile.ZipFile(zip_file).extractall(directory)
    else:
        # module zipfile ignore priviliges i.e. +x
        cmd = "unzip -d " + directory + " " + zip_file
        subprocess.check_output(cmd.split())

def download(url, zip_file):
    print("=" * 80)
    print("Download: " + url + ", file: " + zip_file)
    try:
        os.remove(zip_file)
    except OSError:
        pass
    urllib.urlretrieve(url, zip_file)


@retry(Exception, tries=5, delay=1, backoff=1)
def install_android_ndk():
    file_name = "android-ndk-r16b-" + SYSTEM + "-x86_64.zip"
    url = "https://dl.google.com/android/repository/" + file_name
    zip_file = os.path.abspath(os.path.join(ROOT_DIR, file_name))

    download(url, zip_file)
    unzip(zip_file, ROOT_DIR)

@retry(Exception, tries=5, delay=1, backoff=1)
def install_android_sdk_tools():
    file_name = "sdk-tools-{system}-3859397.zip".format(
        system=platform.system().lower())
    url = "https://dl.google.com/android/repository/" + file_name
    zip_file = os.path.abspath(os.path.join(ROOT_DIR, file_name))

    download(url, zip_file)
    unzip(zip_file, os.path.join(ROOT_DIR, "sdk_tools"))


@retry(Exception, tries=5, delay=1, backoff=1)
def install_android_sdk():
    switches = " --verbose --sdk_root=" + ANDROID_SDK + " "
    cmd1 = SDK_MANAGER + switches
    packages = [
        "platforms;android-27",
        "build-tools;28.0.3",
        "platform-tools",
        "tools"
    ]

    cmd = cmd1 + " ".join(packages)
    run_with_yes(cmd)


def export_environment(ndk_only):
    with open(os.path.join(ROOT_DIR, "environment.sh"), "a") as myfile:
        if not ndk_only:
            myfile.write("export ANDROID_HOME=" + ANDROID_SDK + "\n")
            myfile.write("export ANDROID_SDK_ROOT=" + ANDROID_SDK + "\n")
        myfile.write("export ANDROID_NDK_HOME=" + ANDROID_NDK + "\n")
        myfile.write("export NDK_ROOT=" + ANDROID_NDK + "\n")

    with open(os.path.join(ROOT_DIR, "environment.ps1"), "a") as myfile:
        if not ndk_only:
            myfile.write("$env:ANDROID_HOME=\"" + ANDROID_SDK + "\"\n")
            myfile.write("$env:ANDROID_SDK_ROOT=\"" + ANDROID_SDK + "\"\n")
        myfile.write("$env:ANDROID_NDK_HOME=\"" + ANDROID_NDK + "\"\n")
        myfile.write("$env:NDK_ROOT=\"" + ANDROID_NDK + "\"\n")


def main(ndk_only):
    if not ndk_only:
        install_android_sdk_tools()
        install_android_sdk()
    install_android_ndk()
    export_environment(ndk_only)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Install android sdk/ndk')
    parser.add_argument("--ndk_only", help="Install ndk only", action="store_true")
    args = parser.parse_args()
    main(args.ndk_only)
