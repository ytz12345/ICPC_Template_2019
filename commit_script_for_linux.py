import os
import sys

n = len(sys.argv)
if n == 1:
	print('Please input some comments.')
	exit(0)
s = sys.argv[1]
for i in range(2, n):
	s += ' ' + sys.argv[i]

os.system('git add -A')
os.system('git commit -m \'' + s + '\'')
os.system('git push')