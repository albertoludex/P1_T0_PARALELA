#ifndef _lib_H_
#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include <math.h>
#include<time.h>
//VARIABLES GLOBALES


//FUNCONES
void options();
void ejec_info();
void Error();
unsigned char** matriz_creacion();
int compara_argumentos();
void matriz_load();
unsigned char media();
void media_calculate();
void sobel_calculate();
unsigned char sobel();
void mediana_calculate();
void img_create_raw();
unsigned char mediana();
int comp_ficher0();
void print_results();
#endif