# ACM Template
- 在 `./template/` 寻找算法模板.
- 运行脚本:

  - **要使用这个脚本，你应该有`g++`环境和`python3`环境**
  - 编译且运行: `./run.py -br`
  - 编译不运行: `./run.py -b`
  - 只 是 运 行 : `./run.py -r` 或 `./run.py`
  - ( 你可以编辑 `./cmake-build-debug/input.txt` 来设置输入)
  - ( 你可以运行 `./run.py [-br] > output.txt` 使程序输出到 `./output.txt`)
  
- 刷新脚本:

  - 运行 `./refresh.py` 来初始化 `main.cpp` 为存储在 `./template/main` 文件中的内容。

- 对拍器

  - 运行: `python3 TextCmp.py` 来对两个文本进行对拍。结果存储在当前目录下的`./res.html`。
  - 如果脚本未能自动打开`./res.html`, 你可以用浏览器打开它。
 