@echo off

rem This will use VS2017 for compiler
call "E:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x86

cl /nologo /W3 /D_CRT_SECURE_NO_DEPRECATE /O2 /fp:fast /Gm- /Fedemo.exe main.c user32.lib gdi32.lib /link /incremental:no
