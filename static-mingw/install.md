# Mingw version by yncat readme
The original version had some minor problems using with mingw gcc and static linking. Here is the quick fix.
The included resource file didn't compile on windres.exe in MSYS2 (most likely missing of some constants), so I precompiled it by `rc inputbox.rc` on Visual Studio.
For those who want to use directly, install inputbox-static.h and libinputbox.a and good to go.
To compile:
windres inputbox.res inputbox-res.o
g++ -c inputbox-static.cpp
ar rcs libinputbox.a inputbox-static.o inputbox-res.o