//INTEGRANTES:
//Apellido y nombres: Ramirez, Lucas
//DNI: 39347109
//Usuario: lukasrrg
//Entrega: Si
//
//Apellido y nombres: Varela, Lucas Sebastian
//DNI: 36756277
//Usuario: lucasvarela93
//Entrega: Si
//
//Apellido y nombres: Colombini, Donato
//DNI: 46753332
//Usuario: Donato2405
//Entrega: Si

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "lib/GBT_v2026.1C.01/include/GBT/gbt.h"

#include "paleta.h"
#include "texto.h"
#include "tPantalla.h"
#include "tGrilla.h"
#include "tJugador.h"

//Codigos de errores
#define TODO_OK 0
#define ERROR_MEMORIA_GRILLA    -333
#define ERROR_INICIAR_GBT       -148
#define ERROR_ABRIENDO_VENTANA  -3000
#define ERROR_APLICANDO_PALETA  -666
#define ERROR_CREAR_TEMPORIZADOR 1234


int main(int argc, char *argv[])
{
    int estadoDeJuego = PANTALLA_INICIAL;
    int resolAncho = ANCHO_VENTANA_CGA, resolAlto = ALTO_VENTANA_CGA;
    int anchoGrilla = ANCHO_GRILLA_DEFAULT;
    bool modoDeluxe = false;
    char nombreJugador[MAX_NOMBRE];

    if (argc > 2)
        printf("Demasiados argumentos. No soportado. El juego se iniciara en resolucion CGA.\n");
    else if (argc == 2)
    {
        if (strcmp(argv[1], "vga") == 0 || strcmp(argv[1], "VGA") == 0)
        {
            printf("Iniciando el juego en resolucion VGA (640x480).\n");
            resolAlto = ALTO_VENTANA_VGA;
            resolAncho = ANCHO_VENTANA_VGA;
        }
        else if (strcmp(argv[1], "cga") == 0 || strcmp(argv[1], "CGA") == 0)
            printf("Iniciando el juego en resolucion CGA (320x200).\n");
        else
            printf("Los argumentos validos son 'vga' o 'cga'. El juego se iniciara en resolucion CGA.\n");
    }
    else
        printf("Iniciando el juego en resolucion CGA (320x200).\n");


    if (gbt_iniciar() != 0)
    {
        fprintf(stderr, "Error al iniciar GBT: %s\n", gbt_obtener_log());
        return ERROR_INICIAR_GBT;
    }

    if (gbt_aplicar_paleta(paletaCGA, CANT_COLORES, GBT_FORMATO_888) != 0)
    {
        fprintf(stderr, "Error al aplicar la nueva paleta de colores: %s\n", gbt_obtener_log());
        return ERROR_APLICANDO_PALETA;
    }

    char nombreVentana[128];
    sprintf(nombreVentana, "Ventana %dx%d", resolAncho, resolAlto);

    if (gbt_crear_ventana(nombreVentana, resolAncho, resolAlto, ESCALA_VENTANA) != 0)
    {
        fprintf(stderr, "Error al iniciar el modulo de graficos de GBT: %s\n", gbt_obtener_log());
        return ERROR_ABRIENDO_VENTANA;
    }

    srand(time(0));


    tGrilla grillaDeFondo;
    if (!grillaCrear(&grillaDeFondo, resolAncho, resolAlto, anchoGrilla))
    {
        return ERROR_MEMORIA_GRILLA;
    }

    int cursorBoton;

    double velActual = VEL_CAIDA_DEFAULT;
    int modoVelocidad = VEL_NORMAL;

    tGBT_Temporizador *tempCaida = gbt_temporizador_crear(velActual);
    if (!tempCaida)
        return ERROR_CREAR_TEMPORIZADOR;
    gbt_temporizador_pausar(tempCaida);

    tGBT_Temporizador *tempInactiv = gbt_temporizador_crear(VEL_CAIDA_DEFAULT);
    if (!tempInactiv)
        return ERROR_CREAR_TEMPORIZADOR;
    gbt_temporizador_pausar(tempInactiv);

    tTetromino tetroActivos[TAM_VEC_TETROMINOS];
    bool partidaNueva = true;
    int cantTetrominos = CANT_TETROMINOS_CLASSIC;

    while(estadoDeJuego)
    {
        switch (estadoDeJuego)
        {
            case PANTALLA_INICIAL:
                cursorBoton = 0;
                tBoton botonesPantallaInicial[3];
                botonCrear(&botonesPantallaInicial[0], APUNTADO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_GRANDE)/2, (resolAlto - ALTO_BOTON_DEFAULT)/2, B, AM, "MODO CLASSIC", N);
                botonCrear(&botonesPantallaInicial[1], INACTIVO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_GRANDE)/2, (resolAlto + ALTO_BOTON_DEFAULT)/2 + SEPARACION_ENTRE_BOTON, B, VE, "MODO DELUXE", N);
                botonCrear(&botonesPantallaInicial[2], INACTIVO, ANCHO_BOTON_CHICO,  ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_CHICO)/2,  (resolAlto + 3*ALTO_BOTON_DEFAULT)/2 + SEPARACION_ENTRE_BOTON*2, B, R, "SALIR", N);
                while (estadoDeJuego == PANTALLA_INICIAL)
                    estadoDeJuego = pantallaInicial(resolAncho, resolAlto, &cursorBoton, botonesPantallaInicial, 3);
                partidaNueva = true;
                break;

            case MENU_PRINCIPAL_CLASSIC:
                cursorBoton = 0;
                modoDeluxe = false;
                cantTetrominos = CANT_TETROMINOS_CLASSIC;
                tBoton botonesMenuPrincipalClassic[4];
                int pasoC = ALTO_BOTON_DEFAULT + SEPARACION_ENTRE_BOTON;
                int totalAltoC = 4*ALTO_BOTON_DEFAULT + 3*SEPARACION_ENTRE_BOTON;
                int baseYC = (resolAlto - totalAltoC) / 2;
                botonCrear(&botonesMenuPrincipalClassic[0], APUNTADO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_GRANDE)/2, baseYC,           B, AM, "NUEVA PARTIDA",  N);
                botonCrear(&botonesMenuPrincipalClassic[1], INACTIVO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_GRANDE)/2, baseYC + pasoC,   B, AM, "CARGAR PARTIDA", N);
                botonCrear(&botonesMenuPrincipalClassic[2], INACTIVO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_GRANDE)/2, baseYC + 2*pasoC, B, VE, "CONFIGURACION",  N);
                botonCrear(&botonesMenuPrincipalClassic[3], INACTIVO, ANCHO_BOTON_CHICO,  ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_CHICO)/2,  baseYC + 3*pasoC, B, R,  "ATRAS",          N);
                while(estadoDeJuego == MENU_PRINCIPAL_CLASSIC)
                    estadoDeJuego = menuPrincipalClassic(resolAncho, resolAlto, &cursorBoton, botonesMenuPrincipalClassic, 4);
                break;

            case MENU_PRINCIPAL_DELUXE:
                cursorBoton = 0;
                modoDeluxe = true;
                cantTetrominos = CANT_TETROMINOS_DELUXE;
                tBoton botonesMenuPrincipalDeluxe[4];
                int pasoD = ALTO_BOTON_DEFAULT + SEPARACION_ENTRE_BOTON;
                int totalAltoD = 4*ALTO_BOTON_DEFAULT + 3*SEPARACION_ENTRE_BOTON;
                int baseYD = (resolAlto - totalAltoD) / 2;
                botonCrear(&botonesMenuPrincipalDeluxe[0], APUNTADO, ANCHO_BOTON_GRANDE,  ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_GRANDE)/2,  baseYD,           B, AM, "NUEVA PARTIDA",  N);
                botonCrear(&botonesMenuPrincipalDeluxe[1], INACTIVO, ANCHO_BOTON_MEDIANO, ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_MEDIANO)/2, baseYD + pasoD,   B, AM, "CARGAR PARTIDA", N);
                botonCrear(&botonesMenuPrincipalDeluxe[2], INACTIVO, ANCHO_BOTON_MEDIANO, ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_MEDIANO)/2, baseYD + 2*pasoD, B, VE, "CONFIGURACION",  N);
                botonCrear(&botonesMenuPrincipalDeluxe[3], INACTIVO, ANCHO_BOTON_CHICO,   ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_CHICO)/2,   baseYD + 3*pasoD, B, R,  "ATRAS",          N);
                while(estadoDeJuego == MENU_PRINCIPAL_DELUXE)
                    estadoDeJuego = menuPrincipalDeluxe(resolAncho, resolAlto, &cursorBoton, botonesMenuPrincipalDeluxe, 4);
                break;

            case JUGANDO:
                if (partidaNueva)
                {
                    tetrominoCargarVector(tetroActivos, cantTetrominos);
                    grillaDestruir(&grillaDeFondo);
                    grillaCrear(&grillaDeFondo, resolAncho, resolAlto, modoDeluxe ? anchoGrilla : ANCHO_GRILLA_DEFAULT);
                    partidaNueva = false;
                }
                gbt_temporizador_reanudar(tempCaida);
                while (estadoDeJuego == JUGANDO)
                    estadoDeJuego = interfazJuego(resolAncho, resolAlto, tetroActivos, &grillaDeFondo, &tempCaida, &tempInactiv, &velActual, &modoVelocidad);
                break;

            case PAUSA:
                gbt_temporizador_pausar(tempCaida);
                cursorBoton = 0;
                tBoton botonesMenuPausa[5];
                int pasoP = ALTO_BOTON_DEFAULT + SEPARACION_ENTRE_BOTON;
                int totalAltoP = 5*ALTO_BOTON_DEFAULT + 4*SEPARACION_ENTRE_BOTON;
                int baseYP = (resolAlto - totalAltoP) / 2;
                botonCrear(&botonesMenuPausa[0], APUNTADO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_GRANDE)/2, baseYP,           B, VE, "REANUDAR",       N);
                botonCrear(&botonesMenuPausa[1], INACTIVO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_GRANDE)/2, baseYP + pasoP,   B, AM, "CARGAR PARTIDA", N);
                botonCrear(&botonesMenuPausa[2], INACTIVO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_GRANDE)/2, baseYP + 2*pasoP, B, AM, "GUARDAR PARTIDA",N);
                botonCrear(&botonesMenuPausa[3], INACTIVO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_GRANDE)/2, baseYP + 3*pasoP, B, RB, "CHEAT",          N);
                botonCrear(&botonesMenuPausa[4], INACTIVO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_GRANDE)/2, baseYP + 4*pasoP, B, R,  "SALIR AL MENU",  N);
                while (estadoDeJuego == PAUSA)
                    estadoDeJuego = menuPausa(resolAncho, resolAlto, &cursorBoton, botonesMenuPausa, 5);
                if (estadoDeJuego == JUGANDO)
                    gbt_temporizador_reanudar(tempCaida);
                break;

            case INGRESO_NOMBRE:
                while (estadoDeJuego == INGRESO_NOMBRE)
                    estadoDeJuego = ingresarNombre(resolAncho, resolAlto, nombreJugador);
                break;

            case CONFIG_DELUXE:
                while (estadoDeJuego == CONFIG_DELUXE)
                    estadoDeJuego = menuConfigDeluxe(resolAncho, resolAlto, &anchoGrilla);
                break;
        }
    }

    gbt_temporizador_destruir(tempCaida);
    gbt_temporizador_destruir(tempInactiv);
    grillaDestruir(&grillaDeFondo);
    gbt_destruir_ventana();
    gbt_cerrar();

    return 0;
}
