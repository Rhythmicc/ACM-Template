# 模板库

- 模板库通过命令: `tmpm`管理

  | 命令 | 效果 |
  |:---|:---|
  | `tmpm` | 刷新项目中的默认源文件为`template/main` |
  | `tmpm -c template algorithm` |拷贝指定位置, 创建模板集并写入算法|
  | `tmpm -a template algorithm` |拷贝指定位置, 向模板集追加算法|
  | `tmpm name`| 在`/// __TEMPLATE__`处插入`name`模板集内的模板 |

- 注意事项:

  1. 创建模板: 在模板的起始位置和终止位置分别写入`/// __START__` 和 `/// __END__`, 再运行添加命令
  2. 导入模板: 在要导入模板的位置先写上`/// __TEMPLATE__`, 再运行导入命令. (要确保只有一个模板导入标记)

## 关于环境

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