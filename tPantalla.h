#ifndef TPANTALLA_H_INCLUDED
#define TPANTALLA_H_INCLUDED

#include <stdio.h>
#include "tBoton.h"
#include "tGrilla.h"
#include "tJugador.h"

//Resoluciones
#define ANCHO_VENTANA_CGA 320
#define ALTO_VENTANA_CGA 200
#define ANCHO_VENTANA_VGA 640
#define ALTO_VENTANA_VGA 480
#define ESCALA_VENTANA 2

//Estado de juego
#define PANTALLA_INICIAL 1
#define MENU_PRINCIPAL_CLASSIC 2
#define MENU_PRINCIPAL_DELUXE 3
#define JUGANDO 4
#define PAUSA 5
#define GAME_OVER 6
#define CONFIGURACION 7
#define INGRESO_NOMBRE 8
#define CONFIG_DELUXE 9
#define SALIR_DEL_JUEGO 0

//Datos del juego
<<<<<<< HEAD
#define VEL_CAIDA_DEFAULT 1.0   //Segundos hasta que el tetromino baja un cuadrado
#define SIN_INFORMACION -1      //Para cuadros de texto sin parametro numerico
=======
#define VEL_CAIDA_DEFAULT 1 //Cantidad de segundos (tipo de dato double) hasta que se desencade que el tetromin baje un cuadrado
#define SIN_INFORMACION -1  //Se pone en los cuadros de texto cuando dicho cuadro no necesita mostrar ningun parametro
>>>>>>> bafd173e0d91aff7488c7bdf4932643df57b838d

#define IZQUIERDA -1
#define DERECHA 1
#define ANTIHORARIO -1
#define HORARIO 1
#define VEL_NORMAL 0
#define VEL_RAPIDA 1
#define FACTOR_VEL_RAPIDA 10

int pantallaInicial(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce);
int menuPrincipalClassic(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce);
int menuPrincipalDeluxe(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce);
int interfazJuego(int resolAncho, int resolAlto, tTetromino tetroActivo[TAM_VEC_TETROMINOS], tGrilla *grilla, tGBT_Temporizador **tempCaida, tGBT_Temporizador **tempInactiv, double *velActual, int *modoVelocidad);
int menuPausa(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce);
int gameOver(int resolAncho, int resolAlto);
int menuConfiguracion(int resolAncho, int resolAlto);
<<<<<<< HEAD
int ingresarNombre(int resolAncho, int resolAlto, char nombreOut[MAX_NOMBRE]);
int menuConfigDeluxe(int resolAncho, int resolAlto, int *anchoGrilla);

void infoInterfazDeJuego(int lineas, int puntaje, int puntajeMax, int nivel, char sigTetromino, int resolAncho, int resolAlto);
void dibujarRectangulo(int posX, int posY, int ancho, int alto, int color);
void dibujarCuadroTexto(int posX, int posY, const char str[], int parametro, int ancho, int alto, int colorCuadro, int colorTexto);
=======
void infoInterfazDeJuego(int lineas, int puntaje, int puntajeMax, int nivel, char sigTetromino, int resolAncho, int resolAlto);
void dibujarRectangulo(int posX, int posY, int ancho, int alto, int color);
void dibujarCuadroTexto(int posX, int posY, const char str[], int parametro, int ancho, int alto, int colorCuadro, int colorTexto); //Dibujar un rectangulo con las medidas especificadas, en la posicion dada y color dado. Escribe el parametro numerico, si este vale SIN_INFORMACION no se escribe ningun numero
>>>>>>> bafd173e0d91aff7488c7bdf4932643df57b838d

#endif // TPANTALLA_H_INCLUDED
