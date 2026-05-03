#include "tPantalla.h"

int pantallaInicial(int resolAncho, int resolAlto, eGBT_Tecla tecla, int* cursor, tBoton *vecBotones, int ce)
{
    gbt_borrar_backbuffer(N);                   //Si habia algo en pantalla, lo borra

    botonActualizarTodosInactivo(vecBotones, ce);    //Setea todos los botones como INACTIVOS para dejar solamente iluminado a aquel APUNTADO por el cursor
    (vecBotones + *cursor)->estado = APUNTADO;

    tBoton *i;
    tBoton *finVec = vecBotones + ce;
    for(i = vecBotones; i < finVec; i++)
        botonDibujar(i);



    if (tecla == GBTK_w)               //'W' subir cursor
    {
        *cursor = (*cursor - 1 + ce)%ce;                      //Evito salir del rango del vector de botones
    }
    if (tecla == GBTK_s)               //'S' bajar cursor
    {
        *cursor = (*cursor + 1)%ce;                      //Evito salir del rango del vector de botones
    }
    if (tecla == GBTK_ESCAPE)           //'Esc' ---> Salir del juego
    {
        return SALIR_DEL_JUEGO;
    }
    if (tecla == GBTK_ENTER)            //Si se toca ENTER se lleva al jugador a otra pantalla, segun donde este el cursor
    {
        switch (*cursor)
        {
            case 0:
                return MENU_PRINCIPAL_CLASSIC;
            case 1:
                *cursor = 0;          //Antes de salir esta pantalla, reestablezco cursor a 0, para que asi aparezca en la siguiente pantalla
                return MENU_PRINCIPAL_DELUXE;
            case 2:
                *cursor = 0;          //Antes de salir esta pantalla, reestablezco cursor a 0, para que asi aparezca en la siguiente pantalla
                return SALIR_DEL_JUEGO;
        }
    }

    return PANTALLA_INICIAL;
}

int menuPrincipalClassic(int resolAncho, int resolAlto, eGBT_Tecla tecla, int* cursor, tBoton *vecBotones, int ce)
{
    gbt_borrar_backbuffer(N);                   //Si habia algo en pantalla, lo borra

    botonActualizarTodosInactivo(vecBotones, ce);    //Setea todos los botones como INACTIVOS para dejar solamente iluminado a aquel APUNTADO por el cursor
    (vecBotones + *cursor)->estado = APUNTADO;

    tBoton *i;
    tBoton *finVec = vecBotones + ce;
    for(i = vecBotones; i < finVec; i++)
        botonDibujar(i);

    if (tecla == GBTK_w)               //'W' subir cursor
    {
        *cursor = (*cursor - 1 + ce)%ce;                      //Evito salir del rango del vector de botones
    }
    if (tecla == GBTK_s)               //'S' bajar cursor
    {
        *cursor = (*cursor + 1)%ce;                      //Evito salir del rango del vector de botones
    }
    if (tecla == GBTK_ESCAPE)           //'Esc' ---> Salir del juego
    {
        return SALIR_DEL_JUEGO;
    }

    if (tecla == GBTK_ENTER)            //Si se toca ENTER se lleva al jugador a otra pantalla, segun donde este el cursor
    {
        switch (*cursor)
        {
            case 0:
                return JUGANDO;         //Empieza la partida
            case 1:
                *cursor = 0;          //Antes de salir esta pantalla, reestablezco cursor a 0, para que asi aparezca en la siguiente pantalla
//                return CARGAR_PARTIDA;
                break;
            case 2:
                *cursor = 0;          //Antes de salir esta pantalla, reestablezco cursor a 0, para que asi aparezca en la siguiente pantalla
                return CONFIGURACION;
            case 3:
                //activarCheats()
                break;
            case 4:
                *cursor = 0;
                return PANTALLA_INICIAL;
        }
    }

    return MENU_PRINCIPAL_CLASSIC;
}

int menuPrincipalDeluxe(int resolAncho, int resolAlto, eGBT_Tecla tecla, int* cursor, tBoton *vecBotones, int ce)
{
    gbt_borrar_backbuffer(N);                   //Si habia algo en pantalla, lo borra

    botonActualizarTodosInactivo(vecBotones, ce);    //Setea todos los botones como INACTIVOS para dejar solamente iluminado a aquel APUNTADO por el cursor
    (vecBotones + *cursor)->estado = APUNTADO;

    tBoton *i;
    tBoton *finVec = vecBotones + ce;
    for(i = vecBotones; i < finVec; i++)
        botonDibujar(i);

    if (tecla == GBTK_w)               //'W' subir cursor
    {
        *cursor = (*cursor - 1 + ce)%ce;                      //Evito salir del rango del vector de botones
    }
    if (tecla == GBTK_s)               //'S' bajar cursor
    {
        *cursor = (*cursor + 1)%ce;                      //Evito salir del rango del vector de botones
    }
    if (tecla == GBTK_ESCAPE)           //'Esc' ---> Salir del juego
    {
        return SALIR_DEL_JUEGO;
    }

    if (tecla == GBTK_ENTER)            //Si se toca ENTER se lleva al jugador a otra pantalla, segun donde este el cursor
    {
        switch (*cursor)
        {
            case 0:
                return JUGANDO;         //Empieza la partida
            case 1:
                *cursor = 0;          //Antes de salir esta pantalla, reestablezco cursor a 0, para que asi aparezca en la siguiente pantalla
//                return CARGAR_PARTIDA;
                break;
            case 2:
                *cursor = 0;          //Antes de salir esta pantalla, reestablezco cursor a 0, para que asi aparezca en la siguiente pantalla
                return CONFIGURACION;
            case 3:
                //activarCheats()
                break;
            case 4:
                *cursor = 0;
                return PANTALLA_INICIAL;
        }
    }

    return MENU_PRINCIPAL_DELUXE;
}

int interfazJuego(int resolAncho, int resolAlto, tGrilla *grilla, eGBT_Tecla tecla)
{
    gbt_borrar_backbuffer(N);

    grillaDibujar(grilla);


    if (tecla == GBTK_ESCAPE)           //'Esc' ---> Salir del juego
    {
        return SALIR_DEL_JUEGO;
    }

    return JUGANDO;
}

int menuPausa(int resolAncho, int resolAlto)
{
    return PAUSA;
}

int gameOver(int resolAncho, int resolAlto)
{
    return GAME_OVER;
}

int menuConfiguracion(int resolAncho, int resolAlto)
{
    return CONFIGURACION;
}
