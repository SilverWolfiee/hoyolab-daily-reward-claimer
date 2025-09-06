@echo off
gcc accountmanager.cpp -o accountmanager.exe
if %ERRORLEVEL% neq 0 exit /b
accountmanager.exe
