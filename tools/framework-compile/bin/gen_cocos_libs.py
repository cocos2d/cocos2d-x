#!/usr/bin/python
#-*- coding: UTF-8 -*-

import os
import sys
import time
import shutil
import excopy
from argparse import ArgumentParser

def os_is_win32():
	return sys.platform == 'win32'

def is_32bit_windows():
	arch = os.environ['PROCESSOR_ARCHITECTURE'].lower()
	archw = os.environ.has_key("PROCESSOR_ARCHITEW6432")
	return (arch == "x86" and not archw)

def os_is_mac():
	return sys.platform == 'darwin'

def execute_command(cmdstring, cwd=None, timeout=None, shell=False):
	""" 执行一个SHELL命令
		封装了subprocess的Popen方法, 支持超时判断，支持读取stdout和stderr
		参数:
		cwd: 运行命令时更改路径，如果被设定，子进程会直接先更改当前路径到cwd
		timeout: 超时时间，秒，支持小数，精度0.1秒
		shell: 是否通过shell运行
		Returns: return_code
		Raises:  Exception: 执行超时
	"""

	import shlex
	import datetime
	import subprocess
	import time

	if shell:
		cmdstring_list = cmdstring
	else:
		cmdstring_list = shlex.split(cmdstring)
	if timeout:
		end_time = datetime.datetime.now() + datetime.timedelta(seconds=timeout)

	# 没有指定标准输出和错误输出的管道,因此会打印到屏幕上
	sub = None
	try:
		sub = subprocess.Popen(cmdstring_list, cwd=cwd, stdin=subprocess.PIPE, shell=shell, bufsize=4096)
	except Exception, e:
		print "execute command fail:%s" % cmdstring
		raise e

	# subprocess.poll()方法：检查子进程是否结束了，如果结束了，设定并返回码，放在subprocess.returncode变量中
	while sub.poll() is None:
		time.sleep(0.1)
		if timeout:
			if end_time <= datetime.datetime.now():
				raise Exception("Timeout：%s"%cmdstring)

	if 0 != sub.returncode :
		errStr = "[ERROR] execute command fail:%s" % cmdstring
		print errStr
		raise Exception(errStr)

	return sub.returncode


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
		if self.clean:
			self.clean_libs()
		if self.build_win:
			self.compile_win()
		if self.build_mac:
			self.compile_mac_ios()
		if self.build_android:
			#self.compile_android("lua")
			self.compile_android("js")

	def compile_win(self):
		if not os_is_win32():
			print "this is not win platform, needn't compile"
			return
		print "compile win"

	def compile_mac_ios(self):
		if not os_is_mac():
			print "this is not mac platform, needn't compile"
			return
		print "to compile mac"

		xcode_proj_info = {
			"build/cocos2d_libs.xcodeproj" : {
				"outputdir" : self.lib_dir,
				"targets"   : "libcocos2d",
			},
			"cocos/scripting/lua-bindings/proj.ios_mac/cocos2d_lua_bindings.xcodeproj" : {
				"outputdir" : self.lib_dir,
				"targets"   : "libluacocos2d",
			},
			"cocos/scripting/js-bindings/proj.ios_mac/cocos2d_js_bindings.xcodeproj" : {
				"outputdir" : self.lib_dir,
				"targets"   : "libjscocos2d",
			},
			"tools/simulator/libsimulator/proj.ios_mac/libsimulator.xcodeproj" : {
				"outputdir" : self.lib_dir,
				"targets"   : "libsimulator",
			}
		}

		XCODE_CMD_FMT = "xcodebuild -project \"%s\" -configuration Release -target \"%s\" %s CONFIGURATION_BUILD_DIR=%s"
		for key in xcode_proj_info.keys():
			output_dir = xcode_proj_info[key]["outputdir"]
			proj_path = os.path.join(self.repo_x, key)
			ios_out_dir = os.path.join(output_dir, "ios")
			mac_out_dir = os.path.join(output_dir, "mac")
			ios_sim_libs_dir = os.path.join(ios_out_dir, "simulator")
			ios_dev_libs_dir = os.path.join(ios_out_dir, "device")

			target = xcode_proj_info[key]["targets"]

			# compile ios simulator
			build_cmd = XCODE_CMD_FMT % (proj_path, "%s iOS" % target, "-sdk iphonesimulator ARCHS=\"i386 x86_64\" VALID_ARCHS=\"i386 x86_64\"", ios_sim_libs_dir)
			retVal = execute_command(build_cmd)
			if 0 != retVal:
				print "[ERROR] compile ios simulator fail"
				return retVal

			# compile ios device
			build_cmd = XCODE_CMD_FMT % (proj_path, "%s iOS" % target, "-sdk iphoneos", ios_dev_libs_dir)
			retVal = execute_command(build_cmd)
			if 0 != retVal:
				print "[ERROR] compile ios device fail"
				return retVal

			# compile mac
			build_cmd = XCODE_CMD_FMT % (proj_path, "%s Mac" % target, "", mac_out_dir)
			retVal = execute_command(build_cmd)
			if 0 != retVal:
				print "[ERROR] compile mac fail"
				return retVal

			# generate fat libs for iOS
			for lib in os.listdir(ios_sim_libs_dir):
				sim_lib = os.path.join(ios_sim_libs_dir, lib)
				dev_lib = os.path.join(ios_dev_libs_dir, lib)
				output_lib = os.path.join(ios_out_dir, lib)
				lipo_cmd = "lipo -create -output \"%s\" \"%s\" \"%s\"" % (output_lib, sim_lib, dev_lib)

				execute_command(lipo_cmd)

			# remove the simulator & device libs in iOS
			self.rmdir(ios_sim_libs_dir)
			self.rmdir(ios_dev_libs_dir)

			if not self.disable_strip:
				# strip the libs
				ios_strip_cmd = "xcrun -sdk iphoneos strip -S %s/*.a" % ios_out_dir
				execute_command(ios_strip_cmd)
				mac_strip_cmd = "xcrun strip -S %s/*.a" % mac_out_dir
				execute_command(mac_strip_cmd)

	def compile_android(self, language):
		print "compile android"
		# build .so for android
		CONSOLE_PATH = "tools/cocos2d-console/bin"
		SCRIPT_MK_PATH = "frameworks/runtime-src/proj.android/jni/Application.mk"
		ANDROID_A_PATH = "frameworks/runtime-src/proj.android/obj/local"

		android_out_dir = os.path.join(self.lib_dir, "android")
		engine_dir = self.repo_x
		console_dir = os.path.join(engine_dir, CONSOLE_PATH)
		cmd_path = os.path.join(console_dir, "cocos")
		proj_name = "My%sGame" % language
		proj_dir = os.path.join(self.cur_dir, "temp")
		proj_path = os.path.join(proj_dir, proj_name)
		self.rmdir(proj_path)

		# create a runtime project
		create_cmd = "%s new -l %s -t runtime -d %s %s" % (cmd_path, language, proj_dir, proj_name)
		execute_command(create_cmd)

		# Add multi ABI in Application.mk
		mk_file = os.path.join(proj_path, SCRIPT_MK_PATH)
		self.modify_mk(mk_file)

		# build it
		build_cmd = "%s compile -s %s -p android --ndk-mode release -j 4" % (cmd_path, proj_path)
		execute_command(build_cmd)

		# copy .a to prebuilt dir
		obj_dir = os.path.join(proj_path, ANDROID_A_PATH)
		copy_cfg = {
			"from": obj_dir,
			"to": android_out_dir,
			"include": [
				"*.a$"
			]
		}
		excopy.copy_files_with_config(copy_cfg, obj_dir, android_out_dir)

		if not self.disable_strip:
			# strip the android libs
			ndk_root = os.environ["NDK_ROOT"]
			if os_is_win32():
				if is_32bit_windows():
					bit_str = ""
				else:
					bit_str = "-x86_64"
				sys_folder_name = "windows%s" % bit_str
			elif os_is_mac():
				sys_folder_name = "darwin-x86_64"

			# strip arm libs
			strip_cmd_path = os.path.join(ndk_root, "toolchains/arm-linux-androideabi-4.8/prebuilt/%s/arm-linux-androideabi/bin/strip" % sys_folder_name)
			if os.path.exists(strip_cmd_path):
				strip_cmd = "%s -S %s/armeabi*/*.a" % (strip_cmd_path, android_out_dir)
				execute_command(strip_cmd, shell = True)

			# strip x86 libs
			strip_cmd_path = os.path.join(ndk_root, "toolchains/x86-4.8/prebuilt/%s/i686-linux-android/bin/strip" % sys_folder_name)
			if os.path.exists(strip_cmd_path) and os.path.exists(os.path.join(android_out_dir, "x86")):
				strip_cmd = "%s -S %s/x86/*.a" % (strip_cmd_path, android_out_dir)
				execute_command(strip_cmd, shell = True)

		# remove the project
		self.rmdir(proj_path)

	def modify_mk(self, mk_file):
		if os.path.isfile(mk_file):
			file_obj = open(mk_file, "a")
			file_obj.write("\nAPP_ABI :=armeabi armeabi-v7a x86\n")
			file_obj.close()

	def clean_libs(self):
		print "to clean libs"
		self.rmdir(self.lib_dir)

	def rmdir(self, folder):
		if os.path.exists(folder):
			shutil.rmtree(folder)

	def mkdir(self, folder):
		if not os.path.exists(folder):
			os.makedirs(folder)

	def cpdir(self, source, dest):
		source_dir = source
		dest_dir = dest

		if not os.path.exists(source_dir):
			raise Exception("cpdir source_dir (%s) not exists" % source_dir)

		self.mkdir(dest_dir)

		for f in os.listdir(source_dir):
			path = os.path.join(source_dir, f)
			if os.path.isfile(path):
				shutil.copy(path, dest_dir)
			elif os.path.isdir(path):
				new_dest = os.path.join(dest_dir, f)
				self.cpdir(path, new_dest)



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
	if not args.win and not args.mac and not args.android:
		args.all = True

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

