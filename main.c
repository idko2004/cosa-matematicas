#include "ptrarr.h"
#include "parse_input.h"
#include "diferencias_divididas.h"

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char ** argv)
{
	Points * input = parse_input(argc, argv);
	if(input == NULL) return 1;

	Ptrarr * diferencias_divididas_result = diferencias_divididas_main_loop(input);
}
