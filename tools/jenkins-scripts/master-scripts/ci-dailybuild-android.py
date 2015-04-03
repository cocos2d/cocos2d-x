import os
import json
from shutil import copy
import sys
import traceback
import MySQLdb
from email.mime.text import MIMEText
import smtplib
import datetime
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

def connect_db():
    db_host = os.environ['db_host']
    db_user = os.environ['db_user']
    db_pw = os.environ['db_pw']
    db = MySQLdb.connect(db_host, db_user, db_pw, "dailybuild" )
    return db

def close_db(db):
    db.close()

def save_build_stats(db, filename, size):
    cursor = db.cursor()
    sql = "INSERT INTO %s (size, createdTime) VALUES(%d, now())" % (filename, size)
    print sql
    cursor.execute(sql)
    db.commit()

def scan_all_libs(db):
    stats = {}
    _path = 'tests/cpp-empty-test/proj.android/libs/armeabi/libcpp_empty_test.so'
    filesize = os.path.getsize(_path)/1024
    stats['libcpp_empty_test'] = filesize
    save_build_stats(db, 'libcpp_empty_test', filesize)
    _path = 'tests/lua-empty-test/project/proj.android/libs/armeabi/liblua_empty_test.so'
    filesize = os.path.getsize(_path)/1024
    stats['liblua_empty_test'] = filesize
    save_build_stats(db, 'liblua_empty_test', filesize)
    lib_path = './tests/cpp-tests/proj.android/obj/local/armeabi'
    for root, dirs, files in os.walk(lib_path):
      for _file in files:
        if not _file.endswith(".a"):
          continue
        print _file
        libfile = lib_path + '/' + _file
        _filename = _file.split('.')[0]
        filesize = os.path.getsize(libfile)/1024
        stats[_filename]=filesize
        save_build_stats(db, _filename, filesize)
    return stats

def send_mail(sub,title,content):
    #to_list = os.environ['EMAIL_LIST'].split(' ')
    mail_user = os.environ['EMAIL_USER']
    mail_pass = os.environ['EMAIL_PWD']
    to_list = os.environ['EMAIL_LIST'].split(' ')
    mail_postfix = 'gmail.com'
    me = mail_user + "<" + mail_user + "@" + mail_postfix + ">"
    msg = MIMEText(content, _subtype='plain', _charset='gb2312')
    msg['Subject'] = sub
    msg['From'] = me
    msg['To'] = " ".join(to_list)
    print 'to users:', msg['To']
    msg['Content'] = 'test'
    try:
        s = smtplib.SMTP('smtp.gmail.com', 587)
        s.ehlo()
        s.starttls()
        s.login(mail_user,mail_pass)
        s.sendmail(me, to_list, str(msg))
        print 'info:', me, to_list, str(msg)
        s.close()
        return True
    except Exception, e:
        print str(e)
        return False

def sendEmail(stats):
    now = datetime.datetime.now()
    sub = "Cocos2d-x Android dailybuild stats of " + now.strftime("%Y-%m-%d")
    title = "Dailybuild stats"
    content = "The following list tracks the sizes of Cocos2d-x Android built libraries:\n"

    for key in stats:
        content += key 
        content += " : "
        content += str(stats[key]) + "KB"
        content += "\n"

    send_mail(sub, title, content)

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
      db = connect_db()
      stats = scan_all_libs(db)
      close_db(db)
      sendEmail(stats)
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

