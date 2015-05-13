'''
Given two similar files, for example one with an additional optimization pass,
and with different results, will bisect between them to find the smallest
diff that makes the outputs different.
'''

import os, sys, shutil
from subprocess import Popen, PIPE, STDOUT

__rootpath__ = os.path.abspath(os.path.dirname(os.path.dirname(__file__)))
def path_from_root(*pathelems):
  return os.path.join(__rootpath__, *pathelems)
exec(open(path_from_root('tools', 'shared.py'), 'r').read())

file1 = open(sys.argv[1]).read()
file2 = open(sys.argv[2]).read()

leftf = open('left', 'w')
leftf.write(file1)
leftf.close()

rightf = open('right', 'w')
rightf.write(file2)
rightf.close()

def run_code(name):
  ret = run_js(name, stderr=PIPE, full_output=True)
  # fix stack traces
  ret = filter(lambda line: not line.startswith('    at ') and not name in line, ret.split('\n'))
  return '\n'.join(ret)

print 'running files'
left_result = run_code('left')
right_result = run_code('right') # right as in left-right, not as in correct
assert left_result != right_result

# Calculate diff chunks
print 'diffing'
diff = Popen(['diff', '-U', '5', 'left', 'right'], stdout=PIPE).communicate()[0].split('\n')
pre_diff = diff[:2]
diff = diff[2:]

chunks = []
curr = []
for i in range(len(diff)):
  if diff[i].startswith('@'):
    if len(curr) > 0:
      chunks.append(curr)
    curr = [diff[i]]
  else:
    curr.append(diff[i])
if len(curr) > 0:
  chunks.append(curr)

# Bisect both sides of the span, until we have a single chunk
high = len(chunks)

print 'beginning bisection, %d chunks' % high

for mid in range(high):
  print '  current: %d' % mid,
  # Take chunks from the middle and on. This is important because the eliminator removes variables, so starting from the beginning will add errors
  curr_diff = '\n'.join(map(lambda parts: '\n'.join(parts), chunks[mid:])) + '\n'
  difff = open('diff.diff', 'w')
  difff.write(curr_diff)
  difff.close()
  shutil.copy('left', 'middle')
  Popen(['patch', 'middle', 'diff.diff'], stdout=PIPE).communicate()
  shutil.copyfile('middle', 'middle' + str(mid))
  result = run_code('middle')
  print result == left_result, result == right_result#, 'XXX', left_result, 'YYY', result, 'ZZZ', right_result
  if mid == 0:
    assert result == right_result, '<<< ' + result + ' ??? ' + right_result + ' >>>'
    print 'sanity check passed (a)'
  if mid == high-1:
    assert result == left_result, '<<< ' + result + ' ??? ' + left_result + ' >>>'
    print 'sanity check passed (b)'
  if result != right_result:
    print 'found where it changes: %d' % mid
    found = mid
    break

critical = Popen(['diff', '-U', '5', 'middle' + str(mid-1), 'middle' + str(mid)], stdout=PIPE).communicate()[0]
c = open('critical.diff', 'w')
c.write(critical)
c.close()
print 'middle%d is like left, middle%d is like right, critical.diff is the difference that matters' % (mid-1, mid), 'diff:', critical

