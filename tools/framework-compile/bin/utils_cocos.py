#!/usr/bin/python
#-*- coding: UTF-8 -*-

import os
import sys
import shutil

if sys.platform == 'win32':
	import _winreg

def get_required_vs_version(proj_file):
		# Now VS2012 is the mini version required
		return "11.0"

def get_vs_cmd_path(vs_reg, proj_path, vs_version):
	# get required vs version
	required_vs_version = get_required_vs_version(proj_path)
	if required_vs_version is None:
		raise Exception("Can't parse the sln file to find required VS version")

	# get the correct available VS path
	needUpgrade = False
	vsPath = None

	if vs_version is None:
		i = 0
		try:
			while True:
				version = _winreg.EnumKey(vs_reg, i)
				try:
					if float(version) >= float(required_vs_version):
						key = _winreg.OpenKey(vs_reg, r"SxS\VS7")
						vsPath, type = _winreg.QueryValueEx(key, version)

						if float(version) > float(required_vs_version):
							needUpgrade = True

						key.close()
						break
				except:
					pass
				i += 1
		except WindowsError:
			pass
	else:
		if vs_version == 2012:
			vs_ver = "11.0"
			needUpgrade = False
		else:
			vs_ver = "12.0"
			needUpgrade = True

		try:
			key = _winreg.OpenKey(vs_reg, r"SxS\VS7")
			vsPath, type = _winreg.QueryValueEx(key, vs_ver)
		except:
			raise Exception("Can't find VS%d" % vs_version)

	if vsPath is None:
		message = "Can't find correct Visual Studio's path in the regedit"
		raise Exception(message)

	commandPath = os.path.join(vsPath, "Common7", "IDE", "devenv")
	return (commandPath, needUpgrade)

def rmdir(folder):
	if os.path.exists(folder):
		shutil.rmtree(folder)

def mkdir(folder):
	if not os.path.exists(folder):
		os.makedirs(folder)

def cpdir(source, dest):
	source_dir = source
	dest_dir = dest

	if not os.path.exists(source_dir):
		raise Exception("cpdir source_dir (%s) not exists" % source_dir)

	mkdir(dest_dir)

	for f in os.listdir(source_dir):
		path = os.path.join(source_dir, f)
		if os.path.isfile(path):
			shutil.copy(path, dest_dir)
		elif os.path.isdir(path):
			new_dest = os.path.join(dest_dir, f)
			cpdir(path, new_dest)

def win2unix(filePath):
	try:
		oldfile = open(filePath, "rb+")
		path, name = os.path.split(filePath)
		newfile = open(path + '$' + name, "wa+")

		old = b'\r'
		new = b''

		data = b''
		while (True):
			data = oldfile.read(200)
			newData = data.replace(old, new)
			newfile.write(newData)
			if len(data) < 200:
				break
		newfile.close()
		oldfile.close()

		os.remove(filePath)
		os.rename(path + '$' + name, filePath)
	except IOError as e:
		print(e)





