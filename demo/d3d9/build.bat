@echo off

rem This will use VS2015 for compiler
call "E:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x86

cl /D_CRT_SECURE_NO_DEPRECATE /nologo /W3 /O2 /fp:fast /Gm- /Fedemo.exe main.c user32.lib d3d9.lib /link /incremental:no