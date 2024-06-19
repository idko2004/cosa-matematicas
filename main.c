#include "ptrarr.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	double_t x0, x1, y0, y1, result;
}FractionCalculation;

FractionCalculation * new_FractionCalculation(double_t x0, double_t x1, double_t y0, double_t y1)
{
	FractionCalculation * f = malloc(sizeof(FractionCalculation));
	f->x0 = x0;
	f->x1 = x1;
	f->y0 = y0;
	f->y1 = y1;
	f->result = INFINITY;
	return f;
}

void print_FractionCalculation(FractionCalculation * f)
{
	printf("x\t\ty\n");
	printf("%f\t%f\n", f->x0, f->y0);
	printf("%f\t%f\n", f->x1, f->y1);
	printf("result = %f\n", f->result);
	printf("pointer = %p\n", f);
	printf("\n");
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

int main(int argc, char ** argv)
{
	double_t x[] = {1, 2, 3, 5};
	double_t y[] = {4, 3.5, 4, 5.6};
	int arrLength = 4;

	Ptrarr * iterations = ptrarr_new(arrLength - 1);
	Ptrarr * first_calc_iteration = ptrarr_new(arrLength - 1);
	ptrarr_push(iterations, first_calc_iteration);

	for(int i = 0; i < arrLength - 1; i++)
	{
		printf("%i\n", i);

		FractionCalculation * calc = new_FractionCalculation(x[i], x[i+1], y[i], y[i+1]);
		ptrarr_push(first_calc_iteration, calc);
		calculateFraction(calc);
		print_FractionCalculation(calc);
	}

	Ptrarr * current_iteration = first_calc_iteration;

	for(int iterationCounter = 0; iterationCounter < arrLength - 2; iterationCounter++)
	{
		//Ptrarr * current_iteration = ptrarr_get(iterations, iterationCounter);

		printf("\n\n--------\nbig iteration: %i\n", iterationCounter);

		Ptrarr * next_iteration = ptrarr_new(current_iteration->length - 1);
		ptrarr_push(iterations, next_iteration);
		for(int i = 0; i < current_iteration->length - 1; i++)
		{
			printf("small iteration: %i\n", i);

			FractionCalculation * calc0 = (FractionCalculation *) ptrarr_get(current_iteration, i);
			FractionCalculation * calc1 = (FractionCalculation *) ptrarr_get(current_iteration, i + 1);

			double_t y0 = calc0->result;
			double_t y1 = calc1->result;
			double_t x0 = calc0->x0;
			double_t x1 = calc1->x1;

			FractionCalculation * new_calc = new_FractionCalculation(x0, x1, y0, y1);
			calculateFraction(new_calc);
			ptrarr_push(next_iteration, new_calc);
			print_FractionCalculation(new_calc);
		}

		ptrarr_push(iterations, next_iteration);
		current_iteration = next_iteration;
	}

/*
	//Resolver una iteración
	for(int i = 0; i < arrLength - 1; i++)
	{
		FractionCalculation * calc = new_FractionCalculation(x[i], x[i+1], y[i], y[i+1]);
		ptrarr_push(first_calc_iteration, calc);
		calculateFraction(calc);
		printf("%i\n", i);
		print_FractionCalculation(calc);
	}

	printf("\n\n--------\n\n");
	
	//Armar la siguiente iteración
	Ptrarr * second_calc_iteration = ptrarr_new(first_calc_iteration->length - 1);
	ptrarr_push(iterations, second_calc_iteration);
	for(int i = 0; i < first_calc_iteration->length - 1; i++)
	{
		printf("%i\n", i);

		FractionCalculation * calc0 = (FractionCalculation *) ptrarr_get(first_calc_iteration, i);
		FractionCalculation * calc1 = (FractionCalculation *) ptrarr_get(first_calc_iteration, i + 1);
		
		double_t y0 = calc0->result;
		double_t y1 = calc1->result;
		double_t x0 = calc0->x0;
		double_t x1 = calc1->x1;

		FractionCalculation * new_calc = new_FractionCalculation(x0, x1, y0, y1);
		ptrarr_push(second_calc_iteration, new_calc);
		print_FractionCalculation(new_calc);
	}
*/
	return 0;
}
