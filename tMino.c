#include "tMino.h"

//Matrices para los tetrominos

const char tetrominoVec[CANT_TETROMINOS_DELUXE][4][TAM_MAX_TETROMINO][TAM_MAX_TETROMINO] =

{
    {   {
            //Tetromino T Rotacion 0
            {'X', 'X', 'X', ' '},
            {' ', 'X', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            //Tetromino T Rotacion 1
            {' ', 'X', ' ', ' '},
            {'X', 'X', ' ', ' '},
            {' ', 'X', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            //Tetromino T Rotacion 2
            {' ', 'X', ' ', ' '},
            {'X', 'X', 'X', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            //Tetromino T Rotacion 3
            {'X', ' ', ' ', ' '},
            {'X', 'X', ' ', ' '},
            {'X', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        }
    },

    {   {
            //Tetromino L Rotacion 0
            {'X', ' ', ' ', ' '},
            {'X', ' ', ' ', ' '},
            {'X', 'X', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            //Tetromino L Rotacion 1
            {'X', 'X', 'X', ' '},
            {'X', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            //Tetromino L Rotacion 2
            {'X', 'X', ' ', ' '},
            {' ', 'X', ' ', ' '},
            {' ', 'X', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            //Tetromino L Rotacion 3
            {' ', ' ', 'X', ' '},
            {'X', 'X', 'X', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        }
    },

    {   {
            //Tetromino J Rotacion 0
            {' ', 'X', ' ', ' '},
            {' ', 'X', ' ', ' '},
            {'X', 'X', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            //Tetromino J Rotacion 1
            {'X', ' ', ' ', ' '},
            {'X', 'X', 'X', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            //Tetromino J Rotacion 2
            {'X', 'X', ' ', ' '},
            {'X', ' ', ' ', ' '},
            {'X', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            //Tetromino J Rotacion 3
            {'X', 'X', 'X', ' '},
            {' ', ' ', 'X', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        }
    },

    {   {
            //Tetromino I Rotacion 0
            {'X', ' ', ' ', ' '},
            {'X', ' ', ' ', ' '},
            {'X', ' ', ' ', ' '},
            {'X', ' ', ' ', ' '}
        },
        {
            //Tetromino I Rotacion 1
            {'X', 'X', 'X', 'X'},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            //Tetromino I Rotacion 2
            {'X', ' ', ' ', ' '},
            {'X', ' ', ' ', ' '},
            {'X', ' ', ' ', ' '},
            {'X', ' ', ' ', ' '}
        },
        {
            //Tetromino I Rotacion 3
            {'X', 'X', 'X', 'X'},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        }
    },

    {   {
            //Tetromino S Rotacion 0
            {' ', 'X', 'X', ' '},
            {'X', 'X', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            //Tetromino S Rotacion 1
            {'X', ' ', ' ', ' '},
            {'X', 'X', ' ', ' '},
            {' ', 'X', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            //Tetromino S Rotacion 2
            {' ', 'X', 'X', ' '},
            {'X', 'X', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            //Tetromino S Rotacion 3
            {'X', ' ', ' ', ' '},
            {'X', 'X', ' ', ' '},
            {' ', 'X', ' ', ' '},
            {' ', ' ', ' ', ' '}
        }
    },

    {   {
            //Tetromino Z Rotacion 0
            {'X', 'X', ' ', ' '},
            {' ', 'X', 'X', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            //Tetromino Z Rotacion 1
            {' ', 'X', ' ', ' '},
            {'X', 'X', ' ', ' '},
            {'X', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            //Tetromino Z Rotacion 2
            {'X', 'X', ' ', ' '},
            {' ', 'X', 'X', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            //Tetromino Z Rotacion 3
            {' ', 'X', ' ', ' '},
            {'X', 'X', ' ', ' '},
            {'X', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        }
    },

    {   {
            //Tetromino O Rotacion 0
            {'X', 'X', ' ', ' '},
            {'X', 'X', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            //Tetromino O Rotacion 1
            {'X', 'X', ' ', ' '},
            {'X', 'X', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            //Tetromino O Rotacion 2
            {'X', 'X', ' ', ' '},
            {'X', 'X', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            //Tetromino O Rotacion 3
            {'X', 'X', ' ', ' '},
            {'X', 'X', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        }
    },

    {   {
            //Tetromino X Rotacion 0
            {'X', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            //Tetromino X Rotacion 1
            {'X', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            //Tetromino X Rotacion 2
            {'X', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            //Tetromino X Rotacion 3
            {'X', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        }
    },

    {   {
            //Tetromino C Rotacion 0
            {'X', 'X', ' ', ' '},
            {'X', ' ', ' ', ' '},
            {'X', 'X', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            //Tetromino C Rotacion 1
            {'X', 'X', 'X', ' '},
            {'X', ' ', 'X', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            //Tetromino C Rotacion 2
            {'X', 'X', ' ', ' '},
            {' ', 'X', ' ', ' '},
            {'X', 'X', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            //Tetromino C Rotacion 3
            {'X', ' ', 'X', ' '},
            {'X', 'X', 'X', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        }
    },

    {   {
            //Tetromino P Rotacion 0
            {'X', 'X', ' ', ' '},
            {'X', 'X', ' ', ' '},
            {'X', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            //Tetromino P Rotacion 1
            {'X', 'X', 'X', ' '},
            {' ', 'X', 'X', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            //Tetromino P Rotacion 2
            {' ', 'X', ' ', ' '},
            {'X', 'X', ' ', ' '},
            {'X', 'X', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            //Tetromino P Rotacion 3
            {'X', 'X', ' ', ' '},
            {'X', 'X', 'X', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        }
    },

    {   {
            //Tetromino V Rotacion 0
            {'X', ' ', 'X', ' '},
            {' ', 'X', ' ',' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            //Tetromino V Rotacion 1
            {' ', 'X', ' ', ' '},
            {'X', ' ', ' ',' '},
            {' ', 'X', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            //Tetromino V Rotacion 2
            {' ', 'X', ' ', ' '},
            {'X', ' ', 'X',' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            //Tetromino V Rotacion 3
            {'X', ' ', ' ', ' '},
            {' ', 'X', ' ',' '},
            {'X', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        }
    }
};

void minoCrear(tMino *mino, int col, bool est)
{
    mino->color = col;
    mino->estado = est;
}

void minoDibujar(int color, int pX, int pY)
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
    tetro->rotacion = 0;
    tetro->posX = pX;
    tetro->posY = pY;

    switch(tip)             //Segun que tipo sea, se define su tamańo y color
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
    case TETRO_X:
        tetro->altoMat = 1;
        tetro->anchoMat = 1;
        tetro->color = AB;
        break;
    case TETRO_C:
        tetro->altoMat = 3;
        tetro->anchoMat = 2;
        tetro->color = VB;
        break;
    case TETRO_P:
        tetro->altoMat = 3;
        tetro->anchoMat = 2;
        tetro->color = NA;
        break;
    case TETRO_V:
        tetro->altoMat = 2;
        tetro->anchoMat = 3;
        tetro->color = RB;
        break;
    }
}

void tetrominoCargarVector(tTetromino vec[TAM_VEC_TETROMINOS], int totalTetrominos, int anchoGrilla)
{
    int i;

    for(i = 0; i < TAM_VEC_TETROMINOS; i++)
    {
        tetrominoCrear(&vec[i], rand()%totalTetrominos, anchoGrilla/2 - 1, 0);
        vec[i].posY = -1*vec[i].altoMat;
    }
}

bool _existeOtroMenosFrecuente(int indiceActual, int totalTetrominos, int tetrominosColocados[CANT_TETROMINOS_DELUXE])
{
    int i;

    for(i = 0; i < totalTetrominos; i++)
    {
        if (tetrominosColocados[i] < tetrominosColocados[indiceActual])
            return true;
    }

    return false;
}

void actualizarVectorTetrominos(tTetromino vec[TAM_VEC_TETROMINOS], int totalTetrominos, int tetrominosColocados[CANT_TETROMINOS_DELUXE], int anchoGrilla)
{
    vectorShiftear(vec, 1, TAM_VEC_TETROMINOS, sizeof(tTetromino), IZQUIERDA);

    int proximoTetromino = rand()%totalTetrominos;

    while(_existeOtroMenosFrecuente(proximoTetromino, totalTetrominos, tetrominosColocados)) //Mientras existe uno que haya aparecido menos cantidad de veces, se recalcula el random
    {
        proximoTetromino = rand()%totalTetrominos;
    }

    tetrominoCrear(&vec[TAM_VEC_TETROMINOS - 1], proximoTetromino, anchoGrilla/2 - 1, 0);
    vec[TAM_VEC_TETROMINOS - 1].posY = -1*vec[TAM_VEC_TETROMINOS - 1].altoMat;
}

void tetrominoDibujar(tTetromino *tetro, int posX, int posY)        //Dibuja un tetromino en una coordenada especifica
{
    int fila, col;

    for(fila = 0; fila < tetro->altoMat; fila++)
    {
        for(col = 0; col < tetro->anchoMat; col++)
        {
            if (tetrominoVec[(int)tetro->tipo][tetro->rotacion][fila][col] == 'X')
            {
                minoDibujar(tetro->color, posX + col*TAM_MINO, posY + fila*TAM_MINO); //Dibujar mino de color tetro->color
            }
        }
    }
}

void tetrominoRotar(tTetromino *tetro, int sentido)
{
    int aux;

    tetro->rotacion = (tetro->rotacion + sentido + 4)%4;
    aux = tetro->altoMat;
    tetro->altoMat = tetro->anchoMat;
    tetro->anchoMat = aux;
}
