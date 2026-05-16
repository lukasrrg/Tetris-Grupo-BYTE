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
                return INGRESO_NOMBRE;
            case 1:
//                return CARGAR_PARTIDA;
            case 2:
//                return CONFIGURACION;
            case 3:
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
                return INGRESO_NOMBRE;
            case 1:
//                return CARGAR_PARTIDA;
            case 2:
                return CONFIG_DELUXE;
            case 3:
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

    grillaDeFondoDibujar(resolAncho, resolAlto, grillaActiva->anchoGrilla);        //Dibuja una grilla totalmente vacia que luego sera superpuesta por aquellos minos activos

    if (gbt_temporizador_consumir(temporizador))
    {
        tetroActivo->posY ++; //Si pasa el tiempo, se baja el tetromino
    }

    grillaDibujarTetromino(tetroActivo, resolAncho, resolAlto, grillaActiva->anchoGrilla); //Dibuja el tetromino activo sobre la grilla

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
//                return CHEAT; //ACTIVAR CHEATS
                break;
            case 4:
                return PANTALLA_INICIAL; //VUELVE AL MENU
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

int ingresarNombre(int resolAncho, int resolAlto, char nombreOut[MAX_NOMBRE])
{
    // Sub-estados internos
    // 0 = escribiendo nombre
    // 1 = preguntando si sobreescribir
    static int subEstado = 0;
    static char nombre[MAX_NOMBRE] = "";
    static int largo = 0;

    gbt_borrar_backbuffer(N);
    gbt_procesar_entrada();
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

    // Título
    tCursorTexto cur = {(resolAncho - 5*12) / 2, 20};
    escribirTexto("INGRESE SU NOMBRE", &cur, B);

    if (subEstado == 0)
    {
        // Mostrar nombre ingresado hasta ahora + cursor parpadeante simple
        tCursorTexto curNombre = {(resolAncho - MAX_NOMBRE*6) / 2, 60};
        escribirTexto(nombre, &curNombre, AM);

        // Instrucciones
        tCursorTexto curAyuda = {10, resolAlto - 20};
        escribirTexto("ENTER CONFIRMAR  ESC CANCELAR", &curAyuda, GC);

        // Captura de teclas A-Z y espacio
        char c = 0;
        if (tecla >= GBTK_a && tecla <= GBTK_z)
            c = 'A' + (tecla - GBTK_a);    // Convertir a mayúscula

        if (c != 0 && largo < MAX_NOMBRE - 1)
        {
            nombre[largo++] = c;
            nombre[largo] = '\0';
        }

        if (tecla == GBTK_RETROCESO && largo > 0)
        {
            nombre[--largo] = '\0';
        }

        if (tecla == GBTK_ENTER && largo > 0)
        {
            if (jugadorExiste(nombre))
                subEstado = 1;      // Hay que preguntar si sobreescribir
            else
            {
                // Nombre nuevo: guardar y seguir
                strcpy(nombreOut, nombre);
                tJugador nuevo;
                strcpy(nuevo.nombre, nombre);
                nuevo.puntaje_max = 0;
                jugadorGuardar(&nuevo);

                // Resetear estado estático para la próxima vez
                subEstado = 0;
                nombre[0] = '\0';
                largo = 0;
                return JUGANDO;
            }
        }

        if (tecla == GBTK_ESCAPE)
        {
            subEstado = 0;
            nombre[0] = '\0';
            largo = 0;
            return PANTALLA_INICIAL;
        }
    }
    else if (subEstado == 1)
    {
        // Pregunta de sobreescritura
        tCursorTexto curNombre = {(resolAncho - MAX_NOMBRE*6) / 2, 60};
        escribirTexto(nombre, &curNombre, AM);

        tCursorTexto curPregunta = {10, 90};
        escribirTexto("ESE NOMBRE YA EXISTE", &curPregunta, RB);

        tCursorTexto curOpc = {10, 110};
        escribirTexto("ENTER SOBREESCRIBIR  ESC VOLVER", &curOpc, GC);

        if (tecla == GBTK_ENTER)
        {
            // Sobreescribir
            strcpy(nombreOut, nombre);
            tJugador existente;
            strcpy(existente.nombre, nombre);
            existente.puntaje_max = 0;    // O podrías cargar el puntaje anterior
            jugadorGuardar(&existente);

            subEstado = 0;
            nombre[0] = '\0';
            largo = 0;
            return JUGANDO;
        }

        if (tecla == GBTK_ESCAPE)
        {
            subEstado = 0;  // Volver a escribir nombre
        }
    }

    gbt_volcar_backbuffer();
    return INGRESO_NOMBRE;
}

int menuConfigDeluxe(int resolAncho, int resolAlto, int *anchoGrilla)
{
    gbt_borrar_backbuffer(N);
    gbt_procesar_entrada();
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

    tCursorTexto curTit = {0, 15};
    escribirTexto("CONFIGURACION", &curTit, B); // Titulo

    tCursorTexto curEtiq = {0, 40};
    escribirTexto("ANCHO GRILLA", &curEtiq, GC); //Etiqueta

    tCursorTexto curAyuda = {0, resolAlto - 20};
    escribirTexto("A D CAMBIAR  ENTER OK  ESC VOLVER", &curAyuda, GC); //Instrucciones

    tCursorTexto curValor = {0, 70}; //Mostrar valor actual

    if (tecla == GBTK_a && *anchoGrilla > ANCHO_GRILLA_MIN)
        (*anchoGrilla)--;
    if (tecla == GBTK_d && *anchoGrilla < ANCHO_GRILLA_MAX)
        (*anchoGrilla)++;
    if (tecla == GBTK_ENTER || tecla == GBTK_ESCAPE)
        return MENU_PRINCIPAL_DELUXE;

    gbt_volcar_backbuffer();
    return CONFIG_DELUXE;
}
