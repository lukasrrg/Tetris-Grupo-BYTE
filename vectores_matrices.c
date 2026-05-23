#include "vectores_matrices.h"

bool vectorCrear(tVector *vec, size_t tamElem)
{
    if (tamElem < 1)
    {
        vec->datos = NULL;
        vec->ce = 0;
        vec->cap = 0;
        vec->tamElem = 0;
        return false;
    }

    vec->datos = malloc(VECTOR_CAP_INI*tamElem);

    if (!vec->datos)
    {
        vec->ce = 0;
        vec->cap = 0;
        vec->tamElem = 0;
        return false;
    }

    vec->ce = 0;
    vec->cap = VECTOR_CAP_INI;
    vec->tamElem = tamElem;

    return true;
}

void vectorDestruir(tVector *vec)
{
    free(vec->datos);
    vec->datos = NULL;
    vec->ce = 0;
    vec->cap = 0;
    vec->tamElem = 0;
}


void mostrarVector(const int *vec, size_t ce)
{
    printf("Contenido: ");

    const int *i = vec;

    for (i = vec; i - vec < ce; i++)
    {
        printf("%d ", *i);
    }

    printf("\n");
}

void** matrizCrear(size_t filas, size_t columnas, size_t tamElem)
{

    if(!filas || !columnas || !tamElem)
        return NULL;

    void** matriz = malloc(filas * sizeof(void*));

    if(!matriz)
    {
        return NULL;
    }

    void **ultimaFila = matriz + filas - 1;

    for(void **fila = matriz; fila <= ultimaFila; fila++)
    {

        *fila = malloc(columnas * tamElem);

        if(!*fila)
        {
            matrizDestruir(matriz, fila - matriz);
            return NULL;
        }
    }

    return matriz;
}

void matrizDestruir(void** matriz, size_t filas)
{

    if(!matriz)
        return;

    void **ultimaFila = matriz + filas - 1;

    for(void **fila = matriz; fila <= ultimaFila; fila++)
    {
        free(*fila);
        *fila = NULL;
    }

    free(matriz);
    matriz = NULL;
}

void vectorShiftear(void *vector, int posicionesDesplazadas, int ce, size_t tamElem, int sentido)
{
    int i;
    void *p;

    if (sentido == IZQUIERDA)
    {
        p = vector;

        for (i = 0; i < ce - posicionesDesplazadas; i++)
        {
            memcpy(p, p + posicionesDesplazadas*tamElem, tamElem);
            p += tamElem;
        }
    }


    if (sentido == DERECHA)
    {
        p = vector + (ce - 1)*tamElem;

        for (i = 0; i < ce - posicionesDesplazadas; i++)
        {
            memcpy(p, p - posicionesDesplazadas*tamElem, tamElem);
            p -= tamElem;
        }
    }
}
