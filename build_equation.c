#include "build_equation.h"

#include "parse_input.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SIZE_DOUBLE_TO_CHAR 10 //El número de chars que ocupa un double cuando se convierte a string (en realidad son menos de 10 pero por si acaso)

char * x_template(double_t x_value)
{
	char * template = "(x -%f)";

	int buffer_max_estimated_size = strlen(template) + SIZE_DOUBLE_TO_CHAR;
	char * str = malloc(sizeof(char) * buffer_max_estimated_size);

	int result = snprintf(str, buffer_max_estimated_size, template, x_value);

	if(result < 0 || result > buffer_max_estimated_size)
	{
		fprintf(stderr, "[ERROR] x_template: buffer too small\n");
		return NULL;
	}

	return str;
}

int build_equation(Points * points, double_t * b_values, int * b_values_length)
{
	printf("# Ecuación:\n");

	char * result_string = malloc(sizeof(char) * ((*b_values_length) * (*b_values_length)) + (*b_values_length + 1) * SIZE_DOUBLE_TO_CHAR * 8);
	/*
		sizeof(char) = el tamaño que ocupa un char en memoria
		((*b_values_length) * (*b_values_length)) = b_values_length al cuadrado, porque se va a usar x_template de forma exponencial y así aseguramos que hay suficiente espacio
		(*b_values_length + 1) = para tener en cuenta el espacio necesario para el signo y los espacios que rodean al signo
		SIZE_DOUBLE_TO_CHAR = la cantidad de chars que usa un double al convertirse a string
		8 = strlen(template)
	*/

//fprintf(stderr, "[DEBUG] pointer result_string: %p\n", result_string);

	snprintf(result_string, sizeof(char) * SIZE_DOUBLE_TO_CHAR, "%f", points->y[0]); //Copiar b0 a result_string


//fprintf(stderr, "[DEBUG] result_string contents: %s\n", result_string);

//fprintf(stderr, "[DEBUG] str_write_position contents: %p\n", str_write_position);
//fprintf(stderr, "[DEBUG] result_string length: %li\n", strlen(result_string));
	
	//printf("%s\n%i\n", x_template(0.56), *b_values_length);

	for(int i = 1; i <= *b_values_length; i++)
	{
		//Añadir el signo
		if(b_values[i - 1] > 0) strcpy(result_string + strlen(result_string), " +"); // Si es positivo
		else strcpy(result_string + strlen(result_string), " "); //Si es negavito solo un espacio, ya que el propio double lleva el signo
		
		//Añadir b
		snprintf(result_string + strlen(result_string), SIZE_DOUBLE_TO_CHAR, "%f", b_values[i - 1]);

		//Añadir las x
		for(int j = 0; j < i; j++)
		{
			strcpy(result_string + strlen(result_string), x_template(points->x[j]));
		}

	}

	printf("%s", result_string);
	return 0;
}
