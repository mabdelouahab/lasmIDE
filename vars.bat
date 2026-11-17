setx PKG_CONFIG_PATH C:\msys64\mingw64\lib\pkgconfig /M
setx PATH C:\msys64\mingw64\bin;C:\msys64\usr\bin;%PATH%
setx XDG_DATA_HOME %LOCALAPPDATA% /M
setx XDG_DATA_DIRS C:\msys64\mingw64\share;%ProgramData% /M
setx XDG_CONFIG_HOME  %LOCALAPPDATA% /M
setx XDG_CONFIG_DIRS C:\msys64\mingw64\share;%ProgramData%;%APPDATA% /M
SETx XDG_STATE_HOME %LOCALAPPDATA% /M
SETx XDG_CACHE_HOME %LOCALAPPDATA%\cache /M
SETx XDG_RUNTIME_DIR %LOCALAPPDATA% /M
pause
