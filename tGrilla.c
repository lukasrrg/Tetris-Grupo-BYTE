#include "tGrilla.h"

bool grillaCrear(tGrilla *p, int resolAncho, int resolAlto, int anchoGrilla)
{
    tMino *mino;
    p->anchoGrilla = anchoGrilla;   //Sino las otras funciones van a leer basura
    p->alto = ALTO_GRILLA_TOTAL;

<<<<<<< HEAD
    int offsetX = (resolAncho - anchoGrilla*TAM_MINO)/2;
=======
    p->ancho = ANCHO_GRILLA;
    p->alto = ALTO_GRILLA_TOTAL;

    int offsetX = (resolAncho - ANCHO_GRILLA*TAM_MINO)/2;
>>>>>>> bafd173e0d91aff7488c7bdf4932643df57b838d
    int offsetY = (resolAlto - ALTO_GRILLA_VISIBLE*TAM_MINO)/2;

    p->vecMinos = malloc(anchoGrilla*ALTO_GRILLA_TOTAL*sizeof(tMino)); //Pido memoria para toda la matriz grilla
    if (p->vecMinos == NULL)
    {
        return false;
    }

    mino = p->vecMinos;

    int fila, col;

    for(fila = 0; fila < PRIMERA_FILA_VISIBLE; fila++) //Setear los minos de las filas invisibles en 0, 0 e inactivo
    {
        for(col = 0; col < anchoGrilla; col++)
        {
            mino = p->vecMinos + (fila*anchoGrilla + col);
            minoCrear(mino, 0, 0, T, false);
        }
    }

    for (fila = PRIMERA_FILA_VISIBLE; fila < ALTO_GRILLA_TOTAL; fila++) //Setea los minos de las filas visibles en su respectiva posicion correcta
    {
        for (col = 0; col < anchoGrilla; col++)
        {
            mino = p->vecMinos + (fila*anchoGrilla + col);
            minoCrear(mino, TAM_MINO*col + offsetX, TAM_MINO*(fila - PRIMERA_FILA_VISIBLE) + offsetY, T, false);
        }
    }

    return true;
}

void grillaDestruir(tGrilla *p)
{
    free(p->vecMinos);                //Libero memoria
    p->vecMinos = NULL;
}

<<<<<<< HEAD
void grillaDeFondoDibujar(int resolAncho, int resolAlto, int anchoGrilla)
=======
void grillaDeFondoDibujar(int resolAncho, int resolAlto)    //FUNCION INNECESARIA, SE PUEDE REEMPLAZAR POR dibujarRectangulo()
>>>>>>> bafd173e0d91aff7488c7bdf4932643df57b838d
{
    int i;

    int ancho = anchoGrilla*TAM_MINO;
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
    int fila, col;
    tMino *mino;

    for (fila = PRIMERA_FILA_VISIBLE; fila < ALTO_GRILLA_TOTAL; fila++)
    {
        for (col = 0; col < p->anchoGrilla; col++)
        {
            mino = p->vecMinos + (fila*p->anchoGrilla + col);
            if (mino->estado)
                minoDibujar(mino);
        }
    }
}

void grillaDibujarTetromino(tTetromino *tetro, int resolAncho, int resolAlto, int anchoGrilla)
{
    int fila, col;
    int posX, posY;

    int offsetX = (resolAncho - anchoGrilla*TAM_MINO)/2;
    int offsetY = (resolAlto - ALTO_GRILLA_VISIBLE*TAM_MINO)/2;

<<<<<<< HEAD
    for(fila = 0; fila < tetro->altoMat; fila++)
=======

    int posX;   //Posicion en X del MINO que se va a dibujar (NO relativo a la grilla)
    int posY;   //Posicion en Y del MINO que se va a dibujar (NO relativo a la grilla)

    for(fila = 0;fila < tetro->altoMat; fila++)
>>>>>>> bafd173e0d91aff7488c7bdf4932643df57b838d
    {
        for(col = 0; col < tetro->anchoMat; col++)
        {
            if (tetrominoVec[(int)tetro->tipo][tetro->rotacion][fila][col] == 'X' && tetro->posY + fila >= 0)
            {
                posX = (tetro->posX + col)*TAM_MINO + offsetX;
                posY = (tetro->posY + fila)*TAM_MINO + offsetY;
<<<<<<< HEAD
                minoColorDibujar(tetro->color, posX, posY);
=======
                minoColorDibujar(tetro->color, posX, posY); //Dibujar mino de color tetro->color
>>>>>>> bafd173e0d91aff7488c7bdf4932643df57b838d
            }
        }
    }
}

bool tetrominoColisionaSuelo(tTetromino *tetro)
{
    if(tetro->posY + tetro->altoMat == ALTO_GRILLA_VISIBLE + 1)
        return true;
    return false;
}

