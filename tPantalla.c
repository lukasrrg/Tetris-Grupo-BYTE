#include "tPantalla.h"

int pantallaInicial(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce)
{
<<<<<<< HEAD
=======
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
            case 2:
//                return CONFIGURACION;
            case 3:
                return PANTALLA_INICIAL;
        }
    }

    gbt_volcar_backbuffer();

    return MENU_PRINCIPAL_DELUXE;
}

int interfazJuego(int resolAncho, int resolAlto, tTetromino tetroActivo[TAM_VEC_TETROMINOS], tGrilla *grilla, tGBT_Temporizador **tempCaida, tGBT_Temporizador **tempInactiv, double *velActual, int *modoVelocidad)
{
    int lineas = 0;
    int puntaje = 0;
    int puntajeMax = 0;
    int nivel = 1;

>>>>>>> bafd173e0d91aff7488c7bdf4932643df57b838d
    gbt_borrar_backbuffer(N);

    gbt_procesar_entrada();
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

<<<<<<< HEAD
    botonActualizarTodosInactivo(vecBotones, ce);
    (vecBotones + *cursor)->estado = APUNTADO;

    int anchoLetraConEspacio = (5 + ESPACIADO_ENTRE_LETRAS) * ESCALA_TITULO;
    int anchoTotalTitulo = anchoLetraConEspacio * 6;
    tCursorTexto cursorTitulo = { (resolAncho - anchoTotalTitulo) / 2, 30 };

    caracterDibujarEscalado('T', &cursorTitulo, R,  ESCALA_TITULO);
    caracterDibujarEscalado('E', &cursorTitulo, AZ, ESCALA_TITULO);
    caracterDibujarEscalado('T', &cursorTitulo, RB, ESCALA_TITULO);
    caracterDibujarEscalado('R', &cursorTitulo, B,  ESCALA_TITULO);
    caracterDibujarEscalado('I', &cursorTitulo, AM, ESCALA_TITULO);
    caracterDibujarEscalado('S', &cursorTitulo, VE, ESCALA_TITULO);

    tBoton *i;
    tBoton *finVec = vecBotones + ce;
    for(i = vecBotones; i < finVec; i++)
        botonDibujar(i);

    if (tecla == GBTK_w)
        *cursor = (*cursor - 1 + ce) % ce;
    else if (tecla == GBTK_s)
        *cursor = (*cursor + 1) % ce;
    else if (tecla == GBTK_ESCAPE)
        return SALIR_DEL_JUEGO;
    else if (tecla == GBTK_ENTER)
    {
        switch (*cursor)
        {
            case 0: return MENU_PRINCIPAL_CLASSIC;
            case 1: return MENU_PRINCIPAL_DELUXE;
            case 2: return SALIR_DEL_JUEGO;
=======
    int anchoGrilla = ANCHO_GRILLA*TAM_MINO;
    int altoGrilla = ALTO_GRILLA_VISIBLE*TAM_MINO;
    dibujarRectangulo((resolAncho - anchoGrilla)/2, (resolAlto - altoGrilla)/2, anchoGrilla, altoGrilla, C);       //Dibuja un rectangulo vacio que funciona como grilla

    infoInterfazDeJuego(lineas, puntaje, puntajeMax, nivel, tetroActivo[1].tipo, resolAncho, resolAlto);   //Muestra la informacion del juego en pantalla (score, lineas, nivel, etc)

    grillaDibujarTetromino(tetroActivo, resolAncho, resolAlto); //Dibuja el tetromino activo sobre la grilla

    grillaDibujar(grilla);              //Dibuja a los minos y tetrominos que quedaron ya anclados en el suelo


    if (gbt_temporizador_consumir(*tempCaida))
    {
        tetroActivo->posY ++; //Si pasa el tiempo, se baja el tetromino

        if (tetrominoColisionaSuelo(tetroActivo) || tetrominoColisionaConOtro(tetroActivo, grilla))   //Si colisiona con el suelo (LUEGO IMPLEMENTAR COLISION CON OTROS MINOS)
        {
            grillaActualizar(grilla, tetroActivo);  //Se guarda el tetromino en "grilla"
            actualizarVectorTetrominos(tetroActivo, CANT_TETROMINOS_CLASSIC);    //Se continua con el siguiente tetromino del vector y se agrega un tetromino nuevo al final del mismo
        //AGREGAR UN PEQUEÑO TIEMPO DE ESPERA ENTRE QUE SE DETECTA LA COLISION HASTA QUE REALMENTE SE ANCLA EL TETROMINO

>>>>>>> bafd173e0d91aff7488c7bdf4932643df57b838d
        }
    }

    if (tecla == GBTK_a && !tetrominoColisionaLateralmente(tetroActivo, grilla, IZQUIERDA))    //Si toco 'A' y hay espacio disponible, va a la izquierda
         tetroActivo->posX--;
    else if (tecla == GBTK_d && !tetrominoColisionaLateralmente(tetroActivo, grilla, DERECHA))  //Si toco 'D' y hay espacio disponible, va a la derecha
        tetroActivo->posX++;

        //TODAVIA NO ESTA IMPLKEMENTADO QUE IMPIDA LA ROTACION SI DETECTA UNA COLISION
    else if (tecla == GBTK_j)           //Si toco 'J', rotacion antihoraria
        tetrominoRotar(tetroActivo, ANTIHORARIO);
        //TODAVIA NO ESTA IMPLKEMENTADO QUE IMPIDA LA ROTACION SI DETECTA UNA COLISION
    else if (tecla == GBTK_l)           //Si toco ´L´ rotacion horaria
        tetrominoRotar(tetroActivo, HORARIO);
    else if (tecla == GBTK_ESCAPE || tecla == GBTK_p)           //'Esc' ---> Pausa
        return PAUSA;
    else if (gbt_tecla_sostenida(GBTK_s) && *modoVelocidad != VEL_RAPIDA)   //Si se mantiene ´S´ pulsado y la velocidad estaba NORMAL, se pasa a modo RAPIDO
    {
        gbt_temporizador_destruir(*tempCaida);
        *tempCaida = gbt_temporizador_crear(*velActual/FACTOR_VEL_RAPIDA);

        *modoVelocidad = VEL_RAPIDA;
    }
    else if (*modoVelocidad != VEL_NORMAL && !gbt_tecla_sostenida(GBTK_s))  //Si se suela la ´S´ y la velocidad estaba RAPIDO, se pasa a modo NORMAL
    {
        gbt_temporizador_destruir(*tempCaida);
        *tempCaida = gbt_temporizador_crear(*velActual);

        *modoVelocidad = VEL_NORMAL;
    }


    gbt_volcar_backbuffer();
    return PANTALLA_INICIAL;
}

int menuPrincipalClassic(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce)
{
    gbt_borrar_backbuffer(N);

    gbt_procesar_entrada();
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

    botonActualizarTodosInactivo(vecBotones, ce);
    (vecBotones + *cursor)->estado = APUNTADO;

    tBoton *i;
    tBoton *finVec = vecBotones + ce;
    for(i = vecBotones; i < finVec; i++)
        botonDibujar(i);

    if (tecla == GBTK_w)
        *cursor = (*cursor - 1 + ce) % ce;
    else if (tecla == GBTK_s)
        *cursor = (*cursor + 1) % ce;
    else if (tecla == GBTK_ESCAPE)
        return SALIR_DEL_JUEGO;
    else if (tecla == GBTK_ENTER)
    {
        switch (*cursor)
        {
            case 0: return INGRESO_NOMBRE;
            case 1: // return CARGAR_PARTIDA; (sin implementar)
            case 2: // return CONFIGURACION;  (sin implementar)
            case 3: return PANTALLA_INICIAL;
        }
    }

    gbt_volcar_backbuffer();
    return MENU_PRINCIPAL_CLASSIC;
}

int menuPrincipalDeluxe(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce)
{
    gbt_borrar_backbuffer(N);

    gbt_procesar_entrada();
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

    botonActualizarTodosInactivo(vecBotones, ce);
    (vecBotones + *cursor)->estado = APUNTADO;

    tBoton *i;
    tBoton *finVec = vecBotones + ce;
    for(i = vecBotones; i < finVec; i++)
        botonDibujar(i);

    if (tecla == GBTK_w)
        *cursor = (*cursor - 1 + ce) % ce;
    else if (tecla == GBTK_s)
        *cursor = (*cursor + 1) % ce;
    else if (tecla == GBTK_ESCAPE)
        return SALIR_DEL_JUEGO;
    else if (tecla == GBTK_ENTER)
    {
        switch (*cursor)
        {
            case 0: return INGRESO_NOMBRE;
            case 1: // return CARGAR_PARTIDA; (sin implementar)
            case 2: return CONFIG_DELUXE;
            case 3: return PANTALLA_INICIAL;
        }
    }

    gbt_volcar_backbuffer();
    return MENU_PRINCIPAL_DELUXE;
}

int interfazJuego(int resolAncho, int resolAlto, tTetromino tetroActivo[TAM_VEC_TETROMINOS], tGrilla *grilla, tGBT_Temporizador **tempCaida, tGBT_Temporizador **tempInactiv, double *velActual, int *modoVelocidad)
{
    int lineas = 0;
    int puntaje = 0;
    int puntajeMax = 0;
    int nivel = 1;

    gbt_borrar_backbuffer(N);

    gbt_procesar_entrada();
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

    int anchoGrillaPx = grilla->anchoGrilla * TAM_MINO;
    int altoGrillaPx  = ALTO_GRILLA_VISIBLE * TAM_MINO;
    dibujarRectangulo((resolAncho - anchoGrillaPx)/2, (resolAlto - altoGrillaPx)/2, anchoGrillaPx, altoGrillaPx, C);

    infoInterfazDeJuego(lineas, puntaje, puntajeMax, nivel, tetroActivo[1].tipo, resolAncho, resolAlto);

    grillaDibujarTetromino(tetroActivo, resolAncho, resolAlto, grilla->anchoGrilla);

    grillaDibujar(grilla);

    if (gbt_temporizador_consumir(*tempCaida))
    {
        tetroActivo->posY++;

        if (tetrominoColisionaSuelo(tetroActivo) || tetrominoColisionaConOtro(tetroActivo, grilla))
        {
            grillaActualizar(grilla, tetroActivo);
            actualizarVectorTetrominos(tetroActivo, CANT_TETROMINOS_CLASSIC);
            //TODO: agregar pequeÃ±o tiempo de espera antes de anclar el tetromino
        }
    }

    if (tecla == GBTK_a && !tetrominoColisionaLateralmente(tetroActivo, grilla, IZQUIERDA))
        tetroActivo->posX--;
    else if (tecla == GBTK_d && !tetrominoColisionaLateralmente(tetroActivo, grilla, DERECHA))
        tetroActivo->posX++;
    else if (tecla == GBTK_j)           //Rotacion antihoraria (TODO: verificar colision)
        tetrominoRotar(tetroActivo, ANTIHORARIO);
    else if (tecla == GBTK_l)           //Rotacion horaria    (TODO: verificar colision)
        tetrominoRotar(tetroActivo, HORARIO);
    else if (tecla == GBTK_ESCAPE || tecla == GBTK_p)
        return PAUSA;
    else if (gbt_tecla_sostenida(GBTK_s) && *modoVelocidad != VEL_RAPIDA)
    {
        gbt_temporizador_destruir(*tempCaida);
        *tempCaida = gbt_temporizador_crear(*velActual / FACTOR_VEL_RAPIDA);
        *modoVelocidad = VEL_RAPIDA;
    }
    else if (*modoVelocidad != VEL_NORMAL && !gbt_tecla_sostenida(GBTK_s))
    {
        gbt_temporizador_destruir(*tempCaida);
        *tempCaida = gbt_temporizador_crear(*velActual);
        *modoVelocidad = VEL_NORMAL;
    }

    gbt_volcar_backbuffer();
    return JUGANDO;
}

int menuPausa(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce)
{
    gbt_borrar_backbuffer(N);

    gbt_procesar_entrada();
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

    botonActualizarTodosInactivo(vecBotones, ce);
    (vecBotones + *cursor)->estado = APUNTADO;

    tBoton *i;
    tBoton *finVec = vecBotones + ce;
    for(i = vecBotones; i < finVec; i++)
        botonDibujar(i);

<<<<<<< HEAD
    if (tecla == GBTK_w)
        *cursor = (*cursor - 1 + ce) % ce;
    else if (tecla == GBTK_s)
        *cursor = (*cursor + 1) % ce;
    else if (tecla == GBTK_ESCAPE)
        return JUGANDO;
    else if (tecla == GBTK_ENTER)
    {
        switch (*cursor)
        {
            case 0: return JUGANDO;
            case 1: break;  //CARGAR PARTIDA (sin implementar)
            case 2: break;  //GUARDAR PARTIDA (sin implementar)
            case 3: break;  //CHEAT (sin implementar)
            case 4: return PANTALLA_INICIAL;
=======
    if (tecla == GBTK_w)               //'W' subir cursor
        *cursor = (*cursor - 1 + ce)%ce;                      //Evito salir del rango del vector de botones
    else if (tecla == GBTK_s)               //'S' bajar cursor
        *cursor = (*cursor + 1)%ce;                      //Evito salir del rango del vector de botones
    else if (tecla == GBTK_ESCAPE)           //'Esc' ---> Reanudar
        return JUGANDO;
    else if (tecla == GBTK_ENTER)
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
>>>>>>> bafd173e0d91aff7488c7bdf4932643df57b838d
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

<<<<<<< HEAD
int ingresarNombre(int resolAncho, int resolAlto, char nombreOut[MAX_NOMBRE])
{
    static int subEstado = 0;   // 0 = escribiendo, 1 = preguntando sobreescritura
    static char nombre[MAX_NOMBRE] = "";
    static int largo = 0;

    gbt_borrar_backbuffer(N);
    gbt_procesar_entrada();
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

    tCursorTexto cur = {(resolAncho - 5*12) / 2, 20};
    escribirTexto("INGRESE SU NOMBRE", &cur, B);

    if (subEstado == 0)
    {
        tCursorTexto curNombre = {(resolAncho - MAX_NOMBRE*6) / 2, 60};
        escribirTexto(nombre, &curNombre, AM);

        tCursorTexto curAyuda = {10, resolAlto - 20};
        escribirTexto("ENTER CONFIRMAR  ESC CANCELAR", &curAyuda, GC);

        char c = 0;
        if (tecla >= GBTK_a && tecla <= GBTK_z)
            c = 'A' + (tecla - GBTK_a);

        if (c != 0 && largo < MAX_NOMBRE - 1)
        {
            nombre[largo++] = c;
            nombre[largo] = '\0';
        }

        if (tecla == GBTK_RETROCESO && largo > 0)
            nombre[--largo] = '\0';

        if (tecla == GBTK_ENTER && largo > 0)
        {
            if (jugadorExiste(nombre))
                subEstado = 1;
            else
            {
                strcpy(nombreOut, nombre);
                tJugador nuevo;
                strcpy(nuevo.nombre, nombre);
                nuevo.puntaje_max = 0;
                jugadorGuardar(&nuevo);

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
        tCursorTexto curNombre = {(resolAncho - MAX_NOMBRE*6) / 2, 60};
        escribirTexto(nombre, &curNombre, AM);

        tCursorTexto curPregunta = {10, 90};
        escribirTexto("ESE NOMBRE YA EXISTE", &curPregunta, RB);

        tCursorTexto curOpc = {10, 110};
        escribirTexto("ENTER SOBREESCRIBIR  ESC VOLVER", &curOpc, GC);

        if (tecla == GBTK_ENTER)
        {
            strcpy(nombreOut, nombre);
            tJugador existente;
            strcpy(existente.nombre, nombre);
            existente.puntaje_max = 0;
            jugadorGuardar(&existente);

            subEstado = 0;
            nombre[0] = '\0';
            largo = 0;
            return JUGANDO;
        }

        if (tecla == GBTK_ESCAPE)
            subEstado = 0;
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
    escribirTexto("CONFIGURACION", &curTit, B);

    tCursorTexto curEtiq = {0, 40};
    escribirTexto("ANCHO GRILLA", &curEtiq, AM);

    tCursorTexto curAyuda = {0, resolAlto - 20};
    escribirTexto("A D CAMBIAR  ENTER OK  ESC VOLVER", &curAyuda, GC);

    tCursorTexto curValor = {0, 70};
    escribirNumero(*anchoGrilla, &curValor, B);  //Muestra el valor actual del ancho

    if (tecla == GBTK_a && *anchoGrilla > ANCHO_GRILLA_MIN)
        (*anchoGrilla)--;
    if (tecla == GBTK_d && *anchoGrilla < ANCHO_GRILLA_MAX)
        (*anchoGrilla)++;
    if (tecla == GBTK_ENTER || tecla == GBTK_ESCAPE)
        return MENU_PRINCIPAL_DELUXE;

    gbt_volcar_backbuffer();
    return CONFIG_DELUXE;
}

=======
>>>>>>> bafd173e0d91aff7488c7bdf4932643df57b838d
void infoInterfazDeJuego(int lineas, int puntaje, int puntajeMax, int nivel, char sigTetromino, int resolAncho, int resolAlto)
{
    int anchoCuadros = 60;
    int altoCuadros = 30;
    int espaciadoBordes = 10;
    int altoCuadroSiguiente = 50;
    int espacioEntreCuadros = (resolAlto - espaciadoBordes - 5*altoCuadros)/5;

    tCursorTexto cursor = {espaciadoBordes, espaciadoBordes};

<<<<<<< HEAD
    //Informacion de la izquierda
    dibujarCuadroTexto(cursor.posX, cursor.posY, "LINEAS: ",    lineas,     anchoCuadros, altoCuadros, M, B);
    cursor.posY += altoCuadros + espacioEntreCuadros;
    dibujarCuadroTexto(cursor.posX, cursor.posY, "SCORE: ",     puntaje,    anchoCuadros, altoCuadros, M, B);
    cursor.posY += altoCuadros + espacioEntreCuadros;
    dibujarCuadroTexto(cursor.posX, cursor.posY, "TOP SCORE: ", puntajeMax, anchoCuadros, altoCuadros, M, B);
    cursor.posY += altoCuadros + espacioEntreCuadros;
    dibujarCuadroTexto(cursor.posX, cursor.posY, "NIVEL: ",     nivel,      anchoCuadros, altoCuadros, M, B);
    cursor.posY += altoCuadros + espacioEntreCuadros;
    dibujarCuadroTexto(cursor.posX, cursor.posY, "GRUPO BYTE", SIN_INFORMACION, anchoCuadros, altoCuadros, M, B);

    //Informacion de la derecha
    cursor.posX = resolAncho - espaciadoBordes - anchoCuadros;
    cursor.posY = espaciadoBordes;
    dibujarCuadroTexto(cursor.posX, cursor.posY, "SIGUIENTE: ", SIN_INFORMACION, anchoCuadros, altoCuadroSiguiente, M, B);
=======
    //Dibujo la informacion de la izquierda
    dibujarCuadroTexto(cursor.posX, cursor.posY, "LINEAS: ", lineas, anchoCuadros, altoCuadros, M, B);         //Muestra la cantidad de lineas
    cursor.posY += altoCuadros + espacioEntreCuadros;
    dibujarCuadroTexto(cursor.posX, cursor.posY, "SCORE: ", puntaje, anchoCuadros, altoCuadros, M, B);         //Muestra el puntaje actual
    cursor.posY += altoCuadros + espacioEntreCuadros;
    dibujarCuadroTexto(cursor.posX, cursor.posY, "TOP SCORE: ", puntajeMax, anchoCuadros, altoCuadros, M, B);         //Muestra el mayor puntaje
    cursor.posY += altoCuadros + espacioEntreCuadros;
    dibujarCuadroTexto(cursor.posX, cursor.posY, "NIVEL: ", nivel, anchoCuadros, altoCuadros, M, B);         //Muestra el nivel actual
    cursor.posY += altoCuadros + espacioEntreCuadros;
    dibujarCuadroTexto(cursor.posX, cursor.posY, "GRUPO BYTE", SIN_INFORMACION, anchoCuadros, altoCuadros, M, B);         //Nuestro grupo

    //Dibujo la informacion de la derecha
    cursor.posX = resolAncho - espaciadoBordes - anchoCuadros;
    cursor.posY = espaciadoBordes;
    dibujarCuadroTexto(cursor.posX, cursor.posY, "SIGUIENTE: ", SIN_INFORMACION, anchoCuadros, altoCuadroSiguiente, M, B);  //Muestra el siguiente tetromino
>>>>>>> bafd173e0d91aff7488c7bdf4932643df57b838d

    tTetromino siguienteTetro;
    tetrominoCrear(&siguienteTetro, sigTetromino, 0, 0);

    int posXTetromino = cursor.posX + anchoCuadros/2 - (float)siguienteTetro.anchoMat/2*TAM_MINO;
    int posYTetromino = cursor.posY + altoCuadroSiguiente/2 - (float)siguienteTetro.altoMat/2*TAM_MINO + 3;
    tetrominoDibujar(&siguienteTetro, posXTetromino, posYTetromino);

    cursor.posY += altoCuadroSiguiente + espacioEntreCuadros;
    dibujarCuadroTexto(cursor.posX, cursor.posY, "STATS: ", SIN_INFORMACION, anchoCuadros, resolAlto - 2*espaciadoBordes - espacioEntreCuadros - altoCuadroSiguiente, M, B);
}

void dibujarRectangulo(int posX, int posY, int ancho, int alto, int color)
{
    int i;

<<<<<<< HEAD
    for (i = 0; i < ancho; i++)
        gbt_dibujar_pixel(posX + i, posY, color);
    for (i = 0; i < alto; i++)
        gbt_dibujar_pixel(posX + ancho - 1, posY + i, color);
    for (i = ancho - 1; i >= 0; i--)
        gbt_dibujar_pixel(posX + i, posY + alto - 1, color);
    for (i = alto - 1; i >= 0; i--)
=======
    for (i = 0; i < ancho; i++)         //Linea superior
        gbt_dibujar_pixel(posX + i, posY, color);
    for (i = 0; i < alto; i++)          //Linea derecha
        gbt_dibujar_pixel(posX + ancho - 1, posY + i, color);
    for (i = ancho - 1; i >= 0; i--)    //Linea inferior
        gbt_dibujar_pixel(posX + i, posY + alto - 1, color);
    for (i = alto - 1; i >= 0; i--)     //Linea izquierda
>>>>>>> bafd173e0d91aff7488c7bdf4932643df57b838d
        gbt_dibujar_pixel(posX, posY + i, color);
}

void dibujarCuadroTexto(int posX, int posY, const char str[], int parametro, int ancho, int alto, int colorCuadro, int colorTexto)
{
    tCursorTexto cursor = {posX + 2, posY + 2};

    dibujarRectangulo(posX, posY, ancho, alto, colorCuadro);
<<<<<<< HEAD
=======

>>>>>>> bafd173e0d91aff7488c7bdf4932643df57b838d
    escribirTexto(str, &cursor, colorTexto);

    if (parametro != SIN_INFORMACION)
    {
        cursor.posX = posX + 2;
        cursor.posY += 2*ALTO_ESTANDAR_LETRA + 2;
        escribirNumero(parametro, &cursor, colorTexto);
    }
}
