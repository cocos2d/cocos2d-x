#!/usr/bin/env python
#coding=utf-8

import os, re, argparse, sys
import posixpath
path = posixpath


class LintContext:
  def __init__(self, root, fix):
    self.exclude = [
      # we are leaving win8.1 and winrt pch.cpp unchanged.
      'platform/win8.1-universal/pch.cpp',
      'platform/winrt/pch.cpp'
    ]
    self.source_exts = ['.h','.hpp','.inl','.c','.cpp', '.m', '.mm']
    self.header_exts = ['.h','.hpp','.inl']
    self.root = root
    self.fix = fix
    self.errors = 0
    self.error_files = 0
    self._scan_source(root)
    self._scan_unique_headers(self.headers)

  def _scan_source(self, top):
    # find all headers relative to self.root
    headers = []
    sources = []
    for root, dirnames, filenames in os.walk(top):
      sources += [path.join(root, f)[len(top)+1:] for f in filenames if self._source_to_lint(root, f)]
    self.headers = [f for f in sources if self._is_header(f)]
    self.sources = sources

  def _source_to_lint(self, directory, name):
    if path.relpath(path.join(directory, name), self.root) in self.exclude:
      return False
    ext = path.splitext(name)[1]
    return ext in self.source_exts

  def _is_header(self, name):
    return path.splitext(name)[1] in self.header_exts

  # find headers have unique base filenames
  # this is used to get included headers in other search paths
  def _scan_unique_headers(self, headers):
    known = {}
    for f in headers:
      name = path.basename(f)
      if known.has_key(name):
        known[name].append(f)
      else:
        known[name] = [f]
    uniq = {}
    for k,v in known.iteritems():
      if len(v) == 1:
        uniq[k] = v[0]
    self.uniq = uniq

  def in_search_path(self, filename):
    return path.exists(path.join(self.root, filename))

  def find_uniq(self, basename):
    return self.uniq[basename] if self.uniq.has_key(basename) else None

  def get_include_path(self, original, directory):
    # 1. try search in uniq cocos header names
    p = self.find_uniq(path.basename(original))
    if not p:
      # 2. try search in current header directory
      p = path.normpath(path.join(directory, original))
      if not self.in_search_path(p):
        return None
    return p

def fix(match, cwd, ctx, fixed):
  h = match.group(1)
  # return original if already in search path (cocos directory)
  if ctx.in_search_path(h):
    return match.group(0)

  path = ctx.get_include_path(h, cwd)
  if not path:
    return match.group(0)

  ctx.errors += 1
  fixed[h] = path
  return '#include "%s"' % (path)

def lint_one(header, ctx):
  cwd = path.dirname(header)
  if not cwd:
    return

  filename = path.join(ctx.root, header)
  content = open(filename, 'r').read()
  fixed = {}
  # check all #include "header.*"
  linted = re.sub('#\s*include\s*"(.*)"', lambda m: fix(m, cwd, ctx, fixed), content)
  if content != linted:
    ctx.error_files += 1
    if ctx.fix:
      with open (filename, 'w') as f: f.write(linted)
      print('%s: %d error(s) fixed' % (header, len(fixed)))
    else:
      print('%s:' % (header))
      for k, v in fixed.iteritems():
        print('\t#include "%s" should be #include "%s"' % (k, v))


def lint(ctx):
  print('Checking headers in: %s' % ctx.root)
  for f in ctx.sources:
    lint_one(f, ctx)

  print('Total: %d errors in %d files' % (ctx.errors, ctx.error_files))
  if ctx.errors > 0:
    if ctx.fix:
      print('All fixed')
    else:
      print('Rerun this script with -f to fixes these errors')
      sys.exit(1)


def main():
  default_root = path.abspath(path.join(path.dirname(__file__), '..', '..'))
  parser = argparse.ArgumentParser(description='The cocos headers lint script.')
  parser.add_argument('-f','--fix', action='store_true', help='fixe the headers while linting')
  parser.add_argument('root', nargs='?', default= default_root, help='path to cocos2d-x source root directory')
  args = parser.parse_args()

  lint(LintContext(path.join(args.root, 'cocos'), args.fix))

main()
