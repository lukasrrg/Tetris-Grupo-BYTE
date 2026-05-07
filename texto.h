#ifndef TEXTO_H_INCLUDED
#define TEXTO_H_INCLUDED

#include "lib/GBT_v2026.1C.01/include/GBT/gbt.h"
#include <string.h>

#define ALTO_ESTANDAR_LETRA 8
#define ESPACIADO_ENTRE_LETRAS 1
#define CANTIDAD_DE_CARACTERES 27
#define ESCALA_TITULO 3

typedef struct
{
    int espaciado;          //Cantidad de pixeles de ancho
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


//Fuente 1  Faltan caracteres =
//                              a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,
//                              1,2,3,4,5,6,7,8,9,0
extern const tCaracter fuente1[CANTIDAD_DE_CARACTERES];

void caracterDibujar(const tCaracter *carac, tCursorTexto *cursor, int color);    //Dibuja un caracter a partir de darle un tCaracter como parámetro
int obtenerIndice(char caracter);                   //Si le das un char, devuelve el indice correspondiente del vector fuente
void caracterDibujarChar(char carac, tCursorTexto *cursor, int color);            //Dibuja un caracter a partir de darle un char como parámetro
void escribirTexto(const char str[], tCursorTexto *cursor, int color);
void caracterDibujarEscalado(char carac, tCursorTexto *cursor, int color, int escala);

#endif // TEXTO_H_INCLUDED
