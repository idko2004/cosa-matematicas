#include "ptrarr.h"
#include "parse_input.h"
#include "cosa_de_las_fracciones.h"

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char ** argv)
{
	Points * input = parse_input(argc, argv);
	if(input == NULL) return 1;

	Ptrarr * cosa_de_las_fracciones = cosa_de_las_fracciones_main_loop(input);
	if(cosa_de_las_fracciones == NULL) return 1;

	return 0;
}
