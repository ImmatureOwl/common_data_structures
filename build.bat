@echo off

if exist "bin" (
    RD /S /Q "bin"
)

MD "bin"

clang -o bin\list-test.exe -Iinclude test\main.c src\linked_list.c