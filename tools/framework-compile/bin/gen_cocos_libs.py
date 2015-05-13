#!/usr/bin/python
#-*- coding: UTF-8 -*-

import os
import time
import shutil
from argparse import ArgumentParser

class CocosLibsCompiler(object):

	def __init__(self, args):
		print "Compiler init function"

		# argsments check and set
		self.clean = args.clean
		self.build_win = args.win
		self.build_mac = args.mac
		self.build_android = args.android
		self.disable_strip = args.disable_strip
		self.repo_x = args.repo_x
		if args.all:
			self.build_win = True
			self.build_mac = True
			self.build_android = True

		self.cur_dir = os.path.realpath(os.path.dirname(__file__))
		self.repo_x = os.path.realpath(self.repo_x)
		self.lib_dir = os.path.realpath(os.path.join(self.cur_dir, os.path.pardir, "libs"))

	def compile(self):
		print "compile function"
		self.clean_libs()
		self.compile_win()
		self.compile_mac_ios()
		self.compile_android()

	def compile_win(self):
		print "compile win"

	def compile_mac_ios(self):
		print "to compile mac"

		for key in self.xcode_proj_info.keys():
            output_dir = self.xcode_proj_info[key][Generator.KEY_OUTPUT_DIR]
            proj_path = os.path.join(self.root_dir, key)
            if self.gen_libs:
                output_dir = os.path.join(self.root_dir, "lib", "prebuilt")
                proj_path = os.path.abspath(os.path.join(self.x_repo_path, os.path.pardir, key))
            ios_out_dir = os.path.join(self.root_dir, output_dir, "ios")
            mac_out_dir = os.path.join(self.root_dir, output_dir, "mac")

            ios_sim_libs_dir = os.path.join(ios_out_dir, "simulator")
            ios_dev_libs_dir = os.path.join(ios_out_dir, "device")
            for target in self.xcode_proj_info[key][Generator.KEY_TARGETS]:
                build_cmd = Generator.XCODE_CMD_FMT % (proj_path, "%s iOS" % target, "-sdk iphonesimulator ARCHS=\"i386 x86_64\" VALID_ARCHS=\"i386 x86_64\"", ios_sim_libs_dir)
                run_shell(build_cmd, self.tool_dir)

                build_cmd = Generator.XCODE_CMD_FMT % (proj_path, "%s iOS" % target, "-sdk iphoneos", ios_dev_libs_dir)
                run_shell(build_cmd, self.tool_dir)

                build_cmd = Generator.XCODE_CMD_FMT % (proj_path, "%s Mac" % target, "", mac_out_dir)
                run_shell(build_cmd, self.tool_dir)

            # generate fat libs for iOS
            for lib in os.listdir(ios_sim_libs_dir):
                sim_lib = os.path.join(ios_sim_libs_dir, lib)
                dev_lib = os.path.join(ios_dev_libs_dir, lib)
                output_lib = os.path.join(ios_out_dir, lib)
                lipo_cmd = "lipo -create -output \"%s\" \"%s\" \"%s\"" % (output_lib, sim_lib, dev_lib)

                run_shell(lipo_cmd)

            # remove the simulator & device libs in iOS
            shutil.rmtree(ios_sim_libs_dir)
            shutil.rmtree(ios_dev_libs_dir)

            if not self.disable_strip:
                # strip the libs
                ios_strip_cmd = "xcrun -sdk iphoneos strip -S %s/*.a" % ios_out_dir
                run_shell(ios_strip_cmd)
                mac_strip_cmd = "xcrun strip -S %s/*.a" % mac_out_dir
                run_shell(mac_strip_cmd)

	def compile_android(self):
		print "compile android"

	def clean_libs(self):
		print "to clean libs"
		self.rmdir(self.lib_dir)

	def rmdir(self, folder):
		if os.path.exists(folder):
			shutil.rmtree(folder)




if __name__ == "__main__":
    parser = ArgumentParser(description="Generate prebuilt engine for Cocos Engine.")
    parser.add_argument('-c', dest='clean', action="store_true", help='clean libs folder')
    parser.add_argument('-all', dest='all', action="store_true", help='compile all platform')
    parser.add_argument('--win', dest='win', action="store_true", help='compile windows platform')
    parser.add_argument('--mac', dest='mac', action="store_true", help='compile mac platform')
    parser.add_argument('--android', dest='android', action="store_true",help='complile android platform')
    parser.add_argument('--dis-strip', "--disable-strip", dest='disable_strip', action="store_true", help='Disable the strip of the generated libs.')
    parser.add_argument('--repo-x',  dest='repo_x', help='Set the repo path of cocos2d-x.')

    (args, unknown) = parser.parse_known_args()

    if len(unknown) > 0:
        print("unknown arguments: %s" % unknown)

    if args.repo_x is None:
    	print("ERROR! must set repo of cocos2d-x")
    	exit(1)

    beginSecond = time.time()
    print ">>> Bgein Compile at %s" % time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(beginSecond))

    compiler = CocosLibsCompiler(args)
    compiler.compile()

    endSecond = time.time()
    print ">>> Bgein Compile at %s" % time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(beginSecond))
    print ">>> End Compile at %s" % time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(endSecond))
    interSecond = endSecond - beginSecond
    interSecond = int(interSecond)
    print ">>> Use Second %d" % interSecond
    houre = interSecond/(60*60)
    interSecond = interSecond%(60*60)
    minute = interSecond/60
    second = interSecond%60
    print ">>> Use Time %d:%d:%d" % (houre, minute, second)

