#!/usr/bin/env python
#coding=utf-8

import os, re, argparse, sys
import posixpath

class Path:
  @staticmethod
  def _forward_slash(p):
    return p.replace(os.path.sep, '/')

  @staticmethod
  def join(p, *paths):
    return Path._forward_slash(posixpath.join(p, *paths))

  @staticmethod
  def abspath(p):
    return Path._forward_slash(posixpath.abspath(p))

  @staticmethod
  def normpath(p):
    return Path._forward_slash(posixpath.normpath(p))

  @staticmethod
  def relpath(p, s):
    return Path._forward_slash(posixpath.relpath(p, s))

  @staticmethod
  def exists(p):
    return os.path.exists(p)

  @staticmethod
  def basename(p):
    return posixpath.basename(p)

  @staticmethod
  def extname(p):
    return posixpath.splitext(p)[1]

  @staticmethod
  def dirname(p):
    return posixpath.dirname(p)

class LintContext:
  def __init__(self, root, fix):
    self.exclude = [
      # exclude some platform specific files.
      'editor-support/spine/Json.c',
      'editor-support/spine/PathConstraint.h',
      'editor-support/spine/SkeletonJson.c',
      'editor-support/spine/SkeletonBinary.c',
      'editor-support/spine/kvec.h'
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
    # find all sources and headers relative to self.root
    self.sources = []
    self.headers = []
    for root, dirnames, filenames in os.walk(top):
      for f in filenames:
        p = Path.relpath(Path.join(root, f), top)
        if self._source_to_lint(p):
          self.sources.append(p)
        if self._is_header(p):
          self.headers.append(p)

  def _source_to_lint(self, p):
    if p in self.exclude:
      return False
    ext = Path.extname(p)
    return ext in self.source_exts

  def _is_header(self, name):
    return Path.extname(name) in self.header_exts

  # find headers have unique base filenames
  # this is used to get included headers in other search paths
  def _scan_unique_headers(self, headers):
    known = {}
    for f in headers:
      name = Path.basename(f)
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
    return Path.exists(Path.join(self.root, filename))

  def find_uniq(self, basename):
    return self.uniq[basename] if self.uniq.has_key(basename) else None

  def get_include_path(self, original, directory):
    # 1. try search in uniq cocos header names
    p = self.find_uniq(Path.basename(original))
    if not p:
      # 2. try search in current header directory
      p = Path.normpath(Path.join(directory, original))
      if not self.in_search_path(p):
        return None
    return p

def fix(match, cwd, ctx, fixed):
  h = match.group(2)
  # return original if already in search path (cocos directory)
  if ctx.in_search_path(h):
    return match.group(0)

  p = ctx.get_include_path(h, cwd)
  if not p:
    return match.group(0)

  ctx.errors += 1
  fix = '#%s "%s"' % (match.group(1), p)
  fixed[match.group(0)] = fix
  return fix

def lint_one(header, ctx):
  cwd = Path.dirname(header)
  if not cwd:
    return

  filename = Path.join(ctx.root, header)
  content = open(filename, 'r').read()
  fixed = {}
  # check all #include "header.*"
  linted = re.sub('#\s*(include|import)\s*"(.*)"', lambda m: fix(m, cwd, ctx, fixed), content)
  if content != linted:
    ctx.error_files += 1
    if ctx.fix:
      with open (filename, 'w') as f: f.write(linted)
      print('%s: %d error(s) fixed' % (header, len(fixed)))
    else:
      print('%s:' % (header))
      for k, v in fixed.iteritems():
        print('\t%s should be %s' % (k, v))


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
  default_root = Path.abspath(Path.join(Path.dirname(__file__), '..', '..'))
  parser = argparse.ArgumentParser(description='The cocos headers lint script.')
  parser.add_argument('-f','--fix', action='store_true', help='fixe the headers while linting')
  parser.add_argument('root', nargs='?', default= default_root, help='path to cocos2d-x source root directory')
  args = parser.parse_args()

  lint(LintContext(Path.join(args.root, 'cocos'), args.fix))

main()
