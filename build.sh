#!/bin/bash
BUILD="build"
MATERIALS="${BUILD}/materials"

YELLOW="\033[1;33m"
GREEN="\033[1;32m"
RED="\033[1;31m"
NOCOLOR="\033[0m"

mkdir -p $MATERIALS

echo -e "${YELLOW}Compiling parse_input${NOCOLOR}"
gcc -c parse_input.c -o "${MATERIALS}/parse_input.o"

echo -e "${YELLOW}Compiling ptrarr${NOCOLOR}"
gcc -c ptrarr.c -o "${MATERIALS}/ptrarr.o"

echo -e "${YELLOW}Compiling diferencias_divididas${NOCOLOR}"
gcc -c diferencias_divididas.c -o "${MATERIALS}/diferencias_divididas.o"

echo -e "${YELLOW}Compiling main${NOCOLOR}"
gcc "${MATERIALS}/parse_input.o" "${MATERIALS}/ptrarr.o" "${MATERIALS}/diferencias_divididas.o" main.c -o "${BUILD}/program"

if [ $? -eq 0 ]; then
	echo -e "${GREEN}Done!${NOCOLOR}"
	echo "The program should be in ${BUILD}/program"
else
	echo -e "${RED}Failed to compile :c${NOCOLOR}"
fi
