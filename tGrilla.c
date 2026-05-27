#include "tGrilla.h"
#include "tPantalla.h"

void grillaDecorativaSetear(tGrilla *grilla)
{
    int fila, col;
    tMino *minoActual;

    for (fila = 0; fila < grilla->alto; fila++)
    {
        for (col = 0; col < grilla->anchoGrilla; col++)
        {
            minoActual = *(grilla->matMinos + fila) + col;
            minoActual->estado = true;
            minoActual->color = rand()%CANT_TETROMINOS_CLASSIC + 1;
        }
    }

}

bool grillaCrear(tGrilla *p, int anchoGrilla, int altoGrilla)
{
    tMino *mino;
    p->anchoGrilla = anchoGrilla;   //Sino las otras funciones van a leer basura
    p->alto = altoGrilla;

    p->matMinos = (tMino **)matrizCrear(altoGrilla, anchoGrilla, sizeof(tMino)); //Pido memoria para toda la matriz grilla
    if (p->matMinos == NULL)
    {
        return false;
    }

    int fila, col;

    for (fila = 0; fila < altoGrilla; fila++) //Setea los minos de las filas visibles en su respectiva posicion correcta
    {
        for (col = 0; col < anchoGrilla; col++)
        {
            mino = *(p->matMinos + fila) + col;
            minoCrear(mino, T, false);
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

    int ancho = anchoGrilla*tamMino;
    int alto = ALTO_GRILLA_VISIBLE*tamMino;

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

    int offsetX = (resolAncho - p->anchoGrilla*tamMino)/2;
    int offsetY = (resolAlto - ALTO_GRILLA_VISIBLE*tamMino)/2;

    for (fila = PRIMERA_FILA_VISIBLE; fila < ALTO_GRILLA_TOTAL; fila++)
    {
        for (col = 0; col < p->anchoGrilla; col++)
        {
            mino = *(p->matMinos + fila) + col;
            if (mino->estado)
                minoDibujar(mino->color, tamMino*col + offsetX, tamMino*(fila - PRIMERA_FILA_VISIBLE) + offsetY);
        }
    }
}

void grillaDibujarTetromino(tTetromino *tetro, int resolAncho, int resolAlto, int anchoGrilla, int modoDeJuego)
{
    int fila, col;
    int offsetX = (resolAncho - anchoGrilla*tamMino)/2;
    int offsetY = (resolAlto - ALTO_GRILLA_VISIBLE*tamMino)/2;
    int posX;   //Posicion en X del MINO que se va a dibujar (NO relativo a la grilla)
    int posY;   //Posicion en Y del MINO que se va a dibujar (NO relativo a la grilla)

    for(fila = 0; fila < tetro->altoMat; fila++)
    {
        for(col = 0; col < tetro->anchoMat; col++)
        {
            if (tetrominoVec[(int)tetro->tipo][tetro->rotacion][fila][col] == 'X' && tetro->posY + fila >= 0)
            {
                int xEfectivo = tetro->posX + col;

                if (modoDeJuego == MODO_DELUXE)
                {
                    xEfectivo = (xEfectivo % anchoGrilla + anchoGrilla) % anchoGrilla;              //Para rotacion circular
                }

                posX = xEfectivo * tamMino + offsetX;
                posY = (tetro->posY + fila)*tamMino + offsetY;

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

bool tetrominoColisionaLateralmente(tTetromino *tetro, tGrilla *grilla, int lado, int modoDeJuego)
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
                posActualX = tetro->posX + j + lado;
                posActualY = tetro->posY + i + PRIMERA_FILA_VISIBLE;

                if (modoDeJuego == MODO_DELUXE)
                {
                    posActualX = (posActualX % grilla->anchoGrilla + grilla->anchoGrilla) % grilla->anchoGrilla;       //Rotacion circular en caso de deluxe
                } else if (posActualX < 0 || posActualX >= grilla->anchoGrilla)        //Choca con las paredes laterales
                        return true;

                // Choca con otra pieza
                if (posActualY < grilla->alto)
                {
                    minoActual = *(grilla->matMinos + posActualY) + posActualX;
                    if (minoActual->estado)
                        return true;
                }
            }
        }
    }
    return false;
}

bool tetrominoColisionaConOtro(tTetromino *tetro, tGrilla *grilla, int modoDeJuego)
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

//                // Al rotar, choca con paredes laterales          //FUNCIONA BIEN SIN ESTO?
//                if (posActualX < 0 || posActualX >= grilla->anchoGrilla)
//                    return true;
//
//                // Al rotar, se pasa del piso
//                if (posActualY >= grilla->alto)
//                    return true;

                if (modoDeJuego == MODO_DELUXE)
                {
                    posActualX = (posActualX % grilla->anchoGrilla + grilla->anchoGrilla) % grilla->anchoGrilla;
                }
                else
                {
                    if (posActualX < 0 || posActualX >= grilla->anchoGrilla)        //Al rotar choca con paredes laterales
                        return true;
                }

                // Al rotar, se pasa del piso
                if (posActualY >= grilla->alto)
                    return true;

                // Al rotar, choca con otra pieza
                if (posActualY >= 0)
                {
                    minoActual = *(grilla->matMinos + posActualY) + posActualX;
                    if (minoActual->estado)
                        return true;
                }
            }
        }
    }

    return false;
}

void grillaActualizar(tGrilla *grilla, tTetromino *tetro, int modoDeJuego)
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
                if (modoDeJuego == MODO_DELUXE)
                {
                    col = (col % grilla->anchoGrilla + grilla->anchoGrilla) % grilla->anchoGrilla;
                }

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

    int filaInicial = tetro->posY +  PRIMERA_FILA_VISIBLE;
    int filaFinal = tetro->posY + tetro->altoMat + PRIMERA_FILA_VISIBLE;

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
