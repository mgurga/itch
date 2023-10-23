# Itch
Itch is a robust player for Scratch 3.0 projects (similar to Adobe Flash Player) written in modern C++.

![itch with debug window running monitortest.sb3](https://raw.githubusercontent.com/mgurga/itch/master/docs/itchanddebug.png)

## Usage
The program includes a minimal command line frontend to open .sb3 files and download projects from Scratch servers.
The current command line API looks like this, but is subject to constant change:
```
> itch.exe --help
itch - Scratch 3 project player
Usage: itch.exe [OPTIONS] [.sb3/url/folder]

Positionals:
  .sb3/url/folder TEXT [temp/]
                              .sb3 file path or scratch.mit.edu URL
Options:
  -h,--help                   Print this help message and exit
  -l,--headless               run itch without graphics
  -d,--debugwindow            run with debug window open
```

## How to Build
Itch is well supported on Windows and Linux and uses the CMake build system.
The CMakeLists.txt fetches all libraries when configuring, so no need to hunt for dependencies.

Run the following commands to checkout and build Itch yourself:
```
git clone https://github.com/mgurga/itch
cd itch
mkdir build
cd build
cmake ..
cmake --build .
```
