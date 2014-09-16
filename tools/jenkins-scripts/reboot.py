#!/usr/bin/python
import sys,os,string
import paramiko
import socket

remote_machines=os.environ['REMOTE_MACHINES']
remote_machines=remote_machines.split(', ')
print 'remote_machines',remote_machines

remote_dir=os.environ['REMOTE_DIR']
remote_dir=remote_dir.split(', ')
print 'remote_dir',remote_dir

remote_ip=os.environ['REMOTE_IP']
remote_ip=remote_ip.split(', ')
print 'remote_ip',remote_ip

remote_user=os.environ['REMOTE_USER']
remote_user=remote_user.split(', ')
print 'remote_user',remote_user

remote_port=os.environ['REMOTE_PORT']
remote_port=remote_port.split(', ')
print 'remote_port',int(remote_port[0])

all_machines = {}
def set_default_value_to_all_machines():
	for idx, item in enumerate(remote_machines):
		all_machines[item]={}
		all_machines[item]['ip']=remote_ip[idx]
		all_machines[item]['dir']=remote_dir[idx]
		all_machines[item]['port']=remote_port[idx]
		all_machines[item]['user']=remote_user[idx]
		all_machines[item]['pwd']=os.environ[item+'_PWD']

def reboot_machine(machine, item):
	print 'machine:',machine, 'item:', item
	remote_ip = machine['ip']
	remote_port = machine['port']
	remote_user = machine['user']
	remote_pwd = machine['pwd']
	remote_dir = os.path.join(machine['dir'],'workspace','reboot', 'reboot.py')
	print remote_dir
	ssh = paramiko.SSHClient()
	print 'ssh:',ssh
	ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
	ssh.connect(remote_ip, int(remote_port), remote_user, remote_pwd)
	# excute reboot.py on machine
	cmd = 'python '+remote_dir
	if item == 'win32_win7':
		cmd = 'cmd.exe /c "python '+remote_dir+'"'
	stdin, stdout, stderr = ssh.exec_command(cmd)
	print stdout.readlines()
	ssh.close()
	print 'OK'

def main():
	print 'in main'
	set_default_value_to_all_machines()
	for item in all_machines:
		reboot_machine( all_machines[item], item )

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

