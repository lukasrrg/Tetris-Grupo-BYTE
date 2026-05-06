#include "tGrilla.h"

bool grillaCrear(tGrilla *p, int resolAncho, int resolAlto)
{
    tMino *mino;
    int offsetX = (resolAncho - ANCHO_GRILLA*TAM_MINO)/2;           //Coordenada en X del primer pixel superior izquierdo
    int offsetY = (resolAlto - ALTO_GRILLA_VISIBLE*TAM_MINO)/2;     //Coordenada en Y del primer pixel superior izquierdo

    p->vecMinos = malloc(ANCHO_GRILLA*ALTO_GRILLA_TOTAL*sizeof(tMino)); //Pido memoria para toda la matriz grilla
    if (p->vecMinos == NULL)
    {
        return false;
    }

    mino = p->vecMinos;

    int i, j;

    for(i = 0; i < ANCHO_GRILLA; i++) //Setear los valores correctos de todos los Minos de la grilla
    {
        for(j = 0; j < ALTO_GRILLA_TOTAL; j++)
        {
            mino = p->vecMinos + (j*ANCHO_GRILLA + i);

//            (p + (j*ANCHO_GRILLA + i))->vecMinos->activo = false; //Puede que no haga falta esta implementacion
//            (p + (j*ANCHO_GRILLA + i))->vecMinos->tam = TAM_MINO;
            minoCrear(mino, TAM_MINO*i + offsetX, TAM_MINO*j + offsetY, T);
        }
    }

    return true;
}

void grillaDestruir(tGrilla *p)
{
    free(p->vecMinos);                //Libero memoria
    p->vecMinos = NULL;
}

void grillaDeFondoDibujar(int resolAncho, int resolAlto)
{
    int i, j;

    int offsetX = (resolAncho - ANCHO_GRILLA*TAM_MINO)/2;
    int offsetY = (resolAlto - ALTO_GRILLA_VISIBLE*TAM_MINO)/2;

    for (i = 0; i < ANCHO_GRILLA; i++)
    {
        for (j = 0; j < ALTO_GRILLA_VISIBLE; j++)
        {
            minoColorDibujar(N, TAM_MINO*i + offsetX, TAM_MINO*j + offsetY);
        }
    }
}

void grillaDibujar(const tGrilla *p)
{
    int i, j;

    tMino *mino = p->vecMinos;

    for (i = 0; i < ANCHO_GRILLA; i++)
    {
        for (j = 0; j < ALTO_GRILLA_VISIBLE; j++)
        {
            mino = p->vecMinos + (j*ANCHO_GRILLA + i);

            minoDibujar(mino);
        }
    }
}

void grillaDibujarTetromino(tTetromino *tetro, int resolAncho, int resolAlto)        //Dibuja en la grilla un tetromino en (tetro->posX, tetro->posY)
{
    int i, j;

    int offsetX = (resolAncho - ANCHO_GRILLA*TAM_MINO)/2;           //Coordenada en X del primer pixel superior izquierdo de la grilla
    int offsetY = (resolAlto - ALTO_GRILLA_VISIBLE*TAM_MINO)/2;     //Coordenada en Y del primer pixel superior izquierdo de la grilla

    for(i = 0;i < tetro->altoMat; i++)
    {
        for(j = 0; j < tetro->anchoMat; j++)
        {
            if (tetrominoVec[(int)tetro->tipo][i][j] == 'X')
            {
                minoColorDibujar(tetro->color, (tetro->posX + j)*TAM_MINO + offsetX, (tetro->posY + i)*TAM_MINO + offsetY); //Dibujar mino de color tetro->color
            }
        }
    }
}
