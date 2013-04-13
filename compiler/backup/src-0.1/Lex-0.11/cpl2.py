#! /usr/bin/env python
import os
import glob
import stat
#rm result.txt or error.txt if they exist
if glob.glob('*.txt'):
    os.popen('rm *.txt')
else:
    pass
os.popen('gcc -g *.c 2>error.txt')
err_siz=os.stat('error.txt')[stat.ST_SIZE]
if not err_siz:#no compile terror
    os.popen('rm error.txt')
    a=os.popen('./a.out > result.txt')
else:
    pass
