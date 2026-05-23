#include "tGrilla.h"

bool grillaCrear(tGrilla *p, int resolAncho, int resolAlto, int anchoGrilla)
{
    tMino *mino;
    p->anchoGrilla = anchoGrilla;   //Sino las otras funciones van a leer basura
    p->alto = ALTO_GRILLA_TOTAL;

    int offsetX = (resolAncho - anchoGrilla*TAM_MINO)/2;
    int offsetY = (resolAlto - ALTO_GRILLA_VISIBLE*TAM_MINO)/2;

    p->matMinos = (tMino **)matrizCrear(ALTO_GRILLA_TOTAL, anchoGrilla, sizeof(tMino)); //Pido memoria para toda la matriz grilla
    if (p->matMinos == NULL)
    {
        return false;
    }

    int fila, col;

    for (fila = PRIMERA_FILA_VISIBLE; fila < ALTO_GRILLA_TOTAL; fila++) //Setea los minos de las filas visibles en su respectiva posicion correcta
    {
        for (col = 0; col < anchoGrilla; col++)
        {
            mino = *(p->matMinos + fila) + col;
            minoCrear(mino, TAM_MINO*col + offsetX, TAM_MINO*(fila - PRIMERA_FILA_VISIBLE) + offsetY, T, false);
        }
    }

    return true;
}

void grillaDestruir(tGrilla *p)
{
    free(p->matMinos);                //Libero memoria
    p->matMinos = NULL;
}


void grillaDeFondoDibujar(int resolAncho, int resolAlto, int anchoGrilla)

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

void grillaDibujar(const tGrilla *p, int resolAncho, int resolAlto)
{
    int fila, col;
    tMino *mino;

    int offsetX = (resolAncho - p->anchoGrilla*TAM_MINO)/2;
    int offsetY = (resolAlto - ALTO_GRILLA_VISIBLE*TAM_MINO)/2;

    for (fila = PRIMERA_FILA_VISIBLE; fila < ALTO_GRILLA_TOTAL; fila++)
    {
        for (col = 0; col < p->anchoGrilla; col++)
        {
            mino = *(p->matMinos + fila) + col;
            if (mino->estado)
                minoDibujar(mino->color, TAM_MINO*col + offsetX, TAM_MINO*(fila - PRIMERA_FILA_VISIBLE) + offsetY);
        }
    }
}

void grillaDibujarTetromino(tTetromino *tetro, int resolAncho, int resolAlto, int anchoGrilla)
{
    int fila, col;
    int offsetX = (resolAncho - anchoGrilla*TAM_MINO)/2;
    int offsetY = (resolAlto - ALTO_GRILLA_VISIBLE*TAM_MINO)/2;
    int posX;   //Posicion en X del MINO que se va a dibujar (NO relativo a la grilla)
    int posY;   //Posicion en Y del MINO que se va a dibujar (NO relativo a la grilla)

    for(fila = 0;fila < tetro->altoMat; fila++)
    {
        for(col = 0; col < tetro->anchoMat; col++)
        {
            if (tetrominoVec[(int)tetro->tipo][tetro->rotacion][fila][col] == 'X' && tetro->posY + fila >= 0)
            {
                posX = (tetro->posX + col)*TAM_MINO + offsetX;
                posY = (tetro->posY + fila)*TAM_MINO + offsetY;

                minoDibujar(tetro->color, posX, posY); //Dibujar mino de color tetro->color
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
            if (tetrominoVec[(int)tetro->tipo][tetro->rotacion][i][j] == 'X' && tetro->posY + i >= 0)
            {
                posActualX = tetro->posX + j;
                posActualY = tetro->posY + i + PRIMERA_FILA_VISIBLE;
                minoActual = *(grilla->matMinos + posActualY) + posActualX;
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
            if (tetrominoVec[(int)tetro->tipo][tetro->rotacion][i][j] == 'X' && tetro->posY + i >= 0)
            {
                posActualX = tetro->posX + j + lado;
                posActualY = tetro->posY + i + PRIMERA_FILA_VISIBLE;
                minoActual = *(grilla->matMinos + posActualY) + posActualX;

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
    tMino *minoActual;

    for (i = 0; i < tetro->altoMat; i++)
    {
        for (j = 0; j < tetro->anchoMat; j++)
        {
            if (tetrominoVec[(int)tetro->tipo][tetro->rotacion][i][j] == 'X')
            {
                col = tetro->posX + j;
                fila = tetro->posY + i + PRIMERA_FILA_VISIBLE;
                minoActual = *(grilla->matMinos + fila) + col;

                minoActual->estado = true;
                minoActual->color = tetro->color;
            }
        }
    }
}

void grillaSetearFilaInactiva(tGrilla *grilla)
{
    int i;
    tMino *p = *(grilla->matMinos);

    for (i = 0; i < grilla->anchoGrilla; i++)
    {
        p->estado = false;
        p++;
    }
}

int grillaChequearLinea(tGrilla *grilla, tTetromino *tetro)
{
    int fila, col;
    int cantLineas = 0;

    int filaInicial = tetro->posY;
    int filaFinal = tetro->posY + tetro->altoMat;

    bool hayLinea;

    tMino *filaActual;

    for(fila = filaInicial; fila < filaFinal; fila++)
    {
        hayLinea = true;

        filaActual = *(grilla->matMinos + fila);

        for(col = 0; col < grilla->anchoGrilla && hayLinea; col++)
        {
            if(!(filaActual + col)->estado)
                hayLinea = false;
        }

        if(hayLinea)
        {
            tMino *filaEliminada = grilla->matMinos[fila];

            for(int f = fila; f > 0; f--)
            {
                grilla->matMinos[f] = grilla->matMinos[f - 1];
            }

            grilla->matMinos[0] = filaEliminada;

            grillaSetearFilaInactiva(grilla);

            cantLineas++;

            fila--;
        }
    }

    return cantLineas;
}
