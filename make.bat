@echo off
rc inputbox.rc
cl /Zi /nologo  inputbox.cpp /link /dll /out:inputbox.dll user32.lib inputbox.res /machine:x86
