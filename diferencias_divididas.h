#ifndef DIFERENCIASDIVIDIDAS  /* Include guard */
#define DIFERENCIASDIVIDIDAS
#include "ptrarr.h"
#include <math.h>

typedef struct
{
	double_t x0, x1, y0, y1, result;
}FractionCalculation;

Ptrarr * diferencias_divididas_main_loop();

#endif
