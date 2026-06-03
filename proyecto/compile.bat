@echo off
echo Compilando codigo en ensamblador.
nasm -f win64 funciones.asm -o funciones.obj

echo Compilando codigo en C.
gcc main.c funciones.obj -o BitQuest.exe

echo Compilacion terminada.
BitQuest.exe
pause