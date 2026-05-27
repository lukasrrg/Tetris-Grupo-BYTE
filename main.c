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
    int estadoDeJuego = PANTALLA_INICIAL;               //Esta variable establece que pantalla se debe estar mostrando en cada momento
    int infoJuego[CANT_TETROMINOS_DELUXE + DATOS_DE_JUEGO];      //En este vector se guarda toda la data que sirve para correr el juego
    int i;
    int escala = ESCALA_VENTANA_DEFAULT;

    for (i = 0; i < CANT_TETROMINOS_DELUXE; i++)  //En las primeras posiciones de este vector se guardan las cantidades de cada tetromino colocados, se inicializa en 0
        infoJuego[i] = 0;

    int anchoGrilla;
    char nombreJugador[MAX_NOMBRE];
    double velActual = VEL_CAIDA_DEFAULT;
    tOpciones op;
    opcionesCargar(&op); //Cargar opciones guardadas
    infoJuego[RESOL_ANCHO] = op.resolAncho;
    infoJuego[RESOL_ALTO] = op.resolAlto;
    velActual = op.velCaida;
    anchoGrilla = op.anchoGrilla;

    verificarArgumentos(argc, argv, &infoJuego[RESOL_ANCHO], &infoJuego[RESOL_ALTO], &escala);  //Verifica los argumentos a main y ademas los carga

    if (gbt_iniciar() != 0)
    {
        fprintf(stderr, "Error al iniciar GBT: %s\n", gbt_obtener_log());
        return ERROR_INICIAR_GBT;
    }

    if (gbt_aplicar_paleta(paletaCLASICA, CANT_COLORES, GBT_FORMATO_888) != 0)
    {
        fprintf(stderr, "Error al aplicar la nueva paleta de colores: %s\n", gbt_obtener_log());
        return ERROR_APLICANDO_PALETA;
    }

    char nombreVentana[128];
    sprintf(nombreVentana, "Ventana %dx%d", infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO]);

    if (gbt_crear_ventana(nombreVentana, infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO], escala) != 0)
    {
        fprintf(stderr, "Error al iniciar el modulo de graficos de GBT: %s\n", gbt_obtener_log());
        return ERROR_ABRIENDO_VENTANA;
    }

    tamMino = (infoJuego[RESOL_ANCHO] >= 640) ? 16 : 8;  // escala los minos segun resolucion

    srand(time(0));

    tGrilla grillaDeFondo;
    if (!grillaCrear(&grillaDeFondo, anchoGrilla, ALTO_GRILLA_TOTAL))
    {
        return ERROR_MEMORIA_GRILLA;
    }

    int cursorBoton;
    int estadoAnterior = PANTALLA_INICIAL;  // Rastrea de donde viene CARGAR_PARTIDA
    tGBT_Temporizador *tempCaida = gbt_temporizador_crear(velActual);    //Inicializaci�n del temporizador para la caida
    if (!tempCaida)
        return ERROR_CREAR_TEMPORIZADOR;
    gbt_temporizador_pausar(tempCaida);
    tGBT_Temporizador *tempFijacion = gbt_temporizador_crear(velActual/2);    //Inicializaci�n del temporizador para inactivar tetromino
    if (!tempFijacion)
        return ERROR_CREAR_TEMPORIZADOR;
    gbt_temporizador_pausar(tempFijacion);                          //Se lo pausa ya que todavia no sera utilizado
    tTetromino tetroActivos[TAM_VEC_TETROMINOS];        //Fila de tetrominos que van a entrar en juego
    bool partidaNueva = true;

    tPartida partida;           //Estructura partida que se encargara de manejar los guardados y cargados de partidas

    tGrilla grillaDecorativaSup;
    if(!grillaCrear(&grillaDecorativaSup, ANCHO_VENTANA_VGA/tamMino, 1))
    {
        return ERROR_MEMORIA_GRILLA;
    }
    grillaDecorativaSetear(&grillaDecorativaSup);

    tGrilla grillaDecorativaInf;
    if(!grillaCrear(&grillaDecorativaInf, ANCHO_VENTANA_VGA/tamMino, 3))
    {
        return ERROR_MEMORIA_GRILLA;
    }
    grillaDecorativaSetear(&grillaDecorativaInf);

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
                estadoDeJuego = pantallaInicial(infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO], &cursorBoton, botonesPantallaInicial, 3, &grillaDecorativaSup, &grillaDecorativaInf);
            partidaNueva = true;
            break;

        case MENU_PRINCIPAL_CLASSIC:
            partidaNueva = true;
            cursorBoton = 0;
            infoJuego[MODO_DE_JUEGO] = MODO_CLASSIC;
            tBoton botonesMenuPrincipalClassic[4];
            int pasoC = ALTO_BOTON_DEFAULT + SEPARACION_ENTRE_BOTON;
            int totalAltoC = 4*ALTO_BOTON_DEFAULT + 3*SEPARACION_ENTRE_BOTON;
            int baseYC = (infoJuego[RESOL_ALTO] - totalAltoC) / 2;
            botonCrear(&botonesMenuPrincipalClassic[0], APUNTADO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (infoJuego[RESOL_ANCHO] - ANCHO_BOTON_GRANDE)/2, baseYC,           B, AM, "NUEVA PARTIDA",  N);
            botonCrear(&botonesMenuPrincipalClassic[1], INACTIVO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (infoJuego[RESOL_ANCHO] - ANCHO_BOTON_GRANDE)/2, baseYC + pasoC,   B, NA, "CARGAR PARTIDA", N);
            botonCrear(&botonesMenuPrincipalClassic[2], INACTIVO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (infoJuego[RESOL_ANCHO] - ANCHO_BOTON_GRANDE)/2, baseYC + 2*pasoC, B, VE, "OPCIONES",  N);
            botonCrear(&botonesMenuPrincipalClassic[3], INACTIVO, ANCHO_BOTON_CHICO,  ALTO_BOTON_DEFAULT, (infoJuego[RESOL_ANCHO] - ANCHO_BOTON_CHICO)/2,  baseYC + 3*pasoC, B, R,  "ATRAS",          N);
            while(estadoDeJuego == MENU_PRINCIPAL_CLASSIC)
                estadoDeJuego = menuPrincipalClassic(infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO], &cursorBoton, botonesMenuPrincipalClassic, 4);
            break;

        case MENU_PRINCIPAL_DELUXE:
            partidaNueva = true;
            cursorBoton = 0;
            infoJuego[MODO_DE_JUEGO] = MODO_DELUXE;
            tBoton botonesMenuPrincipalDeluxe[4];
            int pasoD = ALTO_BOTON_DEFAULT + SEPARACION_ENTRE_BOTON;
            int totalAltoD = 4*ALTO_BOTON_DEFAULT + 3*SEPARACION_ENTRE_BOTON;
            int baseYD = (infoJuego[RESOL_ALTO] - totalAltoD) / 2;
            botonCrear(&botonesMenuPrincipalDeluxe[0], APUNTADO, ANCHO_BOTON_GRANDE,  ALTO_BOTON_DEFAULT, (infoJuego[RESOL_ANCHO] - ANCHO_BOTON_GRANDE)/2,  baseYD,           B, AM, "NUEVA PARTIDA",  N);
            botonCrear(&botonesMenuPrincipalDeluxe[1], INACTIVO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (infoJuego[RESOL_ANCHO] - ANCHO_BOTON_GRANDE)/2, baseYD + pasoD,   B, AM, "CARGAR PARTIDA", N);
            botonCrear(&botonesMenuPrincipalDeluxe[2], INACTIVO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (infoJuego[RESOL_ANCHO] - ANCHO_BOTON_GRANDE)/2, baseYD + 2*pasoD, B, VE, "OPCIONES",  N);
            botonCrear(&botonesMenuPrincipalDeluxe[3], INACTIVO, ANCHO_BOTON_CHICO,   ALTO_BOTON_DEFAULT, (infoJuego[RESOL_ANCHO] - ANCHO_BOTON_CHICO)/2,   baseYD + 3*pasoD, B, R,  "ATRAS",          N);
            while(estadoDeJuego == MENU_PRINCIPAL_DELUXE)
                estadoDeJuego = menuPrincipalDeluxe(infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO], &cursorBoton, botonesMenuPrincipalDeluxe, 4);
            break;

        case JUGANDO:
            if (partidaNueva)
            {
                for(i = 0; i < CANT_TETROMINOS_DELUXE; i++)
                {
                    infoJuego[i] = 0;
                }
                infoJuego[TETROMINOS_COLOCADOS] = 0;
                infoJuego[LINEAS] = 0;
                infoJuego[SCORE] = 0;
                infoJuego[TOP_SCORE] = jugadorObtenerPuntajeMax(nombreJugador);
                infoJuego[NIVEL] = 1;
                infoJuego[TETROMINO_LIBRE] = 1;
                infoJuego[CHEATS_ACTIVADOS] = 0;
                velActual = op.velCaida;
                gbt_temporizador_destruir(tempCaida);
                tempCaida = gbt_temporizador_crear(velActual);    //Inicializaci�n del temporizador para la caida
                gbt_temporizador_destruir(tempFijacion);
                tempFijacion = gbt_temporizador_crear(velActual/2);    //Inicializaci�n del temporizador para la fijacion
                if (!tempCaida || !tempFijacion)
                    return ERROR_CREAR_TEMPORIZADOR;
                gbt_temporizador_pausar(tempFijacion);
                grillaDestruir(&grillaDeFondo);
                grillaCrear(&grillaDeFondo, infoJuego[MODO_DE_JUEGO] ? anchoGrilla : ANCHO_GRILLA_DEFAULT, ALTO_GRILLA_TOTAL);
                tetrominoCargarVector(tetroActivos, infoJuego[MODO_DE_JUEGO] ? CANT_TETROMINOS_DELUXE : CANT_TETROMINOS_CLASSIC, grillaDeFondo.anchoGrilla);
                partidaNueva = false;
            }
            gbt_temporizador_reanudar(tempCaida);
            while (estadoDeJuego == JUGANDO)
                estadoDeJuego = interfazJuego(infoJuego, tetroActivos, &grillaDeFondo, &tempCaida, &tempFijacion, &velActual);
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
            botonCrear(&botonesMenuPausa[2], INACTIVO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (infoJuego[RESOL_ANCHO] - ANCHO_BOTON_GRANDE)/2, baseYP + 2*pasoP, B,  VI, "GUARDAR PARTIDA",N);
            botonCrear(&botonesMenuPausa[3], INACTIVO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (infoJuego[RESOL_ANCHO] - ANCHO_BOTON_GRANDE)/2, baseYP + 3*pasoP, B, RB, "CHEAT",          N);
            botonCrear(&botonesMenuPausa[4], INACTIVO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (infoJuego[RESOL_ANCHO] - ANCHO_BOTON_GRANDE)/2, baseYP + 4*pasoP, B,  R,  "SALIR AL MENU",  N);
            while (estadoDeJuego == PAUSA)
                estadoDeJuego = menuPausa(infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO], &cursorBoton, botonesMenuPausa, 5, &infoJuego[CHEATS_ACTIVADOS]);

            if (estadoDeJuego == CARGAR_PARTIDA)
                estadoAnterior = PAUSA;
            break;

        case INGRESO_NOMBRE:
            while (estadoDeJuego == INGRESO_NOMBRE)
                estadoDeJuego = ingresarNombre(infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO], nombreJugador);
            break;
        case GAME_OVER:
            int maxAnterior = jugadorObtenerPuntajeMax(nombreJugador);

            if (infoJuego[SCORE] > maxAnterior)
            {
                tJugador jugadorActual;

                strcpy(jugadorActual.nombre, nombreJugador);
                jugadorActual.puntaje_max = infoJuego[SCORE];

                jugadorGuardar(&jugadorActual);
            }
            cursorBoton = 0;
            tBoton botonesGameOver[3];
            int pasoGO = ALTO_BOTON_DEFAULT + SEPARACION_ENTRE_BOTON;
            int totalAltoGO = 3 * ALTO_BOTON_DEFAULT + 2 * SEPARACION_ENTRE_BOTON;

            int baseYGO = (infoJuego[RESOL_ALTO] - totalAltoGO) / 2 + 40;

            botonCrear(&botonesGameOver[0], APUNTADO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (infoJuego[RESOL_ANCHO] - ANCHO_BOTON_GRANDE)/2, baseYGO, B, VE, "REINICIAR", N);
            botonCrear(&botonesGameOver[1], INACTIVO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (infoJuego[RESOL_ANCHO] - ANCHO_BOTON_GRANDE)/2, baseYGO + pasoGO, B, AM, "CARGAR", N);
            botonCrear(&botonesGameOver[2], INACTIVO, ANCHO_BOTON_CHICO, ALTO_BOTON_DEFAULT, (infoJuego[RESOL_ANCHO] - ANCHO_BOTON_CHICO)/2, baseYGO + 2*pasoGO, B, R, "SALIR", N);

            while (estadoDeJuego == GAME_OVER) {
                estadoDeJuego = gameOver(infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO], &cursorBoton, botonesGameOver, 3, infoJuego[SCORE]);
            }
            if (estadoDeJuego == JUGANDO) {
                partidaNueva = true;
            }
            if (estadoDeJuego == CARGAR_PARTIDA)
                estadoAnterior = GAME_OVER;
            break;
        case OPCIONES:
        {
            int resolAnchoAntes = infoJuego[RESOL_ANCHO];
            while (estadoDeJuego == OPCIONES)
                estadoDeJuego = menuOpciones(infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO], &infoJuego[RESOL_ANCHO], &infoJuego[RESOL_ALTO], &op.velCaida, &anchoGrilla, infoJuego[MODO_DE_JUEGO]);
            if (infoJuego[RESOL_ANCHO] != resolAnchoAntes)
            {
                gbt_destruir_ventana();
                char nombreVentana[128];
                sprintf(nombreVentana, "Ventana %dx%d", infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO]);
                if (gbt_crear_ventana(nombreVentana, infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO], escala) != 0)
                {
                    fprintf(stderr, "Error al recrear la ventana: %s\n", gbt_obtener_log());
                    return ERROR_ABRIENDO_VENTANA;
                }
                grillaDestruir(&grillaDeFondo);
                if (!grillaCrear(&grillaDeFondo, anchoGrilla, ALTO_GRILLA_TOTAL))
                    return ERROR_MEMORIA_GRILLA;
                tamMino = (infoJuego[RESOL_ANCHO] >= 640) ? 16 : 8;
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
            for(i = 0; i <= CANT_TETROMINOS_DELUXE; i++)
            {
                partida.cantTetrominos[i] = infoJuego[i];
            }
            partida.puntaje     = infoJuego[SCORE];
            partida.lineas      = infoJuego[LINEAS];
            partida.nivel       = infoJuego[NIVEL];
            partida.velCaida    = velActual;
            partida.anchoGrilla = anchoGrilla;
            partida.modoDeluxe  = infoJuego[MODO_DE_JUEGO];
            memcpy(partida.tetrominos, tetroActivos, sizeof(tetroActivos));
            partidaSerializarGrilla(&partida, &grillaDeFondo);

            if (partidaExiste(nombreJugador, infoJuego[MODO_DE_JUEGO]))
            {
                // Ya existe: pedir confirmacion antes de sobreescribir
                estadoDeJuego = CONFIRMAR_SOBREESCRITURA;
            }
            else
            {
                partidaGuardar(&partida);
                estadoDeJuego = PAUSA;
            }
            break;
        }
        case CONFIRMAR_SOBREESCRITURA:
            while (estadoDeJuego == CONFIRMAR_SOBREESCRITURA)
                estadoDeJuego = confirmarSobreescritura(infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO]);
            // Si el usuario confirmo (vuelve GUARDAR_PARTIDA), la partida ya esta
            // serializada en 'partida', solo hay que guardarla
            if (estadoDeJuego == GUARDAR_PARTIDA)
            {
                partidaGuardar(&partida);
                estadoDeJuego = PAUSA;
            }
            break;
        case CARGAR_PARTIDA:
        {
            if (partidaCargar(nombreJugador, infoJuego[MODO_DE_JUEGO], &partida))
            {
                infoJuego[SCORE] = partida.puntaje;
                infoJuego[LINEAS] = partida.lineas;
                infoJuego[NIVEL] = partida.nivel;
                infoJuego[TETROMINOS_COLOCADOS] = 0;
                for(i = 0; i < CANT_TETROMINOS_DELUXE; i++)
                {
                    infoJuego[i] = partida.cantTetrominos[i];
                    infoJuego[TETROMINOS_COLOCADOS] += infoJuego[i];
                }
                infoJuego[TOP_SCORE] = jugadorObtenerPuntajeMax(nombreJugador);
                velActual = partida.velCaida;
                anchoGrilla = partida.modoDeluxe ? partida.anchoGrilla : ANCHO_GRILLA_DEFAULT;
                infoJuego[MODO_DE_JUEGO] = partida.modoDeluxe;
                memcpy(tetroActivos, partida.tetrominos, sizeof(tetroActivos));

                grillaDestruir(&grillaDeFondo);
                grillaCrear(&grillaDeFondo, anchoGrilla, ALTO_GRILLA_TOTAL);
                partidaRestaurarGrilla(&partida, &grillaDeFondo, infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO]);

                gbt_temporizador_destruir(tempCaida);
                tempCaida = gbt_temporizador_crear(velActual);
                if (!tempCaida)
                    return ERROR_CREAR_TEMPORIZADOR;
                gbt_temporizador_pausar(tempCaida);

                gbt_temporizador_destruir(tempFijacion);
                tempFijacion = gbt_temporizador_crear(velActual / 2);
                if (!tempFijacion)
                    return ERROR_CREAR_TEMPORIZADOR;
                gbt_temporizador_pausar(tempFijacion);

                infoJuego[TETROMINO_LIBRE] = 1;     // El tetromino cargado empieza cayendo libremente
                infoJuego[MODO_VELOCIDAD]  = MODO_VEL_NORMAL;

                partidaNueva = false;
                estadoDeJuego = JUGANDO;
            }
            else
                estadoDeJuego = (estadoAnterior == GAME_OVER)
                    ? GAME_OVER
                    : (infoJuego[MODO_DE_JUEGO] ? MENU_PRINCIPAL_DELUXE : MENU_PRINCIPAL_CLASSIC);
            break;
        }

        case INGRESO_NOMBRE_CARGA:
            while (estadoDeJuego == INGRESO_NOMBRE_CARGA)
                estadoDeJuego = ingresarNombreCarga(infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO], nombreJugador, infoJuego[MODO_DE_JUEGO]);
            if (estadoDeJuego == CARGAR_PARTIDA)
                estadoAnterior = INGRESO_NOMBRE_CARGA;
            break;
        case ERROR_INTERNO_JUEGO:
            return ERROR_INTERNO_JUEGO;
            break;
        }
    }

    gbt_temporizador_destruir(tempCaida);
    gbt_temporizador_destruir(tempFijacion);
    grillaDestruir(&grillaDeFondo);
    grillaDestruir(&grillaDecorativaSup);
    grillaDestruir(&grillaDecorativaInf);
    gbt_destruir_ventana();
    gbt_cerrar();

    return 0;
}
