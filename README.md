# ACM Template
[![](https://img.shields.io/badge/Author-RhythmLian-blue)]()
[![](https://img.shields.io/badge/License-MIT-yellow)]()

## 关于项目
- 在 `./template/` 寻找算法模板.

- 环境要求:
  - [x] `gcc / g++`
    
    - Mac OS: 
        
        - 安装homebrew: 
            ```shell script
            $ xcode-select --install
            $ /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
            ```  
        - 安装gcc: `brew install gcc`
    - Windows:
    
      | MinGw | [下载地址](https://osdn.net/projects/mingw/downloads/68260/mingw-get-setup.exe/) |
      | :-----: | :-----: |
      | CygWin | [下载地址](https://cygwin.com/setup-x86_64.exe) |
    - Linux: 
    
      | ubuntu | `sudo apt install gcc` |
      | :-----: | :-----: |
      | CentOS | `sudo yum install gcc` |  
  - [x] `python3`
    
    - Windows:[下载地址](https://www.python.org/downloads/)
    - MacOS: 
    
      | 安装包 | [下载地址](https://www.python.org/ftp/python/3.7.4/python-3.7.4-macosx10.9.pkg) |
      | :-----: | :-----: |
      | 命令 | `brew install python3` |
    - Linux: 
      ```shell script
      wget https://www.python.org/ftp/python/3.7.4/Python-3.7.4.tgz
      tar -zxvf Python-3.7.4.tgz
      cd Python-3.7.4
      ./configure --prefix=/usr/local/python3
      make && make install
      ```
## 关于内置脚本

  - 使用Qpro，自动为你的CLion Project配置下面的脚本:
  
    | 安装 | `pip3 install Qpro` |
    | :-----: | :-----: |
    | 使用方法 | [Qpro使用方法](https://pypi.org/project/Qpro/) |