bool tetrominoColisionaConOtro(tTetromino *tetro, tGrilla *grilla)
{
    int i, j;
    tMino *minoActual;
    int posActualX, posActualY;

    for (i = 0; i < tetro->altoMat; i++)
    {
        for (j = 0; j < tetro->anchoMat; j++)
        {
            if (tetrominoVec[(int)tetro->tipo][tetro->rotacion][i][j] == 'X')
            {
                posActualX = tetro->posX + j;
                posActualY = tetro->posY + i + PRIMERA_FILA_VISIBLE;
                minoActual = grilla->vecMinos + (posActualY * grilla->anchoGrilla + posActualX);

                if (minoActual->estado)
                    return true;
            }
        }
    }
    return false;
}

bool tetrominoColisionaLateralmente(tTetromino *tetro, tGrilla *grilla, int lado)
{
    //Deteccion de colision con el borde izquierdo
    if (tetro->posX + lado < 0)
        return true;
    //Deteccion de colision con el borde derecho
    if (tetro->posX + tetro->anchoMat + lado == grilla->anchoGrilla + 1)
        return true;

    int i, j;
    tMino *minoActual;
    int posActualX, posActualY;

    for (i = 0; i < tetro->altoMat; i++)
    {
        for (j = 0; j < tetro->anchoMat; j++)
        {
            if (tetrominoVec[(int)tetro->tipo][tetro->rotacion][i][j] == 'X')
            {
                posActualX = tetro->posX + j + lado;
                posActualY = tetro->posY + i + PRIMERA_FILA_VISIBLE;
                minoActual = grilla->vecMinos + (posActualY * grilla->anchoGrilla + posActualX);

                if (minoActual->estado)
                    return true;
            }
        }
    }
    return false;
}

bool tetrominoColisionaConOtro(tTetromino *tetro, tGrilla *grillaTetrominos)
{
    int i, j;

    tMino *minoActual;
    int posActualX, posActualY;

    for (i = 0; i < tetro->altoMat; i++)
    {
        for (j = 0; j < tetro->anchoMat; j++)
        {
            if (tetrominoVec[(int)tetro->tipo][tetro->rotacion][i][j] == 'X')
            {
                posActualX = tetro->posX + j;
                posActualY = tetro->posY + i + PRIMERA_FILA_VISIBLE;
                minoActual = grillaTetrominos->vecMinos + (posActualY*grillaTetrominos->ancho + posActualX);

                if (minoActual->estado)
                    return true;
            }
        }
    }

    return false;
}

bool tetrominoColisionaLateralmente(tTetromino *tetro, tGrilla *grillaTetrominos, int lado)
{
    //Deteccion de colision con el borde izquierdo
    if (tetro->posX + lado < 0)
        return true;
    //Deteccion de colision con el borde derecho
    if (tetro->posX + tetro->anchoMat + lado == grillaTetrominos->ancho + 1)
        return true;


    int i, j;

    tMino *minoActual;      //Es el mino con el que estmaos verificando si hay colision o no
    int posActualX, posActualY;     //No es la posicion del tetromino, sino es la posicion actual del MINO con el que estamos verificando si hay colision o no

    for (i = 0; i < tetro->altoMat; i++)
    {
        for (j = 0; j < tetro->anchoMat; j++)
        {
            if (tetrominoVec[(int)tetro->tipo][tetro->rotacion][i][j] == 'X')
            {
                posActualX = tetro->posX + j + lado;
                posActualY = tetro->posY + i + PRIMERA_FILA_VISIBLE;
                minoActual = grillaTetrominos->vecMinos + (posActualY*grillaTetrominos->ancho + posActualX);

                if (minoActual->estado)
                    return true;
            }
        }
    }

    return false;
}


void grillaActualizar(tGrilla *grilla, tTetromino *tetro)
{
    int i, j;
    int col, fila;

    for (i = 0; i < tetro->altoMat; i++)
    {
        for (j = 0; j < tetro->anchoMat; j++)
        {
            if (tetrominoVec[(int)tetro->tipo][tetro->rotacion][i][j] == 'X')
            {
                col = tetro->posX + j;
                fila = tetro->posY + i + PRIMERA_FILA_VISIBLE - 1;

<<<<<<< HEAD
                (grilla->vecMinos + fila*grilla->anchoGrilla + col)->estado = true;
                (grilla->vecMinos + fila*grilla->anchoGrilla + col)->color = tetro->color;
=======

                (grilla->vecMinos + fila*grilla->ancho + col)->estado = true;
                (grilla->vecMinos + fila*grilla->ancho + col)->color = tetro->color;
>>>>>>> bafd173e0d91aff7488c7bdf4932643df57b838d
            }
        }
    }
}
