#ifndef PTRARR_H  /* Include guard */
#define PTRARR_H

typedef struct
{
	int spaces_reserved; //La cantidad de punteros que puede guardar str_arr, se cuenta de la misma forma que length
	int length; //La cantidad de punteros que str_arr tiene actualmente
	char ** ptr_arr; //La array donde se guardan los punteros hacia los strings
} Ptrarr;

Ptrarr * ptrarr_new(int capacity); //Inicializa Strarr, debe ejecutarse justo después de crear Strarr, capacity debe indicar la cantidad de espacios a reservar, se cuenta de la misma forma que length

int ptrarr_expand(Ptrarr * ptrarr, int new_capacity); //Expande el array (str_arr) a la capacidad indicada, la capacidad indicada será el nuevo spaces_reserved

int ptrarr_push(Ptrarr * ptrarr, void * p); //Añade un string al final del array

void * ptrarr_get(Ptrarr * ptrarr, int index); //Obtiene el string guardado en el index especificado del array

int ptrarr_set(Ptrarr * ptrarr, int index, void * p); //Reemplaza un string que ha sido guardado en el array anteriormente en el index indicado

int ptrarr_destroy_everything(Ptrarr * ptrarr); //Libera la memoria del struct y de todos los strings que contenía

void ptrarr_print_pointers(Ptrarr * ptrarr); //Imprimir punteros.

#endif
