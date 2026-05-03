#include "tMino.h"

tGBT_ColorRGB paletaCGA[CANT_COLORES] = {

    /// 0-15: Colores CGA (16 colores)
    {0x00, 0x00, 0x00}, // 0:   Negro
    {0x00, 0x00, 0xAA}, // 1:   Azul
    {0x00, 0xAA, 0x00}, // 2:   Verde
    {0x00, 0xAA, 0xAA}, // 3:   Cian
    {0xAA, 0x00, 0x00}, // 4:   Rojo
    {0xAA, 0x00, 0xAA}, // 5:   Magenta
    {0xAA, 0x55, 0x00}, // 6:   Marron
    {0xAA, 0xAA, 0xAA}, // 7:   Gris claro
    {0x55, 0x55, 0x55}, // 8:   Gris oscuro
    {0x55, 0x55, 0xFF}, // 9:   Azul brillante
    {0x55, 0xFF, 0x55}, // 10:  Verde brillante
    {0x55, 0xFF, 0xFF}, // 11:  Cian brillante
    {0xFF, 0x55, 0x55}, // 12:  Rojo brillante
    {0xFF, 0xFF, 0xFE}, // 13:  Blanco
    {0xFF, 0xFF, 0x55}, // 14:  Amarillo
    {0xFF, 0xFF, 0xFF}  // 15:  Usado como transparente por GBT
};

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

void tetraminoCrear(tTetramino *tetramino, int pX, int pY)
{
    static int formas[7][4][4] = {
        { {0,0,0,0},   // O
          {0,1,1,0},
          {0,1,1,0},
          {0,0,0,0} },

        { {0,0,1,0},   // J
          {0,0,1,0},
          {0,1,1,0},
          {0,0,0,0} },

        { {0,0,1,0},   // L
          {0,0,1,0},
          {0,0,1,1},
          {0,0,0,0} },

        { {1,1,1,0},   // T
          {0,1,0,0},
          {0,0,0,0},
          {0,0,0,0} },

        { {0,1,0,0},   // I
          {0,1,0,0},
          {0,1,0,0},
          {0,1,0,0} },

        { {0,1,1,0},   // S
          {1,1,0,0},
          {0,0,0,0},
          {0,0,0,0} },

        { {1,1,0,0},   // Z
          {0,1,1,0},
          {0,0,0,0},
          {0,0,0,0} }
    };

