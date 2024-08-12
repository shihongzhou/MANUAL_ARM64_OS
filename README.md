# 一、运行环境搭建

> OS的模拟环境是树莓派4b，一些串口打印使用树莓派4b的寄存器，所以需要指定Machine

## 1、搭建qemu-v9虚拟环境

参考飞书文档:https://w0av2otdlxx.feishu.cn/docx/Uvd8dqpoPoMmYbxwTkwcJPqLnwb?from=from_copylink

## 2、修改Makefile

### 2.1、修改交叉编译器

可以直接指定绝对路径

```makefile
 ARMGNU ?= aarch64-linux-gnu

```

### 2.2、修改qmeu路径（如果没有添加到环境变量）

```
 QEMU_PWD ?= ../qemu-9.1.0-rc1/build/
```

# 二、编译运行

## 1、编译OS

```bash
make all
```

## 2、使用qemu模拟运行

```bash
make run
```

