#include "tPantalla.h"

int pantallaInicial(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce)
{
    gbt_borrar_backbuffer(N);                   //Si habia algo en pantalla, lo borra

    gbt_procesar_entrada();
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();


    botonActualizarTodosInactivo(vecBotones, ce);    //Setea todos los botones como INACTIVOS para dejar solamente iluminado a aquel APUNTADO por el cursor
    (vecBotones + *cursor)->estado = APUNTADO;

    int anchoLetraConEspacio = (5 + ESPACIADO_ENTRE_LETRAS) * ESCALA_TITULO;
    int anchoTotalTitulo = anchoLetraConEspacio * 6;

    tCursorTexto cursorTitulo = { (resolAncho - anchoTotalTitulo) / 2, 30 };

    caracterDibujarEscalado('T', &cursorTitulo, R,  ESCALA_TITULO);
    caracterDibujarEscalado('E', &cursorTitulo, AZ, ESCALA_TITULO);
    caracterDibujarEscalado('T', &cursorTitulo, RB, ESCALA_TITULO);
    caracterDibujarEscalado('R', &cursorTitulo, B, ESCALA_TITULO);
    caracterDibujarEscalado('I', &cursorTitulo, AM,  ESCALA_TITULO);
    caracterDibujarEscalado('S', &cursorTitulo, VE,  ESCALA_TITULO);

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
                return MENU_PRINCIPAL_DELUXE;
            case 2:
                return SALIR_DEL_JUEGO;
        }
    }

    gbt_volcar_backbuffer();

    return PANTALLA_INICIAL;
}

int menuPrincipalClassic(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce)
{
    gbt_borrar_backbuffer(N);                   //Si habia algo en pantalla, lo borra

    gbt_procesar_entrada();
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

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
//                return CARGAR_PARTIDA;
                break;
            case 2:
//                return CONFIGURACION;
            case 3:
                //activarCheats()
                break;
            case 4:
                return PANTALLA_INICIAL;
        }
    }

    gbt_volcar_backbuffer();

    return MENU_PRINCIPAL_CLASSIC;
}

int menuPrincipalDeluxe(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce)
{
    gbt_borrar_backbuffer(N);                   //Si habia algo en pantalla, lo borra

    gbt_procesar_entrada();
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

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
//                return CARGAR_PARTIDA;
                break;
            case 2:
//                return CONFIGURACION;
            case 3:
                //activarCheats()
                break;
            case 4:
                return PANTALLA_INICIAL;
        }
    }

    gbt_volcar_backbuffer();

    return MENU_PRINCIPAL_DELUXE;
}

int interfazJuego(int resolAncho, int resolAlto, tTetromino tetroActivo[TAM_VEC_TETROMINOS], tGrilla *grillaActiva, tGBT_Temporizador *temporizador)
{
    gbt_borrar_backbuffer(N);

    gbt_procesar_entrada();
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

    grillaDeFondoDibujar(resolAncho, resolAlto);        //Dibuja una grilla totalmente vacia que luego sera superpuesta por aquellos minos activos

    if (gbt_temporizador_consumir(temporizador))
    {
        tetroActivo->posY ++; //Si pasa el tiempo, se baja el tetromino
    }

    grillaDibujarTetromino(tetroActivo, resolAncho, resolAlto); //Dibuja el tetromino activo sobre la grilla

    //Hacer grillaDibujar con una grilla que tenga a los minos estaticos

    if (tecla == GBTK_ESCAPE)           //'Esc' ---> Pausa
    {
        return PAUSA;
    }

    gbt_volcar_backbuffer();

    return JUGANDO;
}

int menuPausa(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce)
{
    gbt_borrar_backbuffer(N);

    gbt_procesar_entrada();
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

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
    if (tecla == GBTK_ESCAPE)           //'Esc' ---> Reanudar
    {
        return JUGANDO;
    }

    if (tecla == GBTK_ENTER)
    {
        switch (*cursor)
        {
            case 0:
                return JUGANDO;         //REANUDAR
            case 1:
//                return CARGAR_PARTIDA;
                break;                  //CARGAR PARTIDA (sin implementar)
            case 2:
//                return GUARDAR_PARTIDA;
                break;                  //GUARDAR PARTIDA (sin implementar)
            case 3:
                return PANTALLA_INICIAL; //SALIR AL MENU
        }
    }

    gbt_volcar_backbuffer();

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
