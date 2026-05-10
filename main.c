//INTEGRANTES:
//Apellido y nombres: Ramirez, Lucas
//DNI: 39347109
//Usuario: lukasrrg
//Entrega: S�
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

//Codigos de errores
#define TODO_OK 0
#define ERROR_MEMORIA_GRILLA -333
#define ERROR_INICIAR_GBT -148
#define ERROR_ABRIENDO_VENTANA -3000
#define ERROR_APLICANDO_PALETA -666
#define ERROR_CREAR_TEMPORIZADOR 1234


int main(int argc, char *argv[])
{
    int estadoDeJuego = PANTALLA_INICIAL;                        //Segun su valor, define en que pantalla vamos a estar en determinado momento (ver defines arriba)
    int resolAncho = ANCHO_VENTANA_CGA, resolAlto = ALTO_VENTANA_CGA;    //Ancho y alto de resolucion, por defecto esta seteado en CGA, pero por argumento a main se puede seleccionar entre CGA (320x200) y VGA (640x480)

    if (argc > 2)        //Por el momento solo se pasa como mucho dos argumentos: el nombre del ejecutable y la resolucion, si se pasa mas, indicar error y seguir normalmente
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




    if (gbt_iniciar() != 0)                         //Inicio GBT
    {
        fprintf(stderr, "Error al iniciar GBT: %s\n", gbt_obtener_log());
        return ERROR_INICIAR_GBT;
    }

    if (gbt_aplicar_paleta(paletaCGA, CANT_COLORES, GBT_FORMATO_888) != 0)
    {
        fprintf(stderr, "Error al aplicar la nueva paleta de colores: %s\n", gbt_obtener_log());
        return ERROR_APLICANDO_PALETA;
    }

    char nombreVentana[128];                        //Nombre para la ventana del juego, con la resolucion seleccionada (por ahora CGA)
    sprintf(nombreVentana, "Ventana %dx%d", resolAncho, resolAlto);

    if (gbt_crear_ventana(nombreVentana, resolAncho, resolAlto, ESCALA_VENTANA) != 0)     //Abro ventana (por ahora en CGA)
    {
        fprintf(stderr, "Error al iniciar el modulo de graficos de GBT: %s\n", gbt_obtener_log());
        return ERROR_ABRIENDO_VENTANA;
    }




    srand(time(0));                                 //Se abre el randomizador




    //Tetrominos para ir probando
    tTetromino tetrominoO;
    tetrominoCrear(&tetrominoO, TETRO_O, 0, 10);

    tTetromino tetrominoZ;
    tetrominoCrear(&tetrominoZ, TETRO_Z, 1, 1);

    tTetromino tetrominoT;
    tetrominoCrear(&tetrominoT, TETRO_T, 2, 8);

    tTetromino tetrominoS;
    tetrominoCrear(&tetrominoS, TETRO_S, 3, 15);

    tTetromino tetrominoL;
    tetrominoCrear(&tetrominoL, TETRO_L, 6, 10);

    tTetromino tetrominoJ;
    tetrominoCrear(&tetrominoJ, TETRO_J, 1, 2);

    tTetromino tetrominoI;
    tetrominoCrear(&tetrominoI, TETRO_I, 0, 1);




    tGrilla grillaDeFondo;                                 //Grilla que despues va a estar in-game
    if (!grillaCrear(&grillaDeFondo, resolAncho, resolAlto))                      //Se pide el espacio en memoria
    {
        return ERROR_MEMORIA_GRILLA;
    }
    int cursorBoton;
    tGBT_Temporizador *temporizador = gbt_temporizador_crear(VEL_INI_CAIDA);    //Inicializaci�n del temporizador
    if (!temporizador)
    {
        return ERROR_CREAR_TEMPORIZADOR;
    }
    gbt_temporizador_pausar(temporizador);                          //Se lo pausa ya que todavia no sera utilizado
    tTetromino tetroActivos[TAM_VEC_TETROMINOS];
    bool partidaNueva = true;           //Indica si se debe resetear el estado al entrar a JUGANDO


    while(estadoDeJuego)                           //Mientras estadoDeJuego no este en SALIR_DEL_JUEGO, el juego se reproduce
    {
        switch (estadoDeJuego)
        {
            case PANTALLA_INICIAL:
                cursorBoton = 0;
                tBoton botonesPantallaInicial[3];               //Guardo en memoria los botones de la pantalla principal
                //Boton Classic
                botonCrear(&botonesPantallaInicial[0], APUNTADO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_GRANDE)/2, (resolAlto - ALTO_BOTON_DEFAULT)/2, B, AM, "MODO CLASSIC", N);
                //Boton Deluxe
                botonCrear(&botonesPantallaInicial[1], INACTIVO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_GRANDE)/2, (resolAlto + ALTO_BOTON_DEFAULT)/2 + SEPARACION_ENTRE_BOTON, B, VE, "MODO DELUXE", N);
                //Boton Salir
                botonCrear(&botonesPantallaInicial[2], INACTIVO, ANCHO_BOTON_CHICO, ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_CHICO)/2, (resolAlto + 3*ALTO_BOTON_DEFAULT)/2 + SEPARACION_ENTRE_BOTON*2, B, R, "SALIR", N);
                while (estadoDeJuego == PANTALLA_INICIAL)
                {
                    estadoDeJuego = pantallaInicial(resolAncho, resolAlto, &cursorBoton, botonesPantallaInicial, 3);
                }
                partidaNueva = true;    //Cualquier camino desde la pantalla inicial siempre arranca partida nueva
                break;

            case MENU_PRINCIPAL_CLASSIC:
                cursorBoton = 0;
                tBoton botonesMenuPrincipalClassic[5];                  //Guardo en memoria los botones del menu principal Classic
                //Boton Partida Nueva
                botonCrear(&botonesMenuPrincipalClassic[0], APUNTADO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_GRANDE)/2, (resolAlto - 5*ALTO_BOTON_DEFAULT)/2, B, AM, "PARTIDA NUEVA", N);
                //Boton Cargar Partida
                botonCrear(&botonesMenuPrincipalClassic[1], INACTIVO, ANCHO_BOTON_MEDIANO, ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_MEDIANO)/2, (resolAlto - 3*ALTO_BOTON_DEFAULT + SEPARACION_ENTRE_BOTON)/2, B, AM, "CARGAR PARTIDA", N);
                //Boton Configuracion
                botonCrear(&botonesMenuPrincipalClassic[2], INACTIVO, ANCHO_BOTON_MEDIANO, ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_MEDIANO)/2, (resolAlto - ALTO_BOTON_DEFAULT)/2 +2*SEPARACION_ENTRE_BOTON, B, AM, "CONFIGURACION", N);
                //Boton Cheats
                botonCrear(&botonesMenuPrincipalClassic[3], INACTIVO, ANCHO_BOTON_MEDIANO, ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_MEDIANO)/2, (resolAlto + ALTO_BOTON_DEFAULT)/2 + 3*SEPARACION_ENTRE_BOTON, B, AM, "CHEATS", N);
                //Boton Atras
                botonCrear(&botonesMenuPrincipalClassic[4], INACTIVO, ANCHO_BOTON_CHICO, ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_CHICO)/2, (resolAlto + 3*ALTO_BOTON_DEFAULT)/2 + 4*SEPARACION_ENTRE_BOTON, B, R, "ATRAS", N);

                while(estadoDeJuego == MENU_PRINCIPAL_CLASSIC)
                {
                    estadoDeJuego = menuPrincipalClassic(resolAncho, resolAlto, &cursorBoton, botonesMenuPrincipalClassic, 5);
                }
                break;

            case MENU_PRINCIPAL_DELUXE:
                cursorBoton = 0;
                tBoton botonesMenuPrincipalDeluxe[5];                  //Guardo en memoria los botones del menu principal Deluxe
                //Boton Partida Nueva
                botonCrear(&botonesMenuPrincipalDeluxe[0], APUNTADO, ANCHO_BOTON_GRANDE, ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_GRANDE)/2, (resolAlto - 5*ALTO_BOTON_DEFAULT)/2, B, AM, "PARTIDA NUEVA", N);
                //Boton Cargar Partida
                botonCrear(&botonesMenuPrincipalDeluxe[1], INACTIVO, ANCHO_BOTON_MEDIANO, ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_MEDIANO)/2, (resolAlto - 3*ALTO_BOTON_DEFAULT + SEPARACION_ENTRE_BOTON)/2, B, AM, "CARGAR PARTIDA", N);
                //Boton Configuracion
                botonCrear(&botonesMenuPrincipalDeluxe[2], INACTIVO, ANCHO_BOTON_MEDIANO, ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_MEDIANO)/2, (resolAlto - ALTO_BOTON_DEFAULT)/2 +2*SEPARACION_ENTRE_BOTON, B, AM, "CONFIGURACION", N);
                //Boton Cheats
                botonCrear(&botonesMenuPrincipalDeluxe[3], INACTIVO, ANCHO_BOTON_MEDIANO, ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_MEDIANO)/2, (resolAlto + ALTO_BOTON_DEFAULT)/2 + 3*SEPARACION_ENTRE_BOTON, B, AM, "CHEATS", N);
                //Boton Atras
                botonCrear(&botonesMenuPrincipalDeluxe[4], INACTIVO, ANCHO_BOTON_CHICO, ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_CHICO)/2, (resolAlto + 3*ALTO_BOTON_DEFAULT)/2 + 4*SEPARACION_ENTRE_BOTON, B, R, "ATRAS", N);

                while(estadoDeJuego == MENU_PRINCIPAL_DELUXE)
                {
                    estadoDeJuego = menuPrincipalDeluxe(resolAncho, resolAlto, &cursorBoton, botonesMenuPrincipalDeluxe, 5);
                }
                break;

            case JUGANDO:
                if (partidaNueva)
                {
                    tetrominoCargarVector(tetroActivos);            //Resetea los tetrominos para la nueva partida
                    grillaDestruir(&grillaDeFondo);                 //Resetea la grilla para la nueva partida
                    grillaCrear(&grillaDeFondo, resolAncho, resolAlto);
                    partidaNueva = false;
                }
                gbt_temporizador_reanudar(temporizador);
                while (estadoDeJuego == JUGANDO)
                {
                    estadoDeJuego = interfazJuego(resolAncho, resolAlto, tetroActivos, &grillaDeFondo, temporizador);
                }
                break;

            case PAUSA:
                gbt_temporizador_pausar(temporizador);
                cursorBoton = 0;
                tBoton botonesMenuPausa[4];
                //Boton Reanudar
                botonCrear(&botonesMenuPausa[0], APUNTADO,  ANCHO_BOTON_GRANDE,  ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_GRANDE)/2,  (resolAlto - 5*ALTO_BOTON_DEFAULT)/2,                          B, VE, "REANUDAR",       N);
                //Boton Cargar Partida
                botonCrear(&botonesMenuPausa[1], INACTIVO,  ANCHO_BOTON_GRANDE,  ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_GRANDE)/2,  (resolAlto - 3*ALTO_BOTON_DEFAULT + SEPARACION_ENTRE_BOTON)/2, B, AM, "CARGAR PARTIDA",  N);
                //Boton Guardar Partida
                botonCrear(&botonesMenuPausa[2], INACTIVO,  ANCHO_BOTON_GRANDE,  ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_GRANDE)/2,  (resolAlto - ALTO_BOTON_DEFAULT)/2 + 2*SEPARACION_ENTRE_BOTON,  B, AM, "GUARDAR PARTIDA", N);
                //Boton Salir al Menu
                botonCrear(&botonesMenuPausa[3], INACTIVO,  ANCHO_BOTON_MEDIANO, ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_MEDIANO)/2, (resolAlto + ALTO_BOTON_DEFAULT)/2 + 3*SEPARACION_ENTRE_BOTON,  B, R,  "SALIR AL MENU",   N);
                while (estadoDeJuego == PAUSA)
                {
                    estadoDeJuego = menuPausa(resolAncho, resolAlto, &cursorBoton, botonesMenuPausa, 4);
                }
                if (estadoDeJuego == JUGANDO)
                    gbt_temporizador_reanudar(temporizador);
                break;
        }
    }




    grillaDestruir(&grillaDeFondo);                //Se libera el espacio en memoria de la grilla
    gbt_destruir_ventana();         //Cierra ventana y GBT
    gbt_cerrar();

    return 0;
}
