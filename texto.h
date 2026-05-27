#ifndef TEXTO_H_INCLUDED
#define TEXTO_H_INCLUDED

#include "lib/GBT_v2026.1C.01/include/GBT/gbt.h"
#include <string.h>

#define ALTO_ESTANDAR_LETRA 8
#define ESPACIADO_ENTRE_LETRAS 1
#define CANTIDAD_DE_CARACTERES 38
#define ESCALA_TITULO 4
#define TAM_MAX_NUMERO 15
#define ALTO_ESTANDAR_LETRA_FUENTE_2 10

#define FUENTE_1 1
#define FUENTE_2 2

typedef struct
{
    int espaciado;          //Cantidad de pixeles de ancho
    int alto;               // Alto de la matriz para la implementacion de una fuente o otra
    const char *matriz;     //Matriz que indica que pixeles se pintan y cuales no
} tCaracter;

typedef struct              //Marca la posición del siguiente caracter en una oracion o palabra
{
    int posX;
    int posY;
} tCursorTexto;

//Caracteres de la fuente1
extern const char aMay1[ALTO_ESTANDAR_LETRA][5];
extern const char bMay1[ALTO_ESTANDAR_LETRA][5];
extern const char cMay1[ALTO_ESTANDAR_LETRA][5];
extern const char dMay1[ALTO_ESTANDAR_LETRA][5];
extern const char eMay1[ALTO_ESTANDAR_LETRA][5];
extern const char fMay1[ALTO_ESTANDAR_LETRA][5];
extern const char gMay1[ALTO_ESTANDAR_LETRA][5];
extern const char hMay1[ALTO_ESTANDAR_LETRA][5];
extern const char iMay1[ALTO_ESTANDAR_LETRA][3];
extern const char jMay1[ALTO_ESTANDAR_LETRA][5];
extern const char kMay1[ALTO_ESTANDAR_LETRA][5];
extern const char lMay1[ALTO_ESTANDAR_LETRA][5];
extern const char mMay1[ALTO_ESTANDAR_LETRA][5];
extern const char nMay1[ALTO_ESTANDAR_LETRA][5];
extern const char oMay1[ALTO_ESTANDAR_LETRA][5];
extern const char pMay1[ALTO_ESTANDAR_LETRA][5];
extern const char qMay1[ALTO_ESTANDAR_LETRA][5];
extern const char rMay1[ALTO_ESTANDAR_LETRA][5];
extern const char sMay1[ALTO_ESTANDAR_LETRA][5];
extern const char tMay1[ALTO_ESTANDAR_LETRA][5];
extern const char uMay1[ALTO_ESTANDAR_LETRA][5];
extern const char vMay1[ALTO_ESTANDAR_LETRA][5];
extern const char wMay1[ALTO_ESTANDAR_LETRA][5];
extern const char xMay1[ALTO_ESTANDAR_LETRA][5];
extern const char yMay1[ALTO_ESTANDAR_LETRA][5];
extern const char zMay1[ALTO_ESTANDAR_LETRA][5];
extern const char espacio1[ALTO_ESTANDAR_LETRA][2];
extern const char cero1[ALTO_ESTANDAR_LETRA][4];
extern const char uno1[ALTO_ESTANDAR_LETRA][3];
extern const char dos1[ALTO_ESTANDAR_LETRA][4];
extern const char tres1[ALTO_ESTANDAR_LETRA][4];
extern const char cuatro1[ALTO_ESTANDAR_LETRA][5];
extern const char cinco1[ALTO_ESTANDAR_LETRA][4];
extern const char seis1[ALTO_ESTANDAR_LETRA][4];
extern const char siete1[ALTO_ESTANDAR_LETRA][4];
extern const char ocho1[ALTO_ESTANDAR_LETRA][4];
extern const char nueve1[ALTO_ESTANDAR_LETRA][4];
extern const char dosPuntos1[ALTO_ESTANDAR_LETRA][2];

// Fuente 2

