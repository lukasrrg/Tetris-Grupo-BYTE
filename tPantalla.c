#include "tPantalla.h"

int pantallaInicial(int resolAncho, int resolAlto, eGBT_Tecla tecla, int* cursor, tBoton *vecBotones, int ce)
{
    tBoton *i;
    tBoton *finVec = vecBotones + ce;
    for(i = vecBotones; i < finVec; i++)
        botonDibujar(i);

    if (tecla == GBTK_w)               //'W' subir cursor
    {
        *cursor = (*cursor + 2)%3;                      //Evito salir del rango del vector de botones
        botonActualizarTodosInactivo(vecBotones, 3);    //Setea todos los botones como INACTIVOS
        (vecBotones + *cursor)->estado = APUNTADO;      //Setea al boton apuntado por el cursor como APUNTADO
    }
    if (tecla == GBTK_s)               //'S' bajar cursor
    {
        *cursor = (*cursor + 1)%3;                      //Evito salir del rango del vector de botones
        botonActualizarTodosInactivo(vecBotones, 3);    //Setea todos los botones como INACTIVOS
        (vecBotones + *cursor)->estado = APUNTADO;      //Setea al boton apuntado por el cursor como APUNTADO
    }
    if (tecla == GBTK_ESCAPE)           //'Esc' ---> Salir del juego
    {
        return SALIR_DEL_JUEGO;
    }

    return PANTALLA_INICIAL;
}

int menuPrincipal(int resolAncho, int resolAlto)
{
    return 0;
}

int interfazJuego(int resolAncho, int resolAlto)
{
    return 0;
}

int menuPausa(int resolAncho, int resolAlto)
{
    return 0;
}

int gameOver(int resolAncho, int resolAlto)
{
    return 0;
}

int menuConfiguracion(int resolAncho, int resolAlto)
{
    return 0;
}
