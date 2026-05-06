#include "tMino.h"

//Matrices para los tetrominos
const char tetrominoVec[CANT_TETROMINOS][TAM_MAX_TETROMINO][TAM_MAX_TETROMINO] =
{
    {//Tetromino T
        {'X', 'X', 'X', ' '},
        {' ', 'X', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },

    {//Tetromino L
        {'X', ' ', ' ', ' '},
        {'X', ' ', ' ', ' '},
        {'X', 'X', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },

    {//Tetromino J
        {' ', 'X', ' ', ' '},
        {' ', 'X', ' ', ' '},
        {'X', 'X', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },

    {//Tetromino I
        {'X', ' ', ' ', ' '},
        {'X', ' ', ' ', ' '},
        {'X', ' ', ' ', ' '},
        {'X', ' ', ' ', ' '}
    },

    {//Tetromino S
        {' ', 'X', 'X', ' '},
        {'X', 'X', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },

    {//Tetromino Z
        {'X', 'X', ' ', ' '},
        {' ', 'X', 'X', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },

    {//Tetromino O
        {'X', 'X', ' ', ' '},
        {'X', 'X', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    }
};

//char tetroT[2][3] = {
//    {'X', 'X', 'X'},
//    {' ', 'X', ' '}
//};
//
//char tetroL[3][2] = {
//    {'X', ' '},
//    {'X', ' '},
//    {'X', 'X'}
//};
//
//char tetroJ[3][2] = {
//    {' ', 'X'},
//    {' ', 'X'},
//    {'X', 'X'}
//};
//
//char tetroI[4][1] = {
//    {'X'},
//    {'X'},
//    {'X'},
//    {'X'}
//};
//
//char tetroS[2][3] = {
//    {' ', 'X', 'X'},
//    {'X', 'X', ' '}
//};
//
//char tetroZ[2][3] = {
//    {'X', 'X', ' '},
//    {' ', 'X', 'X'}
//};
//
//char tetroO[2][2] = {
//    {'X', 'X'},
//    {'X', 'X'}
//};

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

void minoColorDibujar(int color, int pX, int pY)
{
    int i, j;

    for (i = 0; i < TAM_MINO; i++)
    {
        for (j = 0; j < TAM_MINO; j++)
        {
            if (i == 0 || j == 0 || i == TAM_MINO - 1 || j == TAM_MINO - 1)
                gbt_dibujar_pixel(pX + i,pY + j, B);
            else
                gbt_dibujar_pixel(pX + i,pY + j, color);
        }
    }
}

void tetrominoCrear(tTetromino *tetro, char tip, int pX, int pY)
{
    tetro->tipo = tip;
    tetro->posX = pX;
    tetro->posY = pY;

    switch(tip)             //Segun que tipo sea, se define su tamaño y color
    {
        case TETRO_T:
            tetro->altoMat = 2;
            tetro->anchoMat = 3;
            tetro->color = AZ;
            break;
        case TETRO_L:
            tetro->altoMat = 3;
            tetro->anchoMat = 2;
            tetro->color = VE;
            break;
        case TETRO_J:
            tetro->altoMat = 3;
            tetro->anchoMat = 2;
            tetro->color = C;
            break;
        case TETRO_I:
            tetro->altoMat = 4;
            tetro->anchoMat = 1;
            tetro->color = R;
            break;
        case TETRO_S:
            tetro->altoMat = 2;
            tetro->anchoMat = 3;
            tetro->color = M;
            break;
        case TETRO_Z:
            tetro->altoMat = 2;
            tetro->anchoMat = 3;
            tetro->color = VI;
            break;
        case TETRO_O:
            tetro->altoMat = 2;
            tetro->anchoMat = 2;
            tetro->color = AM;
            break;
    }
}
