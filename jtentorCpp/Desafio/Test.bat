rem Copiar este archivo y los dos .txt a la carpeta donde esta el ejecutable
echo off
echo Verifica 1er ejemplo
type Test01.txt | Desafio.exe

echo Verifica 2do ejemplo
type Test02.txt | Desafio.exe

echo Verifica 1er ejemplo con mayor informaci�n.
type Test01.txt | Desafio.exe -v

echo Verifica 2do ejemplo con mayor informaci�n.
type Test02.txt | Desafio.exe -v

