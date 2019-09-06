# ACM Template
- 在 `./template/` 寻找算法模板.
## 运行脚本:

  - 环境要求:
      - [x] `g++`
      - [x] `python3`

  - 编译或运行
  
      - [ -b ] : 编译
      - [ -r ] : 运行
      - [ -br] : 编译且运行
      - ( 如果上述三个命令都不存在，则默认运行当前编译好的程序 )
      - [ -f `*.c/*.cpp`] : 设置目标源文件

  - 输入输出:
      
      - 运行 `./run.py [...] -i` 使程序使用`./cmake-build-debug/input.txt`作为默认输入
      - 你可以编辑 `./cmake-build-debug/input.txt` 来设置输入
      - 运行 `./run.py [...] > output.txt` 使程序输出到 `./output.txt`
      - [ -if `*` ] : 设置输入文件/缺省则使用默认输入
      
  - 推荐的命令示例:
      - `./run.py -i` : 使用默认输入文件并运行。
      - `./run.py`: 运行。
      - `./run.py -i -br` or `./run.py -br -i`: 编译且使用输入文件运行。
## 刷新脚本:

  - 运行 `./refresh.py` 来初始化 `main.cpp` 为存储在 `./template/main` 文件中的内容。

## 对拍器

  - 环境要求:
    - [x] `pip3 install difflib`
  - 运行: `python3 TextCmp.py` 来对两个文本进行对拍。结果存储在当前目录下的`./res.html`。
  - 如果脚本未能自动打开`./res.html`, 你可以用浏览器打开它。
  - ![GUI](./img/1.png)
 