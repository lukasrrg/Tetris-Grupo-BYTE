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
#include "vectores_matrices.h"
#include "tOpciones.h"
#include "tPartida.h"


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
    int infoJuego[CANT_TETROMINOS_DELUXE + DATOS_DE_JUEGO];
    int anchoGrilla;
    char nombreJugador[MAX_NOMBRE];
    double velActual = VEL_CAIDA_DEFAULT;
    tOpciones op;
    opcionesCargar(&op); //Cargar opciones guardadas
    infoJuego[RESOL_ANCHO] = op.resolAncho;
    infoJuego[RESOL_ALTO] = op.resolAlto;
    velActual = op.velCaida;
    anchoGrilla = op.anchoGrilla;

    if (argc > 2)           //Chequea los argumentos a main
        printf("Demasiados argumentos. No soportado. El juego se iniciara en resolucion CGA.\n");
    else if (argc == 2)
    {
        if (strcmp(argv[1], "vga") == 0 || strcmp(argv[1], "VGA") == 0)
        {
            printf("Iniciando el juego en resolucion VGA (640x480).\n");
            infoJuego[RESOL_ALTO] = ALTO_VENTANA_VGA;
            infoJuego[RESOL_ANCHO] = ANCHO_VENTANA_VGA;
        }
        else if (strcmp(argv[1], "cga") == 0 || strcmp(argv[1], "CGA") == 0)
            printf("Iniciando el juego en resolucion CGA (320x200).\n");
        else
            printf("Los argumentos validos son 'vga' o 'cga'. El juego se iniciara en resolucion CGA.\n");
    }
    else
        printf("Iniciando el juego en resolucion %dx%d.\n", infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO]);


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
    sprintf(nombreVentana, "Ventana %dx%d", infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO]);

    if (gbt_crear_ventana(nombreVentana, infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO], ESCALA_VENTANA) != 0)
    {
        fprintf(stderr, "Error al iniciar el modulo de graficos de GBT: %s\n", gbt_obtener_log());
        return ERROR_ABRIENDO_VENTANA;
    }

    srand(time(0));

    tGrilla grillaDeFondo;
    if (!grillaCrear(&grillaDeFondo, infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO], anchoGrilla))
    {
        return ERROR_MEMORIA_GRILLA;
    }

    int cursorBoton;
    int modoVelocidad = VEL_NORMAL;
    tGBT_Temporizador *tempCaida = gbt_temporizador_crear(velActual);    //Inicialización del temporizador para la caida
    if (!tempCaida)
        return ERROR_CREAR_TEMPORIZADOR;
    gbt_temporizador_pausar(tempCaida);
    tGBT_Temporizador *tempFijacion = gbt_temporizador_crear(VEL_CAIDA_DEFAULT);    //Inicialización del temporizador para inactivar tetromino
    if (!tempFijacion)
        return ERROR_CREAR_TEMPORIZADOR;
    gbt_temporizador_pausar(tempFijacion);                          //Se lo pausa ya que todavia no sera utilizado

    tTetromino tetroActivos[TAM_VEC_TETROMINOS];        //Fila de tetrominos que van a entrar en juego
    bool partidaNueva = true;

    tPartida partida;           //Estructura partida que se encargara de manejar los guardados y cargados de partidas

    while(estadoDeJuego)
    {
        switch (estadoDeJuego)
        {
        case PANTALLA_INICIAL:
            cursorBoton = 0;
            tBoton botonesPantallaInicial[3];
            botonCrear(&botonesPantallaInicial[0], APUNTADO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (infoJuego[RESOL_ANCHO] - ANCHO_BOTON_GRANDE)/2, (infoJuego[RESOL_ALTO] - ALTO_BOTON_DEFAULT)/2, B, AM, "MODO CLASSIC", N);
            botonCrear(&botonesPantallaInicial[1], INACTIVO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (infoJuego[RESOL_ANCHO] - ANCHO_BOTON_GRANDE)/2, (infoJuego[RESOL_ALTO] + ALTO_BOTON_DEFAULT)/2 + SEPARACION_ENTRE_BOTON, B, VE, "MODO DELUXE", N);
            botonCrear(&botonesPantallaInicial[2], INACTIVO, ANCHO_BOTON_CHICO,  ALTO_BOTON_DEFAULT, (infoJuego[RESOL_ANCHO] - ANCHO_BOTON_CHICO)/2,  (infoJuego[RESOL_ALTO] + 3*ALTO_BOTON_DEFAULT)/2 + SEPARACION_ENTRE_BOTON*2, B, R, "SALIR", N);
            while (estadoDeJuego == PANTALLA_INICIAL)
                estadoDeJuego = pantallaInicial(infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO], &cursorBoton, botonesPantallaInicial, 3);
            partidaNueva = true;
            break;

        case MENU_PRINCIPAL_CLASSIC:
            cursorBoton = 0;
            infoJuego[MODO_DE_JUEGO] = MODO_CLASSIC;
            tBoton botonesMenuPrincipalClassic[4];
            int pasoC = ALTO_BOTON_DEFAULT + SEPARACION_ENTRE_BOTON;
            int totalAltoC = 4*ALTO_BOTON_DEFAULT + 3*SEPARACION_ENTRE_BOTON;
            int baseYC = (infoJuego[RESOL_ALTO] - totalAltoC) / 2;
            botonCrear(&botonesMenuPrincipalClassic[0], APUNTADO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (infoJuego[RESOL_ANCHO] - ANCHO_BOTON_GRANDE)/2, baseYC,           B, AM, "NUEVA PARTIDA",  N);
            botonCrear(&botonesMenuPrincipalClassic[1], INACTIVO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (infoJuego[RESOL_ANCHO] - ANCHO_BOTON_GRANDE)/2, baseYC + pasoC,   B, AM, "CARGAR PARTIDA", N);
            botonCrear(&botonesMenuPrincipalClassic[2], INACTIVO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (infoJuego[RESOL_ANCHO] - ANCHO_BOTON_GRANDE)/2, baseYC + 2*pasoC, B, VE, "OPCIONES",  N);
            botonCrear(&botonesMenuPrincipalClassic[3], INACTIVO, ANCHO_BOTON_CHICO,  ALTO_BOTON_DEFAULT, (infoJuego[RESOL_ANCHO] - ANCHO_BOTON_CHICO)/2,  baseYC + 3*pasoC, B, R,  "ATRAS",          N);
            while(estadoDeJuego == MENU_PRINCIPAL_CLASSIC)
                estadoDeJuego = menuPrincipalClassic(infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO], &cursorBoton, botonesMenuPrincipalClassic, 4);
            break;

        case MENU_PRINCIPAL_DELUXE:
            cursorBoton = 0;
            infoJuego[MODO_DE_JUEGO] = MODO_DELUXE;
            tBoton botonesMenuPrincipalDeluxe[4];
            int pasoD = ALTO_BOTON_DEFAULT + SEPARACION_ENTRE_BOTON;
            int totalAltoD = 4*ALTO_BOTON_DEFAULT + 3*SEPARACION_ENTRE_BOTON;
            int baseYD = (infoJuego[RESOL_ALTO] - totalAltoD) / 2;
            botonCrear(&botonesMenuPrincipalDeluxe[0], APUNTADO, ANCHO_BOTON_GRANDE,  ALTO_BOTON_DEFAULT, (infoJuego[RESOL_ANCHO] - ANCHO_BOTON_GRANDE)/2,  baseYD,           B, AM, "NUEVA PARTIDA",  N);
            botonCrear(&botonesMenuPrincipalDeluxe[1], INACTIVO, ANCHO_BOTON_MEDIANO, ALTO_BOTON_DEFAULT, (infoJuego[RESOL_ANCHO] - ANCHO_BOTON_MEDIANO)/2, baseYD + pasoD,   B, AM, "CARGAR PARTIDA", N);
            botonCrear(&botonesMenuPrincipalDeluxe[2], INACTIVO, ANCHO_BOTON_MEDIANO, ALTO_BOTON_DEFAULT, (infoJuego[RESOL_ANCHO] - ANCHO_BOTON_MEDIANO)/2, baseYD + 2*pasoD, B, VE, "OPCIONES",  N);
            botonCrear(&botonesMenuPrincipalDeluxe[3], INACTIVO, ANCHO_BOTON_CHICO,   ALTO_BOTON_DEFAULT, (infoJuego[RESOL_ANCHO] - ANCHO_BOTON_CHICO)/2,   baseYD + 3*pasoD, B, R,  "ATRAS",          N);
            while(estadoDeJuego == MENU_PRINCIPAL_DELUXE)
                estadoDeJuego = menuPrincipalDeluxe(infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO], &cursorBoton, botonesMenuPrincipalDeluxe, 4);
            break;

        case JUGANDO:
            if (partidaNueva)
            {
                tetrominoCargarVector(tetroActivos, infoJuego[MODO_DE_JUEGO] ? CANT_TETROMINOS_DELUXE : CANT_TETROMINOS_CLASSIC);
                infoJuego[LINEAS] = 0;
                infoJuego[SCORE] = 0;
                infoJuego[TOP_SCORE] = 0;   //TODO: Hay que consultar previamente en los archivos guardados cual fue el top score
                infoJuego[NIVEL] = 1;
                grillaDestruir(&grillaDeFondo);
                grillaCrear(&grillaDeFondo, infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO], infoJuego[MODO_DE_JUEGO] ? anchoGrilla : ANCHO_GRILLA_DEFAULT);
                partidaNueva = false;
            }
