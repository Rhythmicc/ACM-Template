#!/usr/bin/env python3
import os
import sys

base_dir = sys.path[0]
if sys.platform.startswith('win'):
    dir_char = '\\'
else:
    dir_char = '/'
base_dir += dir_char


def run():
    os.system(
        base_dir + 'cmake-build-debug' + dir_char + 'ACM < ' + base_dir + 'cmake-build-debug' + dir_char + 'input.txt')


if __name__ == '__main__':
    if len(sys.argv) < 2:
        run()
        exit(0)
    elif len(sys.argv) != 2:
        print('usage: run.py [-b / -r / -br]')
        exit(-1)
    elif sys.argv[1] == '-br' or sys.argv[1] == '-b':
        os.system('g++ -std=c++11 ' + base_dir + 'main.cpp -o ' + base_dir + 'cmake-build-debug' + dir_char + 'ACM')
    if sys.argv[1] != '-b':
        run()
