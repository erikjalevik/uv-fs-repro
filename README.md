# Repro of libuv watch bug

`uv_fs_event_start` produces an error on Windows when used with certain SMB shares. To reproduce:

1. Clone libuv 1.53.0:
   `git clone --branch v1.53.0 https://github.com/libuv/libuv.git libuv-v1.53.0`
2. Make sure your C: drive has a name longer than 3 characters. If not, give it one using PowerShell:
   `Set-Volume -DriveLetter C -NewFileSystemLabel "repro"`
3. Run `build.bat` (Expects Visual Studio 2022 Community; adjust the
   `vcvars64.bat` path inside otherwise.)
4. Run `watch.exe \\localhost\C$\Users`

This will output:

```
ERROR  \\localhost\C$\Users: UNKNOWN (-4094) unknown error
```

Running it on a local path works. `watch.exe C:\Users` prints `OK`.

It seems to be happening for any SMB share with a name longer than 3 chars. Tested with local drives accessed via UNC (as above) and network shares on a Synology NAS.

Worked in libuv 1.51.0 and below.