//            vectorInfoJuego[RESOL_ANCHO] = resolAncho;
//            vectorInfoJuego[RESOL_ALTO] = resolAlto;
            gbt_temporizador_reanudar(tempCaida);
            while (estadoDeJuego == JUGANDO)
                estadoDeJuego = interfazJuego(infoJuego, tetroActivos, &grillaDeFondo, &tempCaida, &tempFijacion, &velActual, &modoVelocidad);
            break;
        case PAUSA:
            gbt_temporizador_pausar(tempCaida);
            cursorBoton = 0;
            tBoton botonesMenuPausa[5];
            int pasoP = ALTO_BOTON_DEFAULT + SEPARACION_ENTRE_BOTON;
            int totalAltoP = 5*ALTO_BOTON_DEFAULT + 4*SEPARACION_ENTRE_BOTON;
            int baseYP = (infoJuego[RESOL_ALTO] - totalAltoP) / 2;
            botonCrear(&botonesMenuPausa[0], APUNTADO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (infoJuego[RESOL_ANCHO] - ANCHO_BOTON_GRANDE)/2, baseYP,           B, VE, "REANUDAR",       N);
            botonCrear(&botonesMenuPausa[1], INACTIVO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (infoJuego[RESOL_ANCHO] - ANCHO_BOTON_GRANDE)/2, baseYP + pasoP,   B, AM, "CARGAR PARTIDA", N);
            botonCrear(&botonesMenuPausa[2], INACTIVO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (infoJuego[RESOL_ANCHO] - ANCHO_BOTON_GRANDE)/2, baseYP + 2*pasoP, B, AM, "GUARDAR PARTIDA",N);
            botonCrear(&botonesMenuPausa[3], INACTIVO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (infoJuego[RESOL_ANCHO] - ANCHO_BOTON_GRANDE)/2, baseYP + 3*pasoP, B, RB, "CHEAT",          N);
            botonCrear(&botonesMenuPausa[4], INACTIVO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (infoJuego[RESOL_ANCHO] - ANCHO_BOTON_GRANDE)/2, baseYP + 4*pasoP, B, R,  "SALIR AL MENU",  N);
            while (estadoDeJuego == PAUSA)
                estadoDeJuego = menuPausa(infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO], &cursorBoton, botonesMenuPausa, 5);
            break;

        case INGRESO_NOMBRE:
            while (estadoDeJuego == INGRESO_NOMBRE)
                estadoDeJuego = ingresarNombre(infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO], nombreJugador);
            break;
        case GAME_OVER:
            while (estadoDeJuego == GAME_OVER)
                estadoDeJuego = gameOver(infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO]);
            break;
        case OPCIONES:
        {
            int resolAnchoAntes = infoJuego[RESOL_ANCHO];

            while (estadoDeJuego == OPCIONES)
                estadoDeJuego = menuOpciones(infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO], &infoJuego[RESOL_ANCHO], &infoJuego[RESOL_ALTO], &velActual, &anchoGrilla, infoJuego[MODO_DE_JUEGO]);
            if (infoJuego[RESOL_ANCHO] != resolAnchoAntes)
            {
                gbt_destruir_ventana();
                char nombreVentana[128];
                sprintf(nombreVentana, "Ventana %dx%d", infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO]);
                if (gbt_crear_ventana(nombreVentana, infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO], ESCALA_VENTANA) != 0)
                {
                    fprintf(stderr, "Error al recrear la ventana: %s\n", gbt_obtener_log());
                    return ERROR_ABRIENDO_VENTANA;
                }
                grillaDestruir(&grillaDeFondo);
                if (!grillaCrear(&grillaDeFondo, infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO], anchoGrilla))
                    return ERROR_MEMORIA_GRILLA;
            }

            gbt_temporizador_destruir(tempCaida);
            tempCaida = gbt_temporizador_crear(velActual);
            if (!tempCaida)
                return ERROR_CREAR_TEMPORIZADOR;
            gbt_temporizador_pausar(tempCaida);
            break;
        }

        case GUARDAR_PARTIDA:
        {

            strcpy(partida.nombre, nombreJugador);
            partida.puntaje     = infoJuego[SCORE];
            partida.lineas      = infoJuego[LINEAS];
            partida.nivel       = infoJuego[NIVEL];
            partida.velCaida    = velActual;
            partida.anchoGrilla = anchoGrilla;
            partida.modoDeluxe  = infoJuego[MODO_DE_JUEGO];
            memcpy(partida.tetrominos, tetroActivos, sizeof(tetroActivos));
            partidaSerializarGrilla(&partida, &grillaDeFondo);
            partidaGuardar(&partida);
            estadoDeJuego = PAUSA;
            break;
        }

        case CARGAR_PARTIDA:
        {
            if (partidaCargar(nombreJugador, infoJuego[MODO_DE_JUEGO], &partida))
            {
                infoJuego[SCORE] = partida.puntaje;
                infoJuego[LINEAS] = partida.lineas;
                infoJuego[NIVEL] = partida.nivel;
                velActual = partida.velCaida;
                anchoGrilla = partida.modoDeluxe ? partida.anchoGrilla : ANCHO_GRILLA_DEFAULT;
                infoJuego[MODO_DE_JUEGO] = partida.modoDeluxe;
                memcpy(tetroActivos, partida.tetrominos, sizeof(tetroActivos));

                grillaDestruir(&grillaDeFondo);
                grillaCrear(&grillaDeFondo, infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO], anchoGrilla);
                partidaRestaurarGrilla(&partida, &grillaDeFondo, infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO]);

                gbt_temporizador_destruir(tempCaida);
                tempCaida = gbt_temporizador_crear(velActual);
                if (!tempCaida)
                    return ERROR_CREAR_TEMPORIZADOR;
                gbt_temporizador_pausar(tempCaida);

                partidaNueva = false;
                estadoDeJuego = JUGANDO;
            }
            else
                estadoDeJuego = infoJuego[MODO_DE_JUEGO] ? MENU_PRINCIPAL_DELUXE : MENU_PRINCIPAL_CLASSIC;
            break;
        }

        case INGRESO_NOMBRE_CARGA:
            while (estadoDeJuego == INGRESO_NOMBRE_CARGA)
                estadoDeJuego = ingresarNombreCarga(infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO], nombreJugador, infoJuego[MODO_DE_JUEGO]);
            break;
        }
    }

    gbt_temporizador_destruir(tempCaida);
    gbt_temporizador_destruir(tempFijacion);
    grillaDestruir(&grillaDeFondo);
    gbt_destruir_ventana();
    gbt_cerrar();

    return 0;
}
