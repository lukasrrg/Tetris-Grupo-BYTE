#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "lib/GBT_v2026.1C.01/include/GBT/gbt.h"

#include "tMino.h"
#include "tGrilla.h"

//Codigos de errores
#define TODO_OK 0
#define ERROR_MEMORIA_GRILLA -333
#define ERROR_INICIAR_GBT -148
#define ERROR_ABRIENDO_VENTANA -3000
#define ERROR_APLICANDO_PALETA -666

int main()
{
    int corriendo = 1;                              //Flag para determinar si el juego corre o no corre
    eGBT_Tecla tecla;                               //Se guarda la tecla presionada
    srand(time(0));                                 //Se abre el randomizador

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
    sprintf(nombreVentana, "Ventana %dx%d", ANCHO_VENTANA_CGA, ALTO_VENTANA_CGA);

    if (gbt_crear_ventana(nombreVentana, ANCHO_VENTANA_CGA, ALTO_VENTANA_CGA, ESCALA_VENTANA) != 0)     //Abro ventana (por ahora en CGA)
    {
        fprintf(stderr, "Error al iniciar el modulo de graficos de GBT: %s\n", gbt_obtener_log());
        return ERROR_ABRIENDO_VENTANA;
    }

    tGrilla grilla;                                 //Grilla que despues va a estar in-game

    if (!grillaCrear(&grilla))                      //Se pide el espacio en memoria
    {
        return ERROR_MEMORIA_GRILLA;
    }


    tMino mino;

    minoCrear(&mino, 50, 50, C);

    while(corriendo)                                //Mientras el juego este corriendo...
    {
        gbt_procesar_entrada();
        tecla = gbt_obtener_tecla_presionada();

        grillaDibujar(&grilla);

        if (tecla == GBTK_ESCAPE)                   //'Esc' ---> Salir del juego
        {
            corriendo = 0;
        }


        gbt_volcar_backbuffer();                //Actualiza lo que se tiene que mostrar en pantalla
    }


    grillaDestruir(&grilla);                //Se libera el espacio en memoria de la grilla
    gbt_destruir_ventana();         //Cierra ventana y GBT
    gbt_cerrar();

    return 0;
}
