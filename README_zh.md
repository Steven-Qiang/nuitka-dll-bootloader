# Nuitka DLL Bootloader

[English](README.md)

## 概述

Nuitka DLL Bootloader是一个旨在帮助执行由 [nuitka-extractor](https://github.com/extremecoders-re/nuitka-extractor) 解包的 main.dll 文件的工具。

## 功能

- 加载并执行由 [nuitka-extractor](https://github.com/extremecoders-re/nuitka-extractor) 解包的 main.dll 文件
- 允许将命令行参数传递给原始可执行文件

## 使用方法

使用 Nuitka DLL Bootloader的基本语法是：
boot.exe real_program.exe [参数...]
- `boot.exe`: 本项目提供的启动器
- `real_program.exe`: 解包前的原始可执行文件（部分程序存在验证自身的情况）
- `[参数...]`: 可选的命令行参数，将传递给实际程序

## 示例

要运行名为 `my_app.exe` 的程序并传递参数 `--config config.ini`：
boot.exe my_app.exe --config config.ini
## 安装

1. 从 GitHub 仓库下载 Nuitka DLL Bootloader 的最新版本
2. 解压发布存档的内容
3. 将 `boot.exe` 放在与你解包的 main.dll 文件相同的目录中
4. 确保原始可执行文件 (`real_program.exe`) 也在同一目录或指定路径中可用

## 从源代码构建

如果你希望从源代码构建 Nuitka DLL Bootloader，请按照以下步骤操作：

1. 克隆仓库：
   ```
   git clone https://github.com/Steven-Qiang/nuitka-dll-bootloader.git
   cd nuitka-dll-bootloader
   ```
3. 构建项目：
   ```
   gcc .\boot.c -o boot.exe -municode
   ```

## 许可证

本项目根据 [MIT 许可证](LICENSE) 授权。

## 支持

如有任何问题或疑问，请在 GitHub 仓库上创建一个 issue。
