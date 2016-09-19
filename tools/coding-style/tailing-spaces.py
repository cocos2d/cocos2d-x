#!/usr/bin/env python
#coding=utf-8

'''
Remove tailing whitespaces and ensures one and only one empty ending line.
'''

import os, re

def scan(*dirs, **kwargs):
  files = []
  extensions = kwargs['extensions'] if kwargs.has_key('extensions') else None
  excludes = kwargs['excludes'] if kwargs.has_key('excludes') else []
  for top in dirs:
    for root, dirnames, filenames in os.walk(top):
      dirnames = [i for i in dirnames if i in excludes]
      for f in filenames:
        if f in excludes:
          continue
        ext = os.path.splitext(f)[1].lower()
        if extensions is None or ext in extensions:
          files.append(os.path.join(root, f))
  return files

def fixone(src):
  lines = open(src, 'r').readlines()

  trimed = []
  for line in lines:
    trimed.append(re.sub('\s+$', '', line))

  while len(trimed) > 1 and not trimed[-1]:
    trimed.pop()
  trimed.append('')

  with open(src, 'w') as f:
    for line in trimed:
      f.write('%s\n' % line)


def lint(root):
  print('Checking tailing whitespaces in: %s' % root)
  dirs = [
    os.path.join(root, 'cocos'),
    os.path.join(root, 'extensions'),
    os.path.join(root, 'templates'),
    os.path.join(root, 'tests'),
    os.path.join(root, 'tools', 'simulator')
  ]

  files = scan(*dirs, extensions=['.c', '.cpp', '.h', '.hpp', '.m', '.mm', '.java'])
  for f in files:
    print(f)
    fixone(f)


def main():
  default_root = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
  lint(default_root)

main()
