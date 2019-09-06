#!/usr/bin/env python3
import sys
import difflib
import webbrowser as wb
from run import base_dir


def read_file(filename):
    try:
        with open(filename, 'r') as f:
            return f.readlines()
    except IOError:
        print("ERROR: 没有找到文件:%s或读取文件失败！" % filename)
        sys.exit(1)


def compare_file(file1, file2, out_file):
    file1_content = read_file(file1.strip())
    file2_content = read_file(file2.strip())
    d = difflib.HtmlDiff()
    result = d.make_file(file1_content, file2_content)
    with open(out_file, 'w') as f:
        f.writelines(result)


if __name__ == '__main__':
    path1 = input('first  file path:')
    path2 = input('second file path:')
    compare_file(path1, path2, './res.html')
    wb.open('file://%sres.html' % base_dir)
