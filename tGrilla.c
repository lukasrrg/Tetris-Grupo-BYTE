#include "tGrilla.h"

bool grillaCrear(tGrilla *p, int resolAncho, int resolAlto)
{
    tMino *mino;

    int offsetX = (resolAncho - ANCHO_GRILLA*TAM_MINO)/2;
    int offsetY = (resolAlto - ALTO_GRILLA_VISIBLE*TAM_MINO)/2 - ALTO_GRILLA_INVISIBLE*TAM_MINO;

    p->vecMinos = malloc(ANCHO_GRILLA*ALTO_GRILLA_TOTAL*sizeof(tMino)); //Pido memoria para toda la matriz grilla
    if (p->vecMinos == NULL)
    {
        return false;
    }

    mino = p->vecMinos;

    int i, j;

    for(i = 0; i < ANCHO_GRILLA; i++) //Setear los valores correctos de todos los Minos de la grilla
    {
        for(j = 0; j < ALTO_GRILLA_TOTAL; j++)  // Inicializar todas las filas, incluidas las 4 invisibles
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
    int i;

    int ancho = ANCHO_GRILLA*TAM_MINO;
    int alto = ALTO_GRILLA_VISIBLE*TAM_MINO;

    int offsetX = (resolAncho - ancho)/2;
    int offsetY = (resolAlto - alto)/2;

    for (i = 0; i < ancho; i++)         //Linea superior
        gbt_dibujar_pixel(offsetX + i, offsetY, B);
    for (i = 0; i < alto; i++)          //Linea derecha
        gbt_dibujar_pixel(offsetX + ancho - 1, offsetY + i, B);
    for (i = ancho - 1; i >= 0; i--)    //Linea inferior
        gbt_dibujar_pixel(offsetX + i, offsetY + alto - 1, B);
    for (i = alto - 1; i >= 0; i--)     //Linea izquierda
        gbt_dibujar_pixel(offsetX, offsetY + i, B);
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
