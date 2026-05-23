#include "tPantalla.h"
#include "tOpciones.h"
#include "tPartida.h"

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
                return INGRESO_NOMBRE;         //Empieza la partida
            case 1:
                return INGRESO_NOMBRE_CARGA;
            case 2:
                return OPCIONES;
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
                return INGRESO_NOMBRE;         //Empieza la partida
            case 1:
                return INGRESO_NOMBRE_CARGA;
            case 2:
                return OPCIONES;
            case 3:
                return PANTALLA_INICIAL;
        }
    }

    gbt_volcar_backbuffer();

    return MENU_PRINCIPAL_DELUXE;
}

int interfazJuego(int resolAncho, int resolAlto, tTetromino tetroActivo[TAM_VEC_TETROMINOS], tGrilla *grilla, tGBT_Temporizador **tempCaida, tGBT_Temporizador **tempInactiv, double *velActual, int *modoVelocidad, bool modo, int *puntaje, int *lineas, int *nivel)
{

    int puntajeMax = 0;   // TODO: leer del jugador guardado

    gbt_borrar_backbuffer(N);
    gbt_procesar_entrada();
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

    int anchoGrillaPx = grilla->anchoGrilla * TAM_MINO;
    int altoGrillaPx  = ALTO_GRILLA_VISIBLE * TAM_MINO;

    infoInterfazDeJuego(*lineas,*puntaje,puntajeMax, *nivel, tetroActivo[1].tipo, resolAncho, resolAlto);
    grillaDibujarTetromino(tetroActivo, resolAncho, resolAlto, grilla->anchoGrilla);
    grillaDibujar(grilla);
    dibujarRectangulo((resolAncho - anchoGrillaPx)/2, (resolAlto - altoGrillaPx)/2, anchoGrillaPx, altoGrillaPx, C);

    if (gbt_temporizador_consumir(*tempCaida))
    {
        tetroActivo->posY++;

        if (tetrominoColisionaSuelo(tetroActivo) || tetrominoColisionaConOtro(tetroActivo, grilla))
        {
            grillaActualizar(grilla, tetroActivo);
            actualizarVectorTetrominos(tetroActivo, modo ? CANT_TETROMINOS_DELUXE : CANT_TETROMINOS_CLASSIC );
            //TODO: agregar pequeño tiempo de espera antes de anclar el tetromino
        }
    }

    if (tecla == GBTK_a && !tetrominoColisionaLateralmente(tetroActivo, grilla, IZQUIERDA))
        tetroActivo->posX--;
    else if (tecla == GBTK_d && !tetrominoColisionaLateralmente(tetroActivo, grilla, DERECHA))
        tetroActivo->posX++;
    else if (tecla == GBTK_j || tecla == GBTK_q)           //Rotacion antihoraria (TODO: verificar colision)
        tetrominoRotar(tetroActivo, ANTIHORARIO);
    else if (tecla == GBTK_l || tecla == GBTK_e)           //Rotacion horaria    (TODO: verificar colision)
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
                    return CARGAR_PARTIDA;
                    break;                  //CARGAR PARTIDA
                case 2:
                   return GUARDAR_PARTIDA;
                    break;                  //GUARDAR PARTIDA
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

int menuOpciones(int resolAncho, int resolAlto, int *nuevoAncho, int *nuevoAlto, double *velCaida, int *anchoGrilla, bool modoDeluxe)
{
    static int tempAncho  = 0;
    static int tempAlto   = 0;
    static int tempVelIdx = 1;
    static int tempGrilla = 0;
    static bool iniciado  = false;
    static int cursorOpc  = 0;

    const char *nombresVel[3] = {"RAPIDO", "NORMAL", "LENTO"};
    const double valoresVel[3] = {VEL_CAIDA_RAPIDO, VEL_CAIDA_DEFAULT, VEL_CAIDA_LENTO};

    int cantItems = modoDeluxe ? 3 : 2;

    if (!iniciado)
    {
        tempAncho  = *nuevoAncho;
        tempAlto   = *nuevoAlto;
        tempGrilla = *anchoGrilla;

        if (*velCaida == VEL_CAIDA_RAPIDO)
            tempVelIdx = 0;
        else if (*velCaida == VEL_CAIDA_LENTO)
            tempVelIdx = 2;
        else
            tempVelIdx = 1;

        iniciado = true;
    }

    gbt_borrar_backbuffer(N);
    gbt_procesar_entrada();
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

    // Titulo
    tCursorTexto cur = {(resolAncho - 8*6) / 2, 12};
    escribirTexto("OPCIONES", &cur, B);

    // Items
    int margenIzq  = 15;
    int margenVal  = 120;
    int primerFila = 40;
    int separFila  = 18;

    // RESOLUCION
    cur.posX = margenIzq;
    cur.posY = primerFila;
    escribirTexto("RESOLUCION", &cur, cursorOpc == 0 ? AM : GC);
    cur.posX = margenVal;
    escribirTexto(" ", &cur, cursorOpc == 0 ? AM : GC);
    if (tempAncho == ANCHO_VENTANA_CGA)
        escribirTexto("CGA 320X200", &cur, cursorOpc == 0 ? AM : GC);
    else
        escribirTexto("VGA 640X480", &cur, cursorOpc == 0 ? AM : GC);
    escribirTexto(" ", &cur, cursorOpc == 0 ? AM : GC);

    // VELOCIDAD DE CAIDA
    cur.posX = margenIzq;
    cur.posY = primerFila + separFila;
    escribirTexto("VELOCIDAD DE CAIDA", &cur, cursorOpc == 1 ? AM : GC);
    cur.posX = margenVal;
    escribirTexto(" ", &cur, cursorOpc == 1 ? AM : GC);
    escribirTexto(nombresVel[tempVelIdx], &cur, cursorOpc == 1 ? AM : GC);
    escribirTexto(" ", &cur, cursorOpc == 1 ? AM : GC);

    // ANCHO GRILLA (solo deluxe)
    if (modoDeluxe)
    {
        cur.posX = margenIzq;
        cur.posY = primerFila + 2*separFila;
        escribirTexto("ANCHO GRILLA", &cur, cursorOpc == 2 ? AM : GC);
        cur.posX = margenVal;
        escribirTexto(" ", &cur, cursorOpc == 2 ? AM : GC);
        escribirNumero(tempGrilla, &cur, cursorOpc == 2 ? AM : GC);
        escribirTexto(" ", &cur, cursorOpc == 2 ? AM : GC);
    }

    // Ayuda
    cur.posX = margenIzq;
    cur.posY = resolAlto - 20;
    escribirTexto("W S NAVEGAR  A D CAMBIAR", &cur, GO);
    cur.posX = margenIzq;
    cur.posY += 10;
    escribirTexto("ENTER APLICAR  ESC CANCELAR", &cur, GO);

    // Navegacion vertical
    if (tecla == GBTK_w)
        cursorOpc = (cursorOpc - 1 + cantItems) % cantItems;
    else if (tecla == GBTK_s)
        cursorOpc = (cursorOpc + 1) % cantItems;

    // Cambio de valor
    else if (tecla == GBTK_a || tecla == GBTK_d)
    {
        int dir = (tecla == GBTK_d) ? 1 : -1;

        switch (cursorOpc)
        {
            case 0:   // Resolucion: toggle entre CGA y VGA
                if (tempAncho == ANCHO_VENTANA_CGA)
                {
                    tempAncho = ANCHO_VENTANA_VGA;
                    tempAlto  = ALTO_VENTANA_VGA;
                }
                else
                {
                    tempAncho = ANCHO_VENTANA_CGA;
                    tempAlto  = ALTO_VENTANA_CGA;
                }
                break;

            case 1:   // Velocidad de caida
                tempVelIdx = (tempVelIdx + dir + 3) % 3;
                break;

            case 2:   // Ancho grilla
                if (dir == 1 && tempGrilla < ANCHO_GRILLA_MAX)
                    tempGrilla++;
                else if (dir == -1 && tempGrilla > ANCHO_GRILLA_MIN)
                    tempGrilla--;
                break;
        }
    }

    // ENTER: aplicar y volver
    else if (tecla == GBTK_ENTER)
    {
        *nuevoAncho  = tempAncho;
        *nuevoAlto   = tempAlto;
        *velCaida    = valoresVel[tempVelIdx];
        *anchoGrilla = tempGrilla;

    // Guardar opciones en archivo
        tOpciones op;
        op.resolAncho  = tempAncho;
        op.resolAlto   = tempAlto;
        op.velCaida    = valoresVel[tempVelIdx];
        op.anchoGrilla = tempGrilla;
        op.paleta      = 0;
        opcionesGuardar(&op);

        iniciado  = false;
        cursorOpc = 0;

        gbt_volcar_backbuffer();
        return modoDeluxe ? MENU_PRINCIPAL_DELUXE : MENU_PRINCIPAL_CLASSIC;
    }

    // ESC: cancelar sin aplicar
    else if (tecla == GBTK_ESCAPE)
    {
        iniciado  = false;
        cursorOpc = 0;

        gbt_volcar_backbuffer();
        return modoDeluxe ? MENU_PRINCIPAL_DELUXE : MENU_PRINCIPAL_CLASSIC;
    }

    gbt_volcar_backbuffer();
    return OPCIONES;
}

int ingresarNombre(int resolAncho, int resolAlto, char nombreOut[MAX_NOMBRE])
{
    static int subEstado = 0;
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
        escribirTexto("JUGADOR YA EXISTE", &curPregunta, RB);

        tCursorTexto curOpc = {10, 110};
        escribirTexto("ENTER NUEVA PARTIDA  ESC VOLVER", &curOpc, GC);

        if (tecla == GBTK_ENTER)
        {
            strcpy(nombreOut, nombre);
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

int ingresarNombreCarga(int resolAncho, int resolAlto, char nombreOut[MAX_NOMBRE], bool modoDeluxe)
{
    static char nombre[MAX_NOMBRE] = "";
    static int  largo = 0;
    static int  subEstado = 0;  // 0 = escribiendo, 1 = exito, 2 = no encontrada

    gbt_borrar_backbuffer(N);
    gbt_procesar_entrada();
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

    tCursorTexto cur = {(resolAncho - 14*6) / 2, 20};
    escribirTexto("CARGAR PARTIDA", &cur, B);

    if (subEstado == 0)
    {
        tCursorTexto curNombre = {(resolAncho - MAX_NOMBRE*6) / 2, 60};
        escribirTexto(nombre, &curNombre, AM);

        tCursorTexto curAyuda = {10, resolAlto - 20};
        escribirTexto("ENTER CONFIRMAR  ESC CANCELAR", &curAyuda, GO);

        char c = 0;
        if (tecla >= GBTK_a && tecla <= GBTK_z)
            c = 'A' + (tecla - GBTK_a);

        if (c != 0 && largo < MAX_NOMBRE - 1)
        {
            nombre[largo++] = c;
            nombre[largo]   = '\0';
        }

        if (tecla == GBTK_RETROCESO && largo > 0)
            nombre[--largo] = '\0';

        if (tecla == GBTK_ENTER && largo > 0)
        {
            tPartida temp;
            if (partidaCargar(nombre, modoDeluxe, &temp))
                subEstado = 1;
            else
                subEstado = 2;
        }

        if (tecla == GBTK_ESCAPE)
        {
            nombre[0] = '\0';
            largo = 0;
            subEstado = 0;
            gbt_volcar_backbuffer();
            return PANTALLA_INICIAL;
        }
    }
    else if (subEstado == 1)
    {
        tCursorTexto curOk = {10, 90};
        escribirTexto("PARTIDA CARGADA CON EXITO", &curOk, VB);
        tCursorTexto curOpc = {10, 110};
        escribirTexto("ENTER CONTINUAR", &curOpc, GC);

        if (tecla == GBTK_ENTER)
        {
            strcpy(nombreOut, nombre);
            nombre[0] = '\0';
            largo = 0;
            subEstado = 0;
            gbt_volcar_backbuffer();
            return CARGAR_PARTIDA;
        }
    }
    else if (subEstado == 2)
    {
        tCursorTexto curErr = {10, 90};
        escribirTexto("PARTIDA NO ENCONTRADA", &curErr, RB);
        tCursorTexto curOpc = {10, 110};
        escribirTexto("ENTER VOLVER", &curOpc, GC);

        if (tecla == GBTK_ENTER)
            subEstado = 0;
    }

    gbt_volcar_backbuffer();
    return INGRESO_NOMBRE_CARGA;
}

void infoInterfazDeJuego(int lineas, int puntaje, int puntajeMax, int nivel, char sigTetromino, int resolAncho, int resolAlto)
{
    int anchoCuadros = 60;
    int altoCuadros = 30;
    int espaciadoBordes = 10;
    int altoCuadroSiguiente = 50;
    int espacioEntreCuadros = (resolAlto - espaciadoBordes - 5*altoCuadros)/5;

    tCursorTexto cursor = {espaciadoBordes, espaciadoBordes};

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

    for (i = 0; i < ancho; i++)         //Linea superior
        gbt_dibujar_pixel(posX + i, posY, color);
    for (i = 0; i < alto; i++)          //Linea derecha
        gbt_dibujar_pixel(posX + ancho - 1, posY + i, color);
    for (i = ancho - 1; i >= 0; i--)    //Linea inferior
        gbt_dibujar_pixel(posX + i, posY + alto - 1, color);
    for (i = alto - 1; i >= 0; i--)     //Linea izquierda
        gbt_dibujar_pixel(posX, posY + i, color);
}

void dibujarCuadroTexto(int posX, int posY, const char str[], int parametro, int ancho, int alto, int colorCuadro, int colorTexto)
{
    tCursorTexto cursor = {posX + 2, posY + 2};
    dibujarRectangulo(posX, posY, ancho, alto, colorCuadro);
    escribirTexto(str, &cursor, colorTexto);

    if (parametro != SIN_INFORMACION)
    {
        cursor.posX = posX + 2;
        cursor.posY += 2*ALTO_ESTANDAR_LETRA + 2;
        escribirNumero(parametro, &cursor, colorTexto);
    }
}

int confirmarSobreescritura(int resolAncho, int resolAlto)
{
    gbt_borrar_backbuffer(N);
    gbt_procesar_entrada();
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

    tCursorTexto cur = {(resolAncho - 30*6) / 2, resolAlto/2 - 20};
    escribirTexto("YA EXISTE UNA PARTIDA GUARDADA", &cur, RB);

    //cur.posX = (resolAncho - 16*6) / 2;
    //cur.posY += 12;
    //escribirTexto("PRESIONA ENTER PARA SOBREE", &cur, B);

    cur.posX = 10;
    cur.posY += 26;
    escribirTexto("ENTER SOBREESCRIBIR  ESC CANCELAR", &cur, GC);

    gbt_volcar_backbuffer();

    if (tecla == GBTK_ENTER)
        return GUARDAR_PARTIDA;
    if (tecla == GBTK_ESCAPE)
        return PAUSA;

    return CONFIRMAR_SOBREESCRITURA;
}
