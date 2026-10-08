@echo off
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" >nul
if errorlevel 1 exit /b 1
if not exist obj mkdir obj
cl /nologo /W0 /O1 /MT /I libuv-v1.53.0\include /I libuv-v1.53.0\src /DWIN32_LEAN_AND_MEAN /D_WIN32_WINNT=0x0A00 /D_CRT_SECURE_NO_WARNINGS /D_CRT_NONSTDC_NO_DEPRECATE /Foobj\ /Fewatch.exe watch.c libuv-v1.53.0\src\*.c libuv-v1.53.0\src\win\*.c /link advapi32.lib iphlpapi.lib psapi.lib shell32.lib user32.lib userenv.lib ws2_32.lib dbghelp.lib ole32.lib synchronization.lib
