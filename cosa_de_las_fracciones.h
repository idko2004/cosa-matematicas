#ifndef COSAFRACCIONES  /* Include guard */
#define COSAFRACCIONES
#include "ptrarr.h"
#include "parse_input.h"
#include <math.h>

typedef struct
{
	double_t x0, x1, y0, y1, result;
}FractionCalculation;

Ptrarr * cosa_de_las_fracciones_main_loop(Points * points);

#endif
