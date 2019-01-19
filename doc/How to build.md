# How to build

## Prepare a build environnement under Windows

### CMake

Download the CMake binary distribution from https://cmake.org/download/
and unzip it into a local folder (ex: `C:\TOOLS\cmake-3.13.3-win64-x64`).

### MinGW64

Download the MINGW64 tool chain with the desired version of gcc from
https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds
(ex: MinGW-W64 GCC-7.3.0 / x86_64-posix-seh) and unzip the archive into
a local folder (ex: `C:\TOOLS\MINGW64-7.3.0`).

Create a Conan profile for this toolchain :

```cmd
conan profile new mingw64-7.3.0
```

And edit it from `%USERPROFILE%/.conan/profiles/mingw64-7.3.0`:

```ini
[settings]
os=Windows
os_build=Windows
arch=x86_64
arch_build=x86_64
compiler=gcc
compiler.version=7.3
compiler.libcxx=libstdc++11
build_type=Release
[options]
[build_requires]
[env]
PATH=[C:/TOOLS/MINGW64-7.3.0/bin]
```

### Visual Studio Code

Install Visual Studio Code from https://code.visualstudio.com/#alt-downloads (user
installer recommended).

From VS Code install the following plugins:

* C/C++ (`ms-vscode.cpptools`)
* CMake (`twxs.cmake`)
* CMake Tools (`vector-of-bool.cmake-tools`)
* GitLens - Git supercharged (`eamodio.gitlens`)

And configure your building environnement into VS Code User Settings:

```json
    "cmake.cmakePath": "C:\\TOOLS\\cmake-3.13.3-win64-x64\\bin\\cmake",
    "cmake.mingwSearchDirs": [
        "C:\\TOOLS\\MINGW64-6.4.0",
        "C:\\TOOLS\\MINGW64-7.3.0",
        "C:\\TOOLS\\MINGW64-8.1.0"
    ]
```

Then launch `CMake: Scan for Kits` from the _Command Palette_ (`ctrl + shift + p`)

## Get required packages using conan

Create a folder for the build (`build` sub folder from the project
folder for easy integration with the _CMake Tools_ VS Code extension).

Move to the build folder and launch:
```cmd
conan install .. --profile mingw64-7.3.0 --build missing
```

## Build manually using CMake

Move to the build folder and launch:

```cmd
# Prepare build using CMake
set PATH=C:\TOOLS\MINGW64-7.3.0\bin
cmake -G "MinGW Makefiles" ..

# Build using CMake
cmake --build .
```

## Tips and tricks

### Build boost manually

Download boost sources from the web site http://boost.org

```bash
sudo apt-get install icu-devtools
./bootstrap.sh
./b2 --prefix=/home/xca/TOOLS/boost_1_69_0 --build-dir=/home/xca/DEV/boost_1_69_0_build --with-date_time --with-filesystem --with-program_options --with-regex --with-system --with-thread
```

