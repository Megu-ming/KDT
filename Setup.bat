@echo off
echo Start Setup.bat
REM REM은 주석을, echo.은 enter를 의미한다.
echo.
echo [vcpkg task]
call .\vcpkg\bootstrap-vcpkg.bat
.\vcpkg\vcpkg install rapidjson:x64-windows
.\vcpkg\vcpkg integrate install

echo.
echo [done]
pause