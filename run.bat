@echo off
if "%one%"=="-br" || "%one%"=="-b" (
    g++ -std=c++11 %~dp0%\main.cpp -o %~dp0%\cmake-build-debug\ACM
)
if "%one%"!="-b" (
    %~dp0%\cmake-build-debug\ACM < %~dp0%\cmake-build-debug\input.txt
)