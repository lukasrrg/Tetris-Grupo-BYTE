#include "tGrilla.h"

bool grillaCrear(tGrilla *p)
{
    p->vecMinos = (tMino*)malloc(ANCHO_GRILLA*ALTO_GRILLA); //Pido memoria para toda la matriz grilla
    if (p->vecMinos == NULL)
    {
        return false;
    }

    int i, j;

    for(i = 0; i < ANCHO_GRILLA; i++) //Setear los valores correctos de todos los Minos de la grilla
    {
        for(j = 0; j < ALTO_GRILLA; j++)
        {
//            (p + (j*ANCHO_GRILLA + i))->vecMinos->activo = false; //Puede que no haga falta esta implementacion
//            (p + (j*ANCHO_GRILLA + i))->vecMinos->tam = TAM_MINO;
            (p + (j*ANCHO_GRILLA + i))->vecMinos->posX = i;
            (p + (j*ANCHO_GRILLA + i))->vecMinos->posY = j;
//            (p + (j*ANCHO_GRILLA + i))->vecMinos->color = paletaCGA[N]; //Esta comentado porque tiene un error aun no resuelto
        }
    }

    return true;
}

void grillaDestruir(tGrilla *p)
{
    free(p);                //Libero memoria
    p = NULL;
}

void grillaDibujar(const tGrilla *p)
{

}
