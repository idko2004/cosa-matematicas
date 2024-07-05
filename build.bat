@echo on
SET build=build
SET materials=%build%\materials
echo %materials%
mkdir %build%
mkdir %materials%

echo Compiling parse_input
gcc -c parse_input.c -o "%materials%\parse_input.o"

echo Compiling ptrarr
gcc -c ptrarr.c -o "%materials%\ptrarr.o"

echo Compiling cosa_de_las_fracciones
gcc -c cosa_de_las_fracciones.c -o "%materials%\cosa_de_las_fracciones.o"

echo Compiling build_equation
gcc -c build_equation.c -o "%materials%\build_equation.o"

echo Compiling main
gcc  "%materials%\parse_input.o" "%materials%\ptrarr.o" "%materials%\cosa_de_las_fracciones.o" "%materials%\build_equation.o" main.c -o "%build%\cosa_matematicas.exe"

