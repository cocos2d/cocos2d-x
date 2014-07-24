import os
import platform
import json
from shutil import copy
import sys
import traceback
import MySQLdb

def check_current_3rd_libs():
    #get current_libs config
    backup_files = range(2)
    current_files = range(2)
    config_file_paths = ['external/config.json','templates/lua-template-runtime/runtime/config.json']
    for i, config_file_path in enumerate(config_file_paths):
        if not os.path.isfile(config_file_path):
            raise Exception("Could not find 'external/config.json'")

        with open(config_file_path) as data_file:
            data = json.load(data_file)

        current_3rd_libs_version = data["version"]
        filename = current_3rd_libs_version + '.zip'
        node_name = os.environ['NODE_NAME']
        backup_file = '../cocos-2dx-external/node/' + node_name + '/' + filename
        backup_files[i] = backup_file
        current_file = filename
        current_files[i] = current_file
        if os.path.isfile(backup_file):
          copy(backup_file, current_file)
    #run download-deps.py
    os.system('python download-deps.py -r no')
    #backup file
    for i, backup_file in enumerate(backup_files):
        current_file = current_files[i]
        copy(current_file, backup_file)

def strip_android_libs():
    strip_cmd = os.environ['ndk_strip']
    print strip_cmd
    _cmd = strip_cmd + ' ./tests/cpp-tests/proj.android/obj/local/armeabi/*.a'
    os.system(_cmd)

def save_build_stats(filename, size):
    db_host = os.environ['db_host']
    db_user = os.environ['db_user']
    db_pw = os.environ['db_pw']
    db = MySQLdb.connect(db_host, db_user, db_pw, "dailybuild" )
    cursor = db.cursor()
    sql = "INSERT INTO %s (size, createdTime) VALUES(%d, now())" % (filename, size)
    print sql
    cursor.execute(sql)
    db.commit()
    db.close()
def scan_all_libs():
    _path = 'tests/cpp-empty-test/proj.android/libs/armeabi/libcpp_empty_test.so'
    filesize = os.path.getsize(_path)/1024
    save_build_stats('libcpp_empty_test', filesize)
    _path = 'tests/lua-empty-test/project/proj.android/libs/armeabi/liblua_empty_test.so'
    filesize = os.path.getsize(_path)/1024
    save_build_stats('liblua_empty_test', filesize)
    lib_path = './tests/cpp-tests/proj.android/obj/local/armeabi'
    for root, dirs, files in os.walk(lib_path):
      for _file in files:
        if not _file.endswith(".a"):
          continue
        libfile = lib_path + '/' + _file
        _filename = _file.split('.')[0]
        filesize = os.path.getsize(libfile)/1024
        save_build_stats(_filename, filesize)

def main():
    print 'Build Config:'
    print '    Branch:v3'
    print '    Target:Android'
    print '    build script:python build/android-build.py -b release all'
    if(os.path.exists('build/android-build.py') == False):
      node_name = os.environ['NODE_NAME']
      source_dir = '../cocos-2dx-develop-base-repo/node/' + node_name + "/."
      os.system("cp -r " + source_dir + " .")

    os.system('git pull origin v3')
    os.system('git submodule update --init --force')
    check_current_3rd_libs()

    ret = os.system("python tools/jenkins-scripts/gen_jsb.py")
    if(ret != 0):
        return(1)

    ret = os.system('python build/android-build.py -b release all')
    if(ret == 0):
      strip_android_libs()
      scan_all_libs()
    os.system('git clean -xdf -f')
    print 'build exit'
    print ret
    if ret == 0:
      ret = 0
    else:
      ret = 1
    return ret

# -------------- main --------------
if __name__ == '__main__':
    sys_ret = 0
    try:    
        sys_ret = main()
    except:
        traceback.print_exc()
        sys_ret = 1
    finally:
        sys.exit(sys_ret)

