# Simple App for learning things
```bash
git submodules init
git submodules update
mkdir build
cd build
cmake .. -G"Visual Studio 14 2015 Win64"
```

Currently only set-up for Windows.  Requires Visual Studio 2015 and CMake >= 3.4.0
Linux/OSX build configurations will come at some later date.

Debug and Release builds all go into the same directory.  Lots of things don't compile.  Many things leak memory.  Lots of dangling pointers.  Don't use this as a reference for anything.

I'm 90% sure I don't have any idea what I'm doing.