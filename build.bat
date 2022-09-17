@echo off
cls
g++ -std=c++11 .\Project\*.cpp -o out
echo ----- ----- -----
echo   Build  Output
echo ----- ----- -----
.\out.exe
rm .\out.exe
