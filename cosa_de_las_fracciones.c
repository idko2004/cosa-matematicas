#include "cosa_de_las_fracciones.h"

#include "ptrarr.h"
#include "parse_input.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>


FractionCalculation * new_FractionCalculation(double_t x0, double_t x1, double_t y0, double_t y1)
{
	FractionCalculation * f = malloc(sizeof(FractionCalculation));
	if(f == NULL)
	{
		fprintf(stderr, "[ERROR] new_FractionCalculation: No se pudo alojar memoria para un nuevo FractionCalculation\n");
		return NULL;
	}

	f->x0 = x0;
	f->x1 = x1;
	f->y0 = y0;
	f->y1 = y1;
	f->result = INFINITY;
	return f;
}

void print_FractionCalculation(FractionCalculation * f)
{
	printf("{\n    x\t\ty\n\n");
	printf("    %f\t%f\n", f->x0, f->y0);
	printf("    %f\t%f\n", f->x1, f->y1);
	printf("\n    resultado = %f\n}\n", f->result);
}

double_t calculateFraction(FractionCalculation * input)
{
	if(input == NULL)
	{
		fprintf(stderr, "[ERROR] calculateFraction: input is NULL\n");
		return INFINITY;
	}

	input->result = (input->y1 - input->y0)/(input->x1 - input->x0);

	return input->result;
}

Ptrarr * cosa_de_las_fracciones_main_loop(Points * points)
{
	printf("\n# Diferencias divididas:\n\n");

	//La "tabla"
	double_t * x = points->x;
	double_t * y = points->y;
	int arrLength = points->length;

	Ptrarr * iterations = ptrarr_new(arrLength - 1); //Un array para guardar todas las "columnas"
	Ptrarr * first_calc_iteration = ptrarr_new(arrLength - 1); //Un array para guardar todos los cálculos de esta "columna"

	if(iterations == NULL || first_calc_iteration == NULL)
	{
		fprintf(stderr, "[ERROR] diferencias_divididas_main_loop: iterations o first_calc_iteration es NULL\n");
		return NULL;
	}

	if(ptrarr_push(iterations, first_calc_iteration) != 0)
	{
		fprintf(stderr, "[ERROR] diferencias_divididas_main_loop: No se pudo hacer ptrarr_push\n");
		return NULL;
	}

	printf("## Columna de inicio:\n");

	//A partir de la "tabla", crear la primera "columna"
	for(int i = 0; i < arrLength - 1; i++)
	{
		printf("### Operación nro %i:\n", i + 1);

		FractionCalculation * calc = new_FractionCalculation(x[i], x[i+1], y[i], y[i+1]);
		if(calc == NULL)
		{
			fprintf(stderr, "[ERROR] diferencias_divididas_main_loop: No se pudo crear un nuevo FractionCalculation\n");
			return NULL;
		}

		if(ptrarr_push(first_calc_iteration, calc) != 0)
		{
			fprintf(stderr, "[ERROR] diferencias_divididas_main_loop: No se pudo agregar calc en first_calc_iteration\n");
			return NULL;
		}

		calculateFraction(calc);
		print_FractionCalculation(calc);
	}

	Ptrarr * current_iteration = first_calc_iteration;

	//Calcular cada "columna"
	//Se calcula la primera columna y se crea la columna siguiente, luego se calcula sobre esta y se crea la columna siguiente...
	for(int iterationCounter = 0; iterationCounter < arrLength - 2; iterationCounter++)
	{
		printf("## Columna nro %i:\n", iterationCounter + 2);

		Ptrarr * next_iteration = ptrarr_new(current_iteration->length - 1);
		if(next_iteration == NULL)
		{
			fprintf(stderr, "[ERROR]: diferencias_divididas_main_loop: No se pudo crear un nuevo ptrarr\n");
			return NULL;
		}
		
		if(ptrarr_push(iterations, next_iteration) != 0)
		{
			fprintf(stderr, "[ERROR] diferencias_divididas_main_loop: No se pudo añadir el ptrarr recién creado al otro ptrarr\n");
			return NULL;
		}

		//Calcular cada operación en esta "columna"
		for(int i = 0; i < current_iteration->length - 1; i++)
		{
			printf("### Operación nro %i:\n", i + 1);

			FractionCalculation * calc0 = (FractionCalculation *) ptrarr_get(current_iteration, i);
			FractionCalculation * calc1 = (FractionCalculation *) ptrarr_get(current_iteration, i + 1);

			if(calc0 == NULL || calc1 == NULL)
			{
				fprintf(stderr, "[ERROR] diferencias_divididas_main_loop: No se pudieron obtener los FractionCalculation necesarios para la operación, current_iteration[%i] es NULL (%d), current_iteration[%i] es NULL (%d)\n", i, calc0 == NULL, i + 1, calc1 == NULL);
				return NULL;
			}

			double_t y0 = calc0->result;
			double_t y1 = calc1->result;
			double_t x0 = calc0->x0;
			double_t x1 = calc1->x1;

			FractionCalculation * new_calc = new_FractionCalculation(x0, x1, y0, y1);
			if(new_calc == NULL)
			{
				fprintf(stderr, "[ERROR] diferencias_divididas_main_loop: No se pudo crear new_calc\n");
				return NULL;
			}

			calculateFraction(new_calc);

			if(ptrarr_push(next_iteration, new_calc) != 0)
			{
				fprintf(stderr, "[ERROR] diferencias_divididas_main_loop: No se pudo agregar new_calc a next_iteration\n");
				return NULL;
			}

			print_FractionCalculation(new_calc);
		}

		if(ptrarr_push(iterations, next_iteration) != 0)
		{
			fprintf(stderr, "[ERROR] diferencias_divididas_main_loop: No se pudo agregar la nueva iteración al array de iteraciones\n");
			return NULL;
		}

		current_iteration = next_iteration;
	}

	return iterations;
}
