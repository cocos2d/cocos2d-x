'''
Removes timestamp and line info from a webgl log
'''

import os, sys, re

__rootpath__ = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
def path_from_root(*pathelems):
  return os.path.join(__rootpath__, *pathelems)

def nice(x):
  return '0x' + ('0' * (len(x)-6)) + x[2:].upper()

repdata = open(path_from_root('system', 'include', 'GL', 'gl.h')).readlines() + ['\n'] + \
          open(path_from_root('system', 'include', 'GL', 'glext.h')).readlines()
reps = {}
for rep in repdata:
  rep = rep.replace('\t', ' ').replace('\n', '')
  parts = filter(lambda part: part != '', rep.split(' '))
  if len(parts) == 3 and parts[0] == '#define':
    reps[nice(parts[2])] = '%s (%s)' % (parts[1], parts[2])

lines = sys.stdin.read().split('\n')

for line in lines:
  if line.startswith('['):
    line = line[15:]
  line = line.split(' @ ')[0]
  line = re.sub('(0x[\dabcdef]+)', lambda hexx: reps[nice(hexx.group(0))] if nice(hexx.group(0)) in reps else nice(hexx.group(0)), line)
  print line

#for i in range(100):
#  print

