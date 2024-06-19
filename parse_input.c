#include "parse_input.h"

#include <errno.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void print_points(Points * p)
{
	printf("# Tabla original:\n");
	printf("{\n    x\t\ty\n\n");

	for(int i = 0; i < p->length; i++)
	{
		printf("    %f\t%f\n", p->x[i], p->y[i]);
	}

	printf("}\n");
}

Points * parse_input(int argc, char ** argv)
{
	char * splitter = "@";

	//Determinar cuántos elementos hay
	int size_x = 0, size_y = 0, splitter_index = -1;
	int reading_state = 0; //0 = leyendo x, 1 = leyendo y
	for(int i = 1; i < argc; i++)
	{
		if(strcmp(argv[i], splitter) == 0)
		{
			reading_state++;
			splitter_index = i;
			continue;
		}

		if(reading_state == 0) size_x++;
		else size_y++;
		
	}

	if(reading_state != 1)
	{
		fprintf(stderr, "[INPUT ERROR] Formato erróneo.\nAsegúrese de usar el formato correctamente:\n\nprograma x1 x2 x3 = y1 y2 y3\n");
		return NULL;
	}

	if(size_x != size_y)
	{
		fprintf(stderr, "[INPUT ERROR] Cantidad distinta de X e Y\n");
		return NULL;
	}

	if(size_x < 2)
	{
		fprintf(stderr, "[INPUT ERROR] Demasiados pocos elementos\n");
		return NULL;
	}

	//printf("Cantidad de x: %i\nCantidad de y; %i\n", size_x, size_y);

	//Crear y cargar las arrays
	double_t * x_array = malloc(sizeof(double_t) * size_x);
	double_t * y_array = malloc(sizeof(double_t) * size_y);

	if(x_array == NULL || y_array == NULL)
	{
		fprintf(stderr, "[ERROR] parse_input: No se pudo alojar memoria para double_t **");
		return NULL;
	}

	//Hacer exactamente lo mismo que hace rato
	reading_state = 0;
	int array_i = 0;
	double_t converted_value = INFINITY;
	for(int i = 1; i < argc; i++)
	{
		if(i == splitter_index)
		{
			reading_state++;
			array_i = 0;
			continue;
		}

		//Convertir de char a double
		errno = 0;
		converted_value = (double_t) strtod(argv[i], NULL);
		if(errno != 0)
		{
			fprintf(stderr, "[ERROR] No se pudo interpretar argumento en la posición %i\n", i);
			return NULL;
		}

		if(reading_state == 0)
		{
			x_array[array_i] = converted_value;
			array_i++;
		}
		else
		{
			y_array[array_i] = converted_value;
			array_i++;
		}
	}

	Points * points = malloc(sizeof(Points));
	if(points == NULL)
	{
		fprintf(stderr, "[ERROR] parse_input: No se pudo alojar memoria para Points\n");
		return NULL;
	}

	points->x = x_array;
	points->y = y_array;
	points->length = size_x;

	print_points(points);

	return points;
}

