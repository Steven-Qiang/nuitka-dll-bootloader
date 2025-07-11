# Nuitka DLL Bootloader

[中文](README_zh.md)

## Overview

Nuitka DLL Bootloader is a utility designed to facilitate the execution of main.dll files extracted by [nuitka-extractor](https://github.com/extremecoders-re/nuitka-extractor).

## Features

- Loads and executes main.dll files extracted by [nuitka-extractor](https://github.com/extremecoders-re/nuitka-extractor)
- Allows passing command-line arguments to the original executable

## Usage

The basic syntax for using Nuitka DLL Bootloader is:
boot.exe real_program.exe [arguments...]
- `boot.exe`: The launcher provided by this project
- `real_program.exe`: The original executable file before extraction (Some programs have the issue of verifying themselves)
- `[arguments...]`: Optional command-line arguments that will be passed to the real program

## Example

To run a program named `my_app.exe` with the argument `--config config.ini`:
boot.exe my_app.exe --config config.ini
## Installation

1. Download the latest release of Nuitka DLL Bootloader from the GitHub repository
2. Extract the contents of the release archive
3. Place `boot.exe` in the same directory as your extracted main.dll file
4. Ensure the original executable (`real_program.exe`) is also available in the same directory or a specified path

## Building from Source

If you wish to build Nuitka DLL Bootloader from source, follow these steps:

1. Clone the repository:
   ```
   git clone https://github.com/Steven-Qiang/nuitka-dll-bootloader.git
   cd nuitka-dll-bootloader
   ```

2. Build the project:
   ```
   gcc .\boot.c -o boot.exe -municode
   ```

## License

This project is licensed under the [MIT License](LICENSE).

## Support

For any issues or questions, please open an issue on the GitHub repository.
