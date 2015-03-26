#!/usr/bin/python
# check crash of cppemptytest
# install/open/uninstall apk
# perpose: for emptytest.
# now support: android
# will add: autotest-win7

import os
import sys
import json
import time
import socket
import platform
import threading
import codecs
import re
import paramiko

payload = {}
#get payload from os env
if os.environ.has_key('payload'):
    payload_str = os.environ['payload']
    #parse to json obj
    payload = json.loads(payload_str)
print 'payload:',payload
pr_num = 6326
#get pull number
if payload.has_key('number'):
    pr_num = payload['number']
print 'pr_num:' + str(pr_num)
run_app_time = 5
if os.environ.has_key('RUN_APP_TIME'):
    run_app_time = os.environ['RUN_APP_TIME']
print 'run_app_time:', run_app_time

test_name = ['cpp_empty_test']
if os.environ.has_key('TESTS_NAME'):
    temp_var = os.environ['TESTS_NAME']
    test_name = temp_var.split(', ')
package_name = ['org.cocos2dx.cpp_empty_test']
if os.environ.has_key('PACKAGE_NAME'):
    temp_var = os.environ['PACKAGE_NAME']
    package_name = temp_var.split(', ')
activity_name = ['org.cocos2dx.cpp_empty_test.AppActivity']
if os.environ.has_key('ACTIVITY_NAME'):
    temp_var = os.environ['ACTIVITY_NAME']
    activity_name = temp_var.split(', ')
gIdx = 0
if os.environ.has_key('TEST_INDEX'):
    gIdx = os.environ('TEST_INDEX')

current_platform = platform.system()
print 'current platform is:', current_platform

arrDevices = []
def getDevices():
    cmd = 'adb devices'
    info_devices = os.popen(cmd).read()
    arr_info = info_devices.split('\n')
    del arr_info[0]
    count = 0
    for device in arr_info:
        if len(device) > 0:
            count += 1
            print 'device ', count,device
            deviceInfo = device.split(' ')
            global arrDevices
            obj = {}
            obj['name']  = deviceInfo[0]
            arrDevices.append(obj)
    return count

def getADBDeviceIP(device_name):
    output = os.popen("adb -s "+device_name+" shell netcfg")
    configs = output.read().split('\r\n')
    output.close()
    for l in configs:
        items = l.split()
        if len(items)>1 and items[1] == 'UP':
            if items[2].find('127.0.0.1') < 0 and items[2].find('0.0.0.0') < 0:
                return items[2]
    return False
def mapIP():
    for device in arrDevices:
        ip_d = getADBDeviceIP(device['name'])
        device['ip'] = ip_d

allThreadIsRunning = {}
def setThreadStatus():
    for device in arrDevices:
        allThreadIsRunning[device['name']] = 1

devices_info = {}
info_list = '{"product":["model","brand","name","cpu.abi","cpu.abi2","manufacturer","locale.language","locale.region"],"build":["id","version.sdk","version.release"]}'
if os.environ.has_key('DEVICE_INFO_LIST'):
    info_list = os.environ['DEVICE_INFO_LIST']
info_list = eval(info_list)
def getDeviceInfoByName(name):
    cmd = ''
    dev_name = name
    if len(name) > 0:
        cmd = 'adb -s '+name+' shell cat /system/build.prop'
    else:
        cmd = 'adb shell cat /system/build.prop'
        dev_name = 'device one'
    pip_cat = os.popen(cmd)
    read_info = pip_cat.read()
    read_info_list = read_info.split('\r\n')
    device_info_one = {}
    def checkProperty(item_str, device_name):
        for argv in info_list:
            for item in info_list[argv]:
                prop = argv+'.'+item
                if item_str.find(prop) > -1:
                    arr_item = item_str.split('=')
                    device_info_one[prop] = arr_item[1]
                    break
    for item in read_info_list:
        checkProperty(item, dev_name)
    devices_info[dev_name] = device_info_one

