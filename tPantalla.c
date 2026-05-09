#include "tPantalla.h"

int pantallaInicial(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce)
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
        *cursor = (*cursor - 1 + ce)%ce;                      //Evito salir del rango del vector de botones
    else if (tecla == GBTK_s)               //'S' bajar cursor
        *cursor = (*cursor + 1)%ce;                      //Evito salir del rango del vector de botones
    else if (tecla == GBTK_ESCAPE)           //'Esc' ---> Salir del juego
        return SALIR_DEL_JUEGO;
    else if (tecla == GBTK_ENTER)            //Si se toca ENTER se lleva al jugador a otra pantalla, segun donde este el cursor
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
        *cursor = (*cursor - 1 + ce)%ce;                      //Evito salir del rango del vector de botones
    else if (tecla == GBTK_s)               //'S' bajar cursor
        *cursor = (*cursor + 1)%ce;                      //Evito salir del rango del vector de botones
    else if (tecla == GBTK_ESCAPE)           //'Esc' ---> Salir del juego
        return SALIR_DEL_JUEGO;
    else if (tecla == GBTK_ENTER)            //Si se toca ENTER se lleva al jugador a otra pantalla, segun donde este el cursor
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
        *cursor = (*cursor - 1 + ce)%ce;                      //Evito salir del rango del vector de botones
    else if (tecla == GBTK_s)               //'S' bajar cursor
        *cursor = (*cursor + 1)%ce;                      //Evito salir del rango del vector de botones
    else if (tecla == GBTK_ESCAPE)           //'Esc' ---> Salir del juego
        return SALIR_DEL_JUEGO;
    else if (tecla == GBTK_ENTER)            //Si se toca ENTER se lleva al jugador a otra pantalla, segun donde este el cursor
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

int interfazJuego(int resolAncho, int resolAlto, tTetromino tetroActivo[TAM_VEC_TETROMINOS], tGrilla *grilla, tGBT_Temporizador *tempCaida, tGBT_Temporizador *tempInactiv)
{
    gbt_borrar_backbuffer(N);

    gbt_procesar_entrada();
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

    grillaDeFondoDibujar(resolAncho, resolAlto);        //Dibuja una grilla totalmente vacia que luego sera superpuesta por aquellos minos activos

    grillaDibujarTetromino(tetroActivo, resolAncho, resolAlto); //Dibuja el tetromino activo sobre la grilla

    grillaDibujar(grilla);              //Dibuja a los minos y tetrominos que quedaron ya anclados en el suelo

    if (gbt_temporizador_consumir(tempCaida))
    {
        tetroActivo->posY ++; //Si pasa el tiempo, se baja el tetromino

        if (tetrominoColisionaSuelo(tetroActivo))   //Si colisiona con el suelo (LUEGO IMPLEMENTAR COLISION CON OTROS MINOS)
        {
            grillaActualizar(grilla, tetroActivo);  //Se guarda el tetromino en "grilla"
            actualizarVectorTetrominos(tetroActivo);    //Se continua con el siguiente tetromino del vector y se agrega un tetromino nuevo al final del mismo
        //AGREGAR UN PEQUEÑO TIEMPO DE ESPERA ENTRE QUE SE DETECTA LA COLISION HASTA QUE REALMENTE SE ANCLA EL TETROMINO

        }
    }


    //IMPLEMENTAR CHEQUEAR LAS COLISIONES CON LOS BORDES
    if (tecla == GBTK_a)                //Si toco 'A' va a la izquierda
        tetroActivo->posX--;
    else if (tecla == GBTK_d)                //Si toco 'D' va a la derecha
        tetroActivo->posX++;
    else if (tecla == GBTK_ESCAPE)           //'Esc' ---> Salir del juego (En el futuro cambiar a que se pause el juego, o que pregunte si realmente quiero salir del juego)
        return SALIR_DEL_JUEGO;


    gbt_volcar_backbuffer();

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