extern const char aMay2[ALTO_ESTANDAR_LETRA_FUENTE_2][5];
extern const char bMay2[ALTO_ESTANDAR_LETRA_FUENTE_2][5];
extern const char cMay2[ALTO_ESTANDAR_LETRA_FUENTE_2][5];
extern const char dMay2[ALTO_ESTANDAR_LETRA_FUENTE_2][5];
extern const char eMay2[ALTO_ESTANDAR_LETRA_FUENTE_2][5];
extern const char fMay2[ALTO_ESTANDAR_LETRA_FUENTE_2][5];
extern const char gMay2[ALTO_ESTANDAR_LETRA_FUENTE_2][5];
extern const char hMay2[ALTO_ESTANDAR_LETRA_FUENTE_2][5];
extern const char iMay2[ALTO_ESTANDAR_LETRA_FUENTE_2][3];
extern const char jMay2[ALTO_ESTANDAR_LETRA_FUENTE_2][5];
extern const char kMay2[ALTO_ESTANDAR_LETRA_FUENTE_2][5];
extern const char lMay2[ALTO_ESTANDAR_LETRA_FUENTE_2][5];
extern const char mMay2[ALTO_ESTANDAR_LETRA_FUENTE_2][5];
extern const char nMay2[ALTO_ESTANDAR_LETRA_FUENTE_2][5];
extern const char oMay2[ALTO_ESTANDAR_LETRA_FUENTE_2][5];
extern const char pMay2[ALTO_ESTANDAR_LETRA_FUENTE_2][5];
extern const char qMay2[ALTO_ESTANDAR_LETRA_FUENTE_2][5];
extern const char rMay2[ALTO_ESTANDAR_LETRA_FUENTE_2][5];
extern const char sMay2[ALTO_ESTANDAR_LETRA_FUENTE_2][5];
extern const char tMay2[ALTO_ESTANDAR_LETRA_FUENTE_2][5];
extern const char uMay2[ALTO_ESTANDAR_LETRA_FUENTE_2][5];
extern const char vMay2[ALTO_ESTANDAR_LETRA_FUENTE_2][5];
extern const char wMay2[ALTO_ESTANDAR_LETRA_FUENTE_2][5];
extern const char xMay2[ALTO_ESTANDAR_LETRA_FUENTE_2][5];
extern const char yMay2[ALTO_ESTANDAR_LETRA_FUENTE_2][5];
extern const char zMay2[ALTO_ESTANDAR_LETRA_FUENTE_2][5];
extern const char espacio2[ALTO_ESTANDAR_LETRA_FUENTE_2][2];
extern const char cero2[ALTO_ESTANDAR_LETRA_FUENTE_2][4];
extern const char uno2[ALTO_ESTANDAR_LETRA_FUENTE_2][3];
extern const char dos2[ALTO_ESTANDAR_LETRA_FUENTE_2][4];
extern const char tres2[ALTO_ESTANDAR_LETRA_FUENTE_2][4];
extern const char cuatro2[ALTO_ESTANDAR_LETRA_FUENTE_2][5];
extern const char cinco2[ALTO_ESTANDAR_LETRA_FUENTE_2][4];
extern const char seis2[ALTO_ESTANDAR_LETRA_FUENTE_2][4];
extern const char siete2[ALTO_ESTANDAR_LETRA_FUENTE_2][4];
extern const char ocho2[ALTO_ESTANDAR_LETRA_FUENTE_2][4];
extern const char nueve2[ALTO_ESTANDAR_LETRA_FUENTE_2][4];
extern const char dosPuntos2[ALTO_ESTANDAR_LETRA_FUENTE_2][2];

//Fuente 1  Faltan caracteres =
//                              a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,
//                              1,2,3,4,5,6,7,8,9,0
extern const tCaracter fuente1[CANTIDAD_DE_CARACTERES];
extern const tCaracter fuente2[CANTIDAD_DE_CARACTERES];

void caracterDibujar(const tCaracter *carac, tCursorTexto *cursor, int color);    //Dibuja un caracter a partir de darle un tCaracter como parámetro
int obtenerIndice(char caracter);                   //Si le das un char, devuelve el indice correspondiente del vector fuente
void caracterDibujarChar(char carac, tCursorTexto *cursor, int color, int tipoFuente);            //Dibuja un caracter a partir de darle un char como parámetro
void escribirTexto(const char str[], tCursorTexto *cursor, int color, int tipoFuente);
void escribirNumero(int numero, tCursorTexto *cursor, int color, int tipoFuente);
void caracterDibujarEscalado(char carac, tCursorTexto *cursor, int color, int escala);

#endif // TEXTO_H_INCLUDED