#getDeviceInfoByName('')
#print 'device_info:',device_info
def getDeviceInfomation():
    for device in arrDevices:
        getDeviceInfoByName(device['name'])

info_empty_test = {}
info_empty_test_pro = ['install','open','socket','uninstall']
def init_info_empty_test():
    for item in info_empty_test_pro:
        info_empty_test[item] = {}
init_info_empty_test()

apk_name = 'apks/'+test_name[gIdx]+'/'+test_name[gIdx]+'_'+str(pr_num)+'.apk'
def install_apk_on_device(device):
    name = device['name']
    cmd = 'adb -s '+name+' install '+apk_name
    print 'install on '+name
    info_install = os.popen(cmd).read()
    print 'infomation of install apk:', info_install
    info_install_arr = info_install.split('\r\n')
    info_install_result = False
    for item in info_install_arr:
        if item.find('Success') > -1:
            info_install_result = True
    info_empty_test['install'][name] = info_install_result
    return True

def open_apk_on_device(device):
    print 'will open activity:'
    name = device['name']
    cmd = 'adb -s '+name+' shell am start -n '+package_name[gIdx]+'/'+activity_name[gIdx]
    # print 'start activity:', cmd
    info_start = os.popen(cmd).read()
    info_start = info_start.split('\r\n')
    # print 'info_start:', info_start
    info_start_result = True
    for info in info_start:
        if info.find('Error:') > -1:
            print 'infomation of open activity:',info
            info_start_result = False
    info_empty_test['open'][name] = info_start_result
    return True

PORT = 5678
def socket_status_on_device(device):
    name = device['name']
    ip = device['ip']
    soc = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
    status_socket = False
    info_of_socket_result = ''
    try:
        print 'telnet ', ip, PORT
        soc.connect((ip, PORT))
        cmd = 'resolution\r\n'
        print 'connected successfully.'
        print 'send console command: resolution'
        soc.send(cmd)
        while True:
            data = soc.recv(1024)
            if len(data):
                print data
                if data.find('size:') > -1:
                    info_of_socket_result = 'OK'
                    print 'close', test_name[gIdx]
                    soc.send('director end')
                    status_socket = True
                    break
            if not data:
                info_of_socket_result = test_name[gIdx]+' is crashed!'
                break
    except Exception, e:
        info_of_socket_result = test_name[gIdx]+' is crashed!'
    time.sleep(2)
    soc.close()
    time.sleep(2)
    info_empty_test['socket'][name] = info_of_socket_result
    return status_socket

def uninstall_apk_on_device(device):
    # adb shell pm uninstall -n org.cocos2dx.hellolua
    print 'uninstall ', test_name[gIdx]
    name = device['name']
    cmd = 'adb -s '+name+' shell pm uninstall -n '+package_name[gIdx]
    info_uninstall = os.popen(cmd).read()
    info_uninstall_result = ''
    if info_uninstall.find('Success') > -1:
        info_uninstall_result = 'OK'
    else:
        info_uninstall_result = 'uninstall Failed!'
    info_empty_test['uninstall'][name] = info_uninstall_result
    return True

def excute_test_on_device(device):
    uninstall_apk_on_device(device)
    print device
    info_install = install_apk_on_device(device)
    print 'install:', info_install
    info_open = open_apk_on_device(device)
    print 'open:', info_open
    time.sleep(3)
    info_socket = socket_status_on_device(device)
    print 'socket:', info_socket
    info_uninstall = uninstall_apk_on_device(device)
    print 'uninstall:', info_uninstall
    allThreadIsRunning[device['name']] = 0

