//INTEGRANTES:
//Apellido y nombres: Ramírez, Lucas
//DNI: 39347109
//Usuario: lukasrrg
//Entrega: Sí
//
//Apellido y nombres: Varela, Lucas Sebastián
//DNI: 36756277
//Usuario: lucasvarela93
//Entrega: Sí
//
//Apellido y nombres: Colombini, Donato
//DNI: 46753332
//Usuario: Donato2405
//Entrega: Sí
//
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "lib/GBT_v2026.1C.01/include/GBT/gbt.h"

#include "tPantalla.h"
#include "tGrilla.h"

//Codigos de errores
#define TODO_OK 0
#define ERROR_MEMORIA_GRILLA -333
#define ERROR_INICIAR_GBT -148
#define ERROR_ABRIENDO_VENTANA -3000
#define ERROR_APLICANDO_PALETA -666

//Estado de juego
#define PANTALLA_INICIAL 1
#define MENU_PRINCIPAL 2
#define JUGANDO 3
#define PAUSA 4
#define GAME_OVER 5
#define CONFIGURACION 6
#define SALIR_DEL_JUEGO 0


int main(int argc, char *argv[])
{
    int estadoDeJuego = 1;                        //Segun su valor, define en que pantalla vamos a estar en determinado momento (ver defines arriba)
    int resolAncho = ANCHO_VENTANA_CGA, resolAlto = ALTO_VENTANA_CGA;    //Ancho y alto de resolucion, por defecto esta seteado en CGA, pero por argumento a main se puede seleccionar entre CGA (320x200) y VGA (640x480)

    if (argc > 2)        //Por el momento solo se pasa como mucho dos argumentos, el nombre del ejecutable y la resolucion, si se pasa mas, indicar error y seguir normalmente
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


    eGBT_Tecla tecla;                               //Se guarda la tecla presionada
    srand(time(0));                                 //Se abre el randomizador
    int cursor = 0;
    tBoton botonesPantallaPrincipal[3];
    //Boton Classic
    botonCrear(&botonesPantallaPrincipal[0], APUNTADO, ANCHO_BOTON_MEDIANO, ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_MEDIANO)/2, (resolAlto - ALTO_BOTON_DEFAULT)/2, B, A);
    //Boton Deluxe
    botonCrear(&botonesPantallaPrincipal[1], INACTIVO, ANCHO_BOTON_MEDIANO, ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_MEDIANO)/2, (resolAlto + ALTO_BOTON_DEFAULT)/2, B, V);
    //Boton Salir
    botonCrear(&botonesPantallaPrincipal[2], INACTIVO, ANCHO_BOTON_CHICO, ALTO_BOTON_DEFAULT, (resolAncho - ANCHO_BOTON_CHICO)/2, (resolAlto + 3*ALTO_BOTON_DEFAULT)/2, B, R);
//    cursor = botonesPantallaPrincipal;




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

    tGrilla grilla;                                 //Grilla que despues va a estar in-game

    if (!grillaCrear(&grilla, resolAncho, resolAlto))                      //Se pide el espacio en memoria
    {
        return ERROR_MEMORIA_GRILLA;
    }







    while(estadoDeJuego)                           //Mientras estadoDeJuego no este en SALIR_DEL_JUEGO, el juego se reproduce
    {
        gbt_procesar_entrada();
        tecla = gbt_obtener_tecla_presionada();

        if (estadoDeJuego == 1)
        {
            estadoDeJuego = pantallaInicial(resolAncho, resolAlto, tecla, &cursor, botonesPantallaPrincipal, 3);
        }
//
//        grillaDibujar(&grilla);
//
//        if (tecla == GBTK_ESCAPE)                   //'Esc' ---> Salir del juego
//        {
//            estadoDeJuego = 0;
//        }


        gbt_volcar_backbuffer();                //Actualiza lo que se tiene que mostrar en pantalla
    }








    grillaDestruir(&grilla);                //Se libera el espacio en memoria de la grilla
    gbt_destruir_ventana();         //Cierra ventana y GBT
    gbt_cerrar();

    return 0;
}
