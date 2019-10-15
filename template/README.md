# 模板库

- 模板库通过命令: `refresh`管理

    |命令|效果|
    |:---|:---|
    |`refresh`|将`compile_filename`文件恢复为`template/main`|
    |`refresh -c name`|拷贝`compile_filename`文件, 并创建`name.md`模板|
    |`refresh name`|将`name`模板导入到`compile_filename`文件相应位置|

- 注意事项:

  1. 添加模板要确保已经删除代买内的宏定义, 头文件和main函数
  2. 导入模板: 在要导入模板的位置先写上`/// __TEMPLATE__`, 再运行导入命令. (要确保只有一个模板导入标记)
