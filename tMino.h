#ifndef TMINO_H_INCLUDED
#define TMINO_H_INCLUDED

#include <stdbool.h>

#include "lib/GBT_v2026.1C.01/include/GBT/gbt.h"
#include "paleta.h"

//Tamaño de mino
#define TAM_MINO 8
#define TAM_MAX_TETROMINO 4

#define TETRO_T 0
#define TETRO_L 1
#define TETRO_J 2
#define TETRO_I 3
#define TETRO_S 4
#define TETRO_Z 5
#define TETRO_O 6
#define TETRO_X 7
#define TETRO_C 8
#define TETRO_P 9
#define TETRO_V 10

#define CANT_TETROMINOS 11
#define CANT_TETROMINOS_CLASSIC 7
#define TAM_VEC_TETROMINOS 5

//Matrices de tetrominos
extern const char tetrominoVec[CANT_TETROMINOS][TAM_MAX_TETROMINO][TAM_MAX_TETROMINO];

typedef struct      //Esta estructura define cada Mino, o sea, cada CUADRADRITO
{
    bool estado;
//    int tam;  //Puede que no haga falta esta implementacion
    int posX;
    int posY;
    int color;
} tMino;

typedef struct
{
    char tipo;      //Tipos de tetromino: T L J I S Z O X C P V
    int posX;       //Posicion en X en relacion a la grilla
    int posY;       //Posicion en Y en relacion a la grilla
    int color;
    int anchoMat;
    int altoMat;
//    char matriz[TAM_TETROMINO][TAM_TETROMINO];
} tTetromino;

void minoCrear(tMino *mino, int pX, int pY, int col, bool est);
void minoDibujar(tMino *mino);
void minoColorDibujar(int color, int pX, int pY);
void tetrominoCrear(tTetromino *tetro, char tip, int grX, int grY);
void tetrominoCargarVector(tTetromino vec[TAM_VEC_TETROMINOS], int totalTetrominos);         //Toma un vector de un tamaño TAM_VEC_TETROMINOS y lo carga con tetrominos al azar
void actualizarVectorTetrominos(tTetromino vec[TAM_VEC_TETROMINOS], int totalTetrominos);    //Desplaza todos los elementos del vector a la izquierda y agrega un nuevo tetromino al final del vector
void tetrominoDibujar(tTetromino *tetro, int posX, int posY);       //Dibuja un tetromino en una coordenada especifica

#endif // TMINO_H_INCLUDED
