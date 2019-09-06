#!/usr/bin/env python3
import os
import sys

base_dir = sys.path[0]
if sys.platform.startswith('win'):
    dir_char = '\\'
else:
    dir_char = '/'
base_dir += dir_char


def run(use_txt=False, executable_file=base_dir + 'cmake-build-debug' + dir_char + 'ACM'):
    cmd = executable_file + (' < ' + inputfile if use_txt else '')
    os.system(cmd)


def red_col(string):
    return '\033[1;31m' + string + '\033[0m'


def blue_col(string):
    return '\033[1;34m' + string + '\033[0m'


if __name__ == '__main__':
    to_build = '-b' in sys.argv or '-br' in sys.argv
    to_run = '-r' in sys.argv or '-b' not in sys.argv
    filename = base_dir + 'main.cpp'
    flag = False
    inputfile = base_dir + 'cmake-build-debug' + dir_char + 'input.txt'
    if '-h' in sys.argv:
        print(blue_col('usage: run.py:\n'
                       '\tbuild or run:\n'
                       '\t\t[ -b ] : build\n'
                       '\t\t[ -r ] : run\n'
                       '\t\t[ -br] : build and run\n'
                       '\t\t(it will run if neither of commands in "build or run")\n'
                       '\t[ -i ] : use input.txt as input\n'
                       '\t[ -f *.cpp]: set build file as *.cpp\n'
                       '\t[ -h ] : help'))
        exit(0)
    if '-f' in sys.argv:
        index = sys.argv.index('-f')
        if index == len(sys.argv) - 1:
            print(red_col('ERROR: No file with -f'))
        filename = sys.argv[index + 1]
        if not os.path.exists(filename):
            print(red_col('ERROR: No such file:%s' % filename))
            exit(-1)
        if not filename.endswith('.cpp') and not filename.endswith('.c'):
            print(red_col("ERROR: %s is not an C/CPP file" % filename))
            exit(-1)
        flag = True
    if '-if' in sys.argv:
        index = sys.argv.index('-if')
        if index == len(sys.argv)-1:
            print(red_col('ERROR: No file with -if'))
        inputfile = sys.argv[index+1]
        if not os.path.exists(inputfile):
            print(red_col('ERROR: No such file:%s' % inputfile))
            exit(-1)
    o_file = base_dir + 'cmake-build-debug' + dir_char + 'ACM'
    if to_build:
        if flag:
            o_file = base_dir + filename.split(dir_char)[-1].split('.')[0]
        os.system('g++ -std=c++11 ' + filename + ' -o ' + o_file)
    if to_run:
        run('-i' in sys.argv or '-if' in sys.argv, o_file)
    if flag:
        os.remove(o_file)
