#include "tMino.h"

void minoCrear(tMino *mino, int pX, int pY, int col)
{
    mino->color = col;
    mino->posX = pX;
    mino->posY = pY;
}

void minoDibujar(tMino *mino)
{
    int i, j;

    for (i = 0; i < TAM_MINO; i++)
    {
        for (j = 0; j < TAM_MINO; j++)
        {
            if (i == 0 || j == 0 || i == TAM_MINO - 1 || j == TAM_MINO - 1)
                gbt_dibujar_pixel(mino->posX + i,mino->posY + j, B);
            else
                gbt_dibujar_pixel(mino->posX + i,mino->posY + j, mino->color);
        }
    }
}