address_of_result_html = ''
def send_result_to_master():
    if not os.environ.has_key('REMOTE_IP'):
        return false
    remote_ip = os.environ['REMOTE_IP']
    remote_port = os.environ['REMOTE_PORT']
    remote_user = os.environ['REMOTE_USER']
    remote_pwd = os.environ['REMOTE_PWD']
    remote_dir = os.environ['REMOTE_DIR']
    remote_dir = remote_dir + str(pr_num)+'/'
    print remote_dir
    ssh = paramiko.SSHClient()
    print 'ssh:',ssh
    ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    ssh.connect(remote_ip, int(remote_port), remote_user, remote_pwd)
    # create dir
    stdin, stdout, stderr = ssh.exec_command("mkdir "+remote_dir)
    ssh.close()
    trans = paramiko.Transport((remote_ip,int(remote_port)))
    trans.connect(username = remote_user, password = remote_pwd)
    sftp = paramiko.SFTPClient.from_transport(trans)
    remotepath = remote_dir+test_name[gIdx]+'_'+str(pr_num)+'.html'
    localpath = 'html/cpp_empty_test/cpp_empty_test_'+str(pr_num)+'.html'
    sftp.put(localpath, remotepath)
    sftp.close()
    result_dir = remote_dir.replace('/data',':9000')
    global address_of_result_html
    address_of_result_html = 'http://'+remote_ip+result_dir+test_name[gIdx]+'_'+str(pr_num)+'.html'
    
def check_thread_is_running():
    while 1:
        in_running = 0
        for key in allThreadIsRunning:
            in_running = in_running + allThreadIsRunning[key]
        # print 'in_running:', in_running
        time.sleep(3)
        if not in_running:
            break
    print 'all cpp emptytest is finished.'
    log_emptytest_result()
    print 'will send result:'
    send_result_to_master()
    print 'end of check thread is running.'
    print 'address of result is:',address_of_result_html

def generate_html_with_result(result):
    target_path = 'html/cpp_empty_test/cpp_empty_test_'+str(pr_num)+'.html'
    data = codecs.open('hello.html', encoding='UTF-8').read()
    data = re.sub("content", result, data)
    codecs.open(target_path, 'wb', encoding='UTF-8').write(data)

empty_test_result = True
str_result = ''
def log_emptytest_result():
    def appendToResult(one_str):
        global str_result
        str_result = str_result + one_str + '\r\n'
    appendToResult('<pre>')
    appendToResult('empty test start:')
    for device in arrDevices:
        name = device['name']
        appendToResult('device infomation of : '+name)
        for key in devices_info[name]:
            appendToResult('\t'+key+':'+devices_info[name][key])
        appendToResult('install: ' + str(info_empty_test['install'][name]))
        appendToResult('open: ' + str(info_empty_test['open'][name]))
        appendToResult('telnet ' + str(device['ip'])+' : ' + str(info_empty_test['socket'][name]))
        appendToResult('close: ' + str(info_empty_test['socket'][name]))
        appendToResult('uninstall: ' + str(info_empty_test['uninstall'][name]))
        if not info_empty_test['install'][name] or not info_empty_test['open'][name] or not info_empty_test['socket'][name] or not info_empty_test['uninstall'][name]:
            empty_test_result = False
            appendToResult('run failed!')
        else: appendToResult('run successfully!')
        appendToResult('')
    appendToResult('empty test end.</pre>')
    generate_html_with_result(str_result)
    print 'log empty test end'

class myThread(threading.Thread):
    def __init__(self,threadname):
        threading.Thread.__init__(self,name=threadname)
    def run(self):
        time.sleep(2)
        device = self.getName()
        print type(device)
        device = eval(device)
        print type(device), device
        excute_test_on_device(device)

def run_emptytest():
    for device in arrDevices:
        th = myThread(device)
        th.start()

def main():
    print 'in main:'
    getDevices()
    if len(arrDevices):
        mapIP()
        setThreadStatus()
        print 'arrDevices:',arrDevices
        time.sleep(1)
    else:
        print 'there is no device for emptytest, please check devices!'
        return 1
    if len(arrDevices):
        getDeviceInfomation()
    run_emptytest()
    check_thread_is_running()
    print 'info_empty_test:', info_empty_test
    print 'empty test end', empty_test_result
    if empty_test_result:
        return 0
    else:
        return 1

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
