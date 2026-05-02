#include "tGrilla.h"

bool grillaCrear(tGrilla *p)
{
    tMino *mino;

    p->vecMinos = malloc(ANCHO_GRILLA*ALTO_GRILLA*sizeof(tMino)); //Pido memoria para toda la matriz grilla
    if (p->vecMinos == NULL)
    {
        return false;
    }

    mino = p->vecMinos;

    int i, j;

    for(i = 0; i < ANCHO_GRILLA; i++) //Setear los valores correctos de todos los Minos de la grilla
    {
        for(j = 0; j < ALTO_GRILLA; j++)
        {
            mino = p->vecMinos + (j*ANCHO_GRILLA + i);

//            (p + (j*ANCHO_GRILLA + i))->vecMinos->activo = false; //Puede que no haga falta esta implementacion
//            (p + (j*ANCHO_GRILLA + i))->vecMinos->tam = TAM_MINO;
            minoCrear(mino, TAM_MINO*i, TAM_MINO*j, T);
        }
    }

    return true;
}

void grillaDestruir(tGrilla *p)
{
    free(p->vecMinos);                //Libero memoria
    p->vecMinos = NULL;
}

void grillaDibujar(const tGrilla *p)
{
    int i, j;

    tMino *mino = p->vecMinos;

    for (i = 0; i < ANCHO_GRILLA; i++)
    {
        for (j = 0; j < ALTO_GRILLA; j++)
        {
            mino = p->vecMinos + (j*ANCHO_GRILLA + i);

            minoDibujar(mino);
        }
    }
}
