#!/usr/bin/env python3
import os
import sys

base_dir = sys.path[0]
if sys.platform.startswith('win'):
    dir_char = '\\'
else:
    dir_char = '/'
base_dir += dir_char


def run(use_txt=False):
    cmd = base_dir + 'cmake-build-debug' + dir_char + 'ACM' + (
        ' < ' + base_dir + 'cmake-build-debug' + dir_char + 'input.txt' if use_txt else '')
    os.system(cmd)


if __name__ == '__main__':
    to_build = '-b' in sys.argv or '-br' in sys.argv
    to_run = '-r' in sys.argv or '-b' not in sys.argv
    if '-h' in sys.argv:
        print('usage: run.py:\n'
              '\tbuild or run:\n'
              '\t\t[ -b ] : build\n'
              '\t\t[ -r ] : run\n'
              '\t\t[ -br] : build and run\n'
              '\t\t(it will run if neither of commands in "build or run")\n'
              '\t[ -i ] : use input.txt as input\n'
              '\t[ -h ] : help')
        exit(0)
    if to_build:
        os.system('g++ -std=c++11 ' + base_dir + 'main.cpp -o ' + base_dir + 'cmake-build-debug' + dir_char + 'ACM')
    if to_run:
        run('-i' in sys.argv)
