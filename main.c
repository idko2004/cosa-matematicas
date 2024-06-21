#include "build_equation.h"
#include "ptrarr.h"
#include "parse_input.h"
#include "cosa_de_las_fracciones.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char ** argv)
{
	#ifdef _WIN32
		printf("[INFO] Las tildes se van a ver mal porque Windows es una basura c:\n\n");
	#endif

	Points * input = parse_input(argc, argv);
	if(input == NULL) return 1;

	Ptrarr * cosa_de_las_fracciones = cosa_de_las_fracciones_main_loop(input);
	if(cosa_de_las_fracciones == NULL) return 1;

	int * b_values_length = malloc(sizeof(int));
	double_t * b_values = obtain_b_values(cosa_de_las_fracciones, b_values_length);

	build_equation(input, b_values, b_values_length);

	return 0;
}
