#ifndef PARSEINPUT  /* Include guard */
#define PARSEINPUT

#include <math.h>

typedef struct
{
	double_t * x;
	double_t * y;
	int length;
}Points;

Points * parse_input(int argc, char ** argv);

#endif
