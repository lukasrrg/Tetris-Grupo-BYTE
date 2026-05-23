#ifndef VECTORES_MATRICES_H_INCLUDED
#define VECTORES_MATRICES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define VECTOR_CAP_INI 10

#define IZQUIERDA -1
#define DERECHA 1

typedef struct
{
    size_t cap;
    size_t ce;
    size_t tamElem;
    void *datos;
} tVector;

typedef struct
{
    size_t filas;
    size_t columnas;
    size_t tamElem;
    void **datos;
} tMatriz;

void *crearVector(size_t);
void vectorDestruir(tVector *vec);
void mostrarVector(const int *vec, size_t ce);
void **matrizCrear(size_t filas, size_t columnas, size_t tamElem);
void matrizDestruir(void** matriz, size_t filas);
void vectorShiftear(void *vect, int posicionesDesplazadas, int ce, size_t tamElem, int sentido);

#endif // VECTORES_MATRICES_H_INCLUDED
