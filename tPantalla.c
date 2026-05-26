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

    int _escala = (resolAncho >= 640) ? ESCALA_TITULO * 2 : ESCALA_TITULO;
    int _tituloY = (resolAncho >= 640) ? resolAlto / 4 : 30;
    int anchoLetraConEspacio = (5 + ESPACIADO_ENTRE_LETRAS) * _escala;
    int anchoTotalTitulo = anchoLetraConEspacio * 6;

    tCursorTexto cursorTitulo = { (resolAncho - anchoTotalTitulo) / 2, _tituloY };

    caracterDibujarEscalado('T', &cursorTitulo, R,  _escala);
    caracterDibujarEscalado('E', &cursorTitulo, AZ, _escala);
    caracterDibujarEscalado('T', &cursorTitulo, M, _escala);
    caracterDibujarEscalado('R', &cursorTitulo, VI,  _escala);
    caracterDibujarEscalado('I', &cursorTitulo, AM, _escala);
    caracterDibujarEscalado('S', &cursorTitulo, VE, _escala);

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

int interfazJuego(int infoJuego[CANT_TETROMINOS_DELUXE + DATOS_DE_JUEGO], tTetromino tetroActivo[TAM_VEC_TETROMINOS], tGrilla *grilla, tGBT_Temporizador **tempCaida, tGBT_Temporizador **tempFijacion, double *velActual)
{
//    int puntajeMax = 0;   // TODO: leer del jugador guardado
    gbt_borrar_backbuffer(N);
    gbt_procesar_entrada();
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

    int anchoGrillaPx = grilla->anchoGrilla * TAM_MINO;
    int altoGrillaPx  = ALTO_GRILLA_VISIBLE * TAM_MINO;

    infoInterfazDeJuego(infoJuego, tetroActivo[1].tipo,(int)(1000*(*velActual)));
    grillaDibujarTetromino(tetroActivo, infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO], grilla->anchoGrilla, infoJuego[MODO_DE_JUEGO]);
    grillaDibujar(grilla, infoJuego[RESOL_ANCHO], infoJuego[RESOL_ALTO]);
    dibujarRectangulo((infoJuego[RESOL_ANCHO] - anchoGrillaPx)/2, (infoJuego[RESOL_ALTO] - altoGrillaPx)/2, anchoGrillaPx, altoGrillaPx, C);

    if (infoJuego[TETROMINO_LIBRE])
    {
        gbt_temporizador_pausar(*tempFijacion);
        gbt_temporizador_reanudar(*tempCaida);
    }


    if (gbt_temporizador_consumir(*tempFijacion))
    {
        infoJuego[TETROMINOS_COLOCADOS]++;

        if (infoJuego[TETROMINOS_COLOCADOS]%10 == 0 && infoJuego[TETROMINOS_COLOCADOS] != 0)    //Cada 10 tetrominos colcoados, aumentar la velocidad
        {
            *velActual /= FACTOR_AUMENTO_VEL;
            gbt_temporizador_destruir(*tempCaida);
            *tempCaida = gbt_temporizador_crear(*velActual);

            infoJuego[NIVEL]++;
        }

        if (tetroActivo->posY <= 0)         //Si el tetromino se bloquea tocando el techo, se termina la partida
            return GAME_OVER;

        infoJuego[(int)tetroActivo->tipo]++;        //Aumento en 1 la cantidad de tetrominos de ese tipo colocados

        grillaActualizar(grilla, tetroActivo, infoJuego[MODO_DE_JUEGO]);      //Guarda el tetromino colisionado en la grilla

        int cantidadLineas = grillaChequearLinea(grilla, tetroActivo);  //Si hay lineas completas, las elimina
        if (cantidadLineas)
        {
            infoJuego[LINEAS] += cantidadLineas;  //Se aumenta la cantidad de lineas completas
            infoJuego[SCORE] += SCORE_LINEA*cantidadLineas*pow(PORCENT_EXTRA_LINEA, cantidadLineas - 1)/(*velActual);
        }

        actualizarVectorTetrominos(tetroActivo, infoJuego[MODO_DE_JUEGO] ? CANT_TETROMINOS_DELUXE : CANT_TETROMINOS_CLASSIC, infoJuego, grilla->anchoGrilla); //Crea un nuevo tetromino y lo coloca al final del vector

        gbt_temporizador_pausar(*tempFijacion);
        gbt_temporizador_reanudar(*tempCaida);
        infoJuego[TETROMINO_LIBRE] = 1;
    }

    if (!infoJuego[CHEATS_ACTIVADOS]) //Sin CHEATS activados
    {
        if (gbt_temporizador_consumir(*tempCaida))
        {
            tetroActivo->posY++;
            if (infoJuego[MODO_VELOCIDAD] == MODO_VEL_RAPIDA)
                infoJuego[SCORE] += SCORE_CAIDA_RAPIDA/(*velActual);    //Si se deposita un tetromino mantieniendo 'S' presionado, se gana puntaje extra

            if (tetrominoColisionaSuelo(tetroActivo) || tetrominoColisionaConOtro(tetroActivo, grilla,infoJuego[MODO_DE_JUEGO]))
            {
                tetroActivo->posY--;        //Si ya colisiono, entonces hay que revertir la ultima bajada del tetromino
                infoJuego[TETROMINO_LIBRE] = 0;
                gbt_temporizador_pausar(*tempCaida);
                gbt_temporizador_reanudar(*tempFijacion);
            }
        }
    }
    else    //Con CHEATS activados
    {
        if (tecla == GBTK_s)
        {
            tetroActivo->posY++;

            if (tetrominoColisionaSuelo(tetroActivo) || tetrominoColisionaConOtro(tetroActivo, grilla, infoJuego[MODO_DE_JUEGO]))
            {
                tetroActivo->posY--;        //Si ya colisiono, entonces hay que revertir la ultima bajada del tetromino
                infoJuego[TETROMINO_LIBRE] = 0;
                gbt_temporizador_pausar(*tempCaida);
                gbt_temporizador_reanudar(*tempFijacion);
            }
        }

    }



    if (tecla == GBTK_a && !tetrominoColisionaLateralmente(tetroActivo, grilla, IZQUIERDA,infoJuego[MODO_DE_JUEGO]))
    {
        tetroActivo->posX--;
        if(!infoJuego[TETROMINO_LIBRE])
        {
            if (!tetrominoColisionaSuelo(tetroActivo) && !tetrominoColisionaConOtro(tetroActivo, grilla,infoJuego[MODO_DE_JUEGO]))
                infoJuego[TETROMINO_LIBRE] = 1;

            gbt_temporizador_destruir(*tempFijacion);
            *tempFijacion = gbt_temporizador_crear(*velActual/2);
            if (!(*tempFijacion))
                return ERROR_INTERNO_JUEGO;
        }
    }

    else if (tecla == GBTK_d && !tetrominoColisionaLateralmente(tetroActivo, grilla, DERECHA,infoJuego[MODO_DE_JUEGO]))
    {
        tetroActivo->posX++;
        if(!infoJuego[TETROMINO_LIBRE])
        {
            if (!tetrominoColisionaSuelo(tetroActivo) && !tetrominoColisionaConOtro(tetroActivo, grilla,infoJuego[MODO_DE_JUEGO]))
                infoJuego[TETROMINO_LIBRE] = 1;

            gbt_temporizador_destruir(*tempFijacion);
            *tempFijacion = gbt_temporizador_crear(*velActual/2);
            if (!(*tempFijacion))
                return ERROR_INTERNO_JUEGO;
        }
    }
    else if (tecla == GBTK_j || tecla == GBTK_q)
    {
        tetrominoRotar(tetroActivo, HORARIO);
        if (tetrominoColisionaConOtro(tetroActivo, grilla,infoJuego[MODO_DE_JUEGO]))
        {
            tetrominoRotar(tetroActivo, ANTIHORARIO);
        }
    }
    else if (tecla == GBTK_l || tecla == GBTK_e)
    {
        tetrominoRotar(tetroActivo, HORARIO);
        if (tetrominoColisionaConOtro(tetroActivo, grilla,infoJuego[MODO_DE_JUEGO]))
        {
            tetrominoRotar(tetroActivo, ANTIHORARIO);
        }
    }
    else if (tecla == GBTK_ESCAPE || tecla == GBTK_p)
        return PAUSA;
    else if (gbt_tecla_sostenida(GBTK_s) && infoJuego[MODO_VELOCIDAD] != MODO_VEL_RAPIDA)
    {
        gbt_temporizador_destruir(*tempCaida);
        *tempCaida = gbt_temporizador_crear(*velActual / FACTOR_VEL_RAPIDA);
        infoJuego[MODO_VELOCIDAD] = MODO_VEL_RAPIDA;
    }
    else if (infoJuego[MODO_VELOCIDAD] != MODO_VEL_NORMAL && !gbt_tecla_sostenida(GBTK_s))
    {
        gbt_temporizador_destruir(*tempCaida);
        *tempCaida = gbt_temporizador_crear(*velActual);
        infoJuego[MODO_VELOCIDAD] = MODO_VEL_NORMAL;
    }

    if (infoJuego[SCORE] > infoJuego[TOP_SCORE])
    infoJuego[TOP_SCORE] = infoJuego[SCORE];

    gbt_volcar_backbuffer();
    return JUGANDO;
}

int menuPausa(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce, int *cheatsActivos)
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
            return CARGAR_PARTIDA;  //CARGAR PARTIDA
        case 2:
            return GUARDAR_PARTIDA; //GUARDAR PARTIDA
        case 3:
            *cheatsActivos = !(*cheatsActivos);
            return JUGANDO;
        case 4:
            return PANTALLA_INICIAL; //VUELVE AL MENU
        }
    }

    gbt_volcar_backbuffer();
    return PAUSA;
}

int gameOver(int resolAncho, int resolAlto, int* cursor, tBoton *vecBotones, int ce, int score)
{
    gbt_borrar_backbuffer(N);
    gbt_procesar_entrada();
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

    int _sy = resolAlto / 200; if (_sy < 1) _sy = 1;
    int anchoLetraConEspacio = (5 + ESPACIADO_ENTRE_LETRAS) * ESCALA_TITULO;
    int anchoTotalTitulo = anchoLetraConEspacio * 9;
    tCursorTexto cursorTitulo = { (resolAncho - anchoTotalTitulo) / 2, 20*_sy };

    caracterDibujarEscalado('G', &cursorTitulo, R, ESCALA_TITULO);
    caracterDibujarEscalado('A', &cursorTitulo, R, ESCALA_TITULO);
    caracterDibujarEscalado('M', &cursorTitulo, R, ESCALA_TITULO);
    caracterDibujarEscalado('E', &cursorTitulo, R, ESCALA_TITULO);
    cursorTitulo.posX += anchoLetraConEspacio;
    caracterDibujarEscalado('O', &cursorTitulo, R, ESCALA_TITULO);
    caracterDibujarEscalado('V', &cursorTitulo, R, ESCALA_TITULO);
    caracterDibujarEscalado('E', &cursorTitulo, R, ESCALA_TITULO);
    caracterDibujarEscalado('R', &cursorTitulo, R, ESCALA_TITULO);

    tCursorTexto curScore = { (resolAncho - 14*6) / 2, 70*_sy };
    escribirTexto("SCORE FINAL: ", &curScore, B);
    escribirNumero(score, &curScore, AM);

    botonActualizarTodosInactivo(vecBotones, ce);
    (vecBotones + *cursor)->estado = APUNTADO;

    for(int i = 0; i < ce; i++)
        botonDibujar(&vecBotones[i]);

    if (tecla == GBTK_w)
        *cursor = (*cursor - 1 + ce) % ce;
    else if (tecla == GBTK_s)
        *cursor = (*cursor + 1) % ce;
    else if (tecla == GBTK_ENTER)
    {
        switch (*cursor)
        {
        case 0:
            return JUGANDO;
        case 1:
            return CARGAR_PARTIDA;  // Usa el nombre del jugador actual, sin pedirlo de nuevo
        case 2:
            return PANTALLA_INICIAL;
        }
    }

    gbt_volcar_backbuffer();
    return GAME_OVER;
}

int menuOpciones(int resolAncho, int resolAlto, int *nuevoAncho, int *nuevoAlto, double *velCaida, int *anchoGrilla, bool modoDeluxe)
{
    static int tempAncho  = 0;
    static int tempAlto   = 0;
    static int tempVelIdx = 1;
    static int tempGrilla = 0;
    static int tempPaleta = 0;
    static bool iniciado  = false;
    static int cursorOpc  = 0;
    static int estadoPaleta = 0;

    const char *nombresVel[3] = {"RAPIDO", "NORMAL", "LENTO"};
    const double valoresVel[3] = {VEL_CAIDA_RAPIDO, VEL_CAIDA_DEFAULT, VEL_CAIDA_LENTO};

    int cantItems = modoDeluxe ? 4 : 3;

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

    //SELECCION DE COLOR
    cur.posX = margenIzq;
    cur.posY = primerFila + 2*separFila;
    escribirTexto("PALETA", &cur, cursorOpc == 2 ? AM : GC);
    cur.posX = margenVal;
    escribirTexto(" ", &cur, cursorOpc == 2 ? AM : GC);
    if (tempPaleta == 0)
        escribirTexto("CLASICA", &cur, cursorOpc == 2 ? AM : GC);
    else
        escribirTexto("SHINY", &cur, cursorOpc == 2 ? AM : GC);
    escribirTexto(" ", &cur, cursorOpc == 2 ? AM : GC);

    // ANCHO GRILLA (solo deluxe)
    if (modoDeluxe)
    {
        cur.posX = margenIzq;
        cur.posY = primerFila + 3*separFila;
        escribirTexto("ANCHO GRILLA", &cur, cursorOpc == 3 ? AM : GC);
        cur.posX = margenVal;
        escribirTexto(" ", &cur, cursorOpc == 3 ? AM : GC);
        escribirNumero(tempGrilla, &cur, cursorOpc == 3 ? AM : GC);
        escribirTexto(" ", &cur, cursorOpc == 3 ? AM : GC);
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
            case 2: // Paleta
                tempPaleta = (tempPaleta == 0) ? 1 : 0;

                if (tempPaleta == 0)
                    estadoPaleta= gbt_aplicar_paleta(paletaCGA,CANT_COLORES,GBT_FORMATO_888);
                else
                    estadoPaleta= gbt_aplicar_paleta(paletaVGA,CANT_COLORES,GBT_FORMATO_888);

                if (estadoPaleta != 0)
                {
                    tempPaleta = (tempPaleta == 0) ? 1 : 0;
                }

                break;

            case 3:   // Ancho grilla
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

int confirmarSobreescritura(int resolAncho, int resolAlto)
{
    gbt_borrar_backbuffer(N);
    gbt_procesar_entrada();
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

    tCursorTexto cur = {(resolAncho - 30*6) / 2, resolAlto/2 - 20};
    escribirTexto("YA EXISTE UNA PARTIDA GUARDADA", &cur, RB);

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

int ingresarNombre(int resolAncho, int resolAlto, char nombreOut[MAX_NOMBRE])
{
    static int subEstado = 0;
    static char nombre[MAX_NOMBRE] = "";
    static int largo = 0;

    gbt_borrar_backbuffer(N);
    gbt_procesar_entrada();
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

    int _sy = resolAlto / 200; if (_sy < 1) _sy = 1;
    tCursorTexto cur = {(resolAncho - 5*12) / 2, 20*_sy};
    escribirTexto("INGRESE SU NOMBRE", &cur, B);

    if (subEstado == 0)
    {
        tCursorTexto curNombre = {(resolAncho - MAX_NOMBRE*6) / 2, 60*_sy};
        escribirTexto(nombre, &curNombre, AM);

        tCursorTexto curAyuda = {10, resolAlto - 20*_sy};
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
        tCursorTexto curNombre = {(resolAncho - MAX_NOMBRE*6) / 2, 60*_sy};
        escribirTexto(nombre, &curNombre, AM);

        tCursorTexto curPregunta = {10, 90*_sy};
        escribirTexto("JUGADOR YA EXISTE", &curPregunta, RB);

        tCursorTexto curOpc = {10, 110*_sy};
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

    int _sy = resolAlto / 200; if (_sy < 1) _sy = 1;
    tCursorTexto cur = {(resolAncho - 14*6) / 2, 20*_sy};
    escribirTexto("CARGAR PARTIDA", &cur, B);

    if (subEstado == 0)
    {
        tCursorTexto curNombre = {(resolAncho - MAX_NOMBRE*6) / 2, 60*_sy};
        escribirTexto(nombre, &curNombre, AM);

        tCursorTexto curAyuda = {10, resolAlto - 20*_sy};
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
        tCursorTexto curOk = {10, 90*_sy};
        escribirTexto("PARTIDA CARGADA CON EXITO", &curOk, VB);
        tCursorTexto curOpc = {10, 110*_sy};
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
        tCursorTexto curErr = {10, 90*_sy};
        escribirTexto("PARTIDA NO ENCONTRADA", &curErr, RB);
        tCursorTexto curOpc = {10, 110*_sy};
        escribirTexto("ENTER VOLVER", &curOpc, GC);

        if (tecla == GBTK_ENTER)
            subEstado = 0;
    }

    gbt_volcar_backbuffer();
    return INGRESO_NOMBRE_CARGA;
}

void infoInterfazDeJuego(int infoJuego[CANT_TETROMINOS_DELUXE + DATOS_DE_JUEGO], char sigTetromino, int velActual)
{
    int _sx = infoJuego[RESOL_ANCHO] / 320; if (_sx < 1) _sx = 1;
    int _sy = infoJuego[RESOL_ALTO]  / 200; if (_sy < 1) _sy = 1;
    int espaciadoBordes = (infoJuego[RESOL_ANCHO] >= 640) ? 20 * _sy : 4;
    int espacioEntreCuadros = 2 * _sy;
    int anchoGrillaMaxPx = (infoJuego[MODO_DE_JUEGO] == MODO_DELUXE ? ANCHO_GRILLA_MAX : ANCHO_GRILLA_DEFAULT) * TAM_MINO;
    int margenDisponible = (infoJuego[RESOL_ANCHO] - anchoGrillaMaxPx) / 2 - 2 * espaciadoBordes;
    int anchoCuadros = (90 * _sx < margenDisponible) ? 90 * _sx : margenDisponible;
    int altoCuadros = (infoJuego[RESOL_ANCHO] >= 640)
        ? (infoJuego[RESOL_ALTO] - 2*espaciadoBordes - 4*espacioEntreCuadros) / 12
        : 2 + 2*ALTO_ESTANDAR_LETRA + 2 + ALTO_ESTANDAR_LETRA + 2;
    int altoCuadroSiguiente = altoCuadros * 2 + espacioEntreCuadros + (infoJuego[RESOL_ANCHO] >= 640 ? TAM_MINO : 0);

    tCursorTexto cursor = {espaciadoBordes, espaciadoBordes};

    //Dibujo la informacion de la izquierda
    dibujarCuadroTexto(cursor.posX, cursor.posY, "LINEAS: ", infoJuego[LINEAS], anchoCuadros, altoCuadros, M, B);         //Muestra la cantidad de lineas
    cursor.posY += altoCuadros + espacioEntreCuadros;
    dibujarCuadroTexto(cursor.posX, cursor.posY, "SCORE: ", infoJuego[SCORE], anchoCuadros, altoCuadros, M, B);         //Muestra el puntaje actual
    cursor.posY += altoCuadros + espacioEntreCuadros;
    dibujarCuadroTexto(cursor.posX, cursor.posY, "TOP SCORE: ", infoJuego[TOP_SCORE], anchoCuadros, altoCuadros, M, B);         //Muestra el mayor puntaje
    cursor.posY += altoCuadros + espacioEntreCuadros;
    dibujarRectangulo(cursor.posX, cursor.posY, anchoCuadros, altoCuadros, M);
    cursor.posX += 2;
    cursor.posY += 2;
    escribirTexto("NIVEL: ", &cursor, B);           //Muestra el nivel actual y la velocidad actual
    escribirNumero(infoJuego[NIVEL], &cursor, B);
    cursor.posX = espaciadoBordes + 2;
    cursor.posY += 2*ALTO_ESTANDAR_LETRA + 2;
    escribirTexto("VELOCIDAD: ", &cursor, B);           //Muestra el nivel actual y la velocidad actual
    escribirNumero(velActual, &cursor, B);
    cursor.posX = espaciadoBordes;
    cursor.posY -= 2*ALTO_ESTANDAR_LETRA + 4;

    cursor.posY += altoCuadros + espacioEntreCuadros;
    dibujarCuadroTexto(cursor.posX, cursor.posY, "GRUPO BYTE", SIN_INFORMACION, anchoCuadros, altoCuadros, M, B);         //Nuestro grupo

    if (infoJuego[CHEATS_ACTIVADOS])
    {
        tCursorTexto cursorCheat = {espaciadoBordes + 2, cursor.posY + altoCuadros - ALTO_ESTANDAR_LETRA - 2};
        escribirTexto("CHEAT: ON", &cursorCheat, R);
    }

    //Dibujo la informacion de la derecha
    cursor.posX = infoJuego[RESOL_ANCHO] - espaciadoBordes - anchoCuadros;
    cursor.posY = espaciadoBordes;
    dibujarCuadroTexto(cursor.posX, cursor.posY, "SIGUIENTE: ", SIN_INFORMACION, anchoCuadros, altoCuadroSiguiente, M, B);  //Muestra el siguiente tetromino

    tTetromino siguienteTetro;
    tetrominoCrear(&siguienteTetro, sigTetromino, 0, 0);

    int posXTetromino = cursor.posX + anchoCuadros/2 - (float)siguienteTetro.anchoMat/2*TAM_MINO;
    int posYTetromino = cursor.posY + altoCuadroSiguiente/2 - (float)siguienteTetro.altoMat/2*TAM_MINO + 3;
    tetrominoDibujar(&siguienteTetro, posXTetromino, posYTetromino);

    int posXStats = cursor.posX;
    cursor.posY += altoCuadroSiguiente + espacioEntreCuadros;
    int altoStats = (infoJuego[RESOL_ALTO] - 2*espaciadoBordes - espacioEntreCuadros - altoCuadroSiguiente);
    if (infoJuego[RESOL_ANCHO] >= 640) altoStats = altoStats / 2;
    dibujarCuadroTexto(posXStats, cursor.posY, "STATS: ", SIN_INFORMACION, anchoCuadros, altoStats, M, VE);

    int separStats = (infoJuego[RESOL_ANCHO] >= 640) ? 2 : 1;

    cursor.posX = posXStats + 2;
    cursor.posY += ALTO_ESTANDAR_LETRA + 4;
    escribirTexto("TETRO T: ", &cursor, B);
    escribirNumero(infoJuego[TETRO_T], &cursor, B);

    cursor.posX = posXStats + 2;
    cursor.posY += ALTO_ESTANDAR_LETRA + separStats;
    escribirTexto("TETRO L: ", &cursor, B);
    escribirNumero(infoJuego[TETRO_L], &cursor, B);

    cursor.posX = posXStats + 2;
    cursor.posY += ALTO_ESTANDAR_LETRA + separStats;
    escribirTexto("TETRO J: ", &cursor, B);
    escribirNumero(infoJuego[TETRO_J], &cursor, B);

    cursor.posX = posXStats + 2;
    cursor.posY += ALTO_ESTANDAR_LETRA + separStats;
    escribirTexto("TETRO I: ", &cursor, B);
    escribirNumero(infoJuego[TETRO_I], &cursor, B);

    cursor.posX = posXStats + 2;
    cursor.posY += ALTO_ESTANDAR_LETRA + separStats;
    escribirTexto("TETRO S: ", &cursor, B);
    escribirNumero(infoJuego[TETRO_S], &cursor, B);

    cursor.posX = posXStats + 2;
    cursor.posY += ALTO_ESTANDAR_LETRA + separStats;
    escribirTexto("TETRO Z: ", &cursor, B);
    escribirNumero(infoJuego[TETRO_Z], &cursor, B);

    cursor.posX = posXStats + 2;
    cursor.posY += ALTO_ESTANDAR_LETRA + separStats;
    escribirTexto("TETRO O: ", &cursor, B);
    escribirNumero(infoJuego[TETRO_O], &cursor, B);


    if (infoJuego[MODO_DE_JUEGO] == MODO_DELUXE)
    {
        cursor.posX = posXStats + 2;
        cursor.posY += ALTO_ESTANDAR_LETRA + separStats;
        escribirTexto("TETRO X: ", &cursor, B);
        escribirNumero(infoJuego[TETRO_X], &cursor, B);

        cursor.posX = posXStats + 2;
        cursor.posY += ALTO_ESTANDAR_LETRA + separStats;
        escribirTexto("TETRO C: ", &cursor, B);
        escribirNumero(infoJuego[TETRO_C], &cursor, B);

        cursor.posX = posXStats + 2;
        cursor.posY += ALTO_ESTANDAR_LETRA + separStats;
        escribirTexto("TETRO P: ", &cursor, B);
        escribirNumero(infoJuego[TETRO_P], &cursor, B);

        cursor.posX = posXStats + 2;
        cursor.posY += ALTO_ESTANDAR_LETRA + separStats;
        escribirTexto("TETRO V: ", &cursor, B);
        escribirNumero(infoJuego[TETRO_V], &cursor, B);
    }
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

void verificarArgumentos(int argc, char *argv[], int *resolAncho, int *resolAlto, int *escala)
{
    if (argc > 3)
        printf("Demasiados argumentos. No soportado. El juego se iniciara en resolucion CGA con escala %d.\n", ESCALA_VENTANA_DEFAULT);
    else
    {
        switch (argc)
        {
        case 3:
            int entero = atoi(argv[2]);
            if (entero >= 1 && entero <= 5)
                *escala = entero;
            else
                *escala = ESCALA_VENTANA_DEFAULT;
            printf("Iniciando el juego en escala %d.\n", *escala);
        case 2:
            if (strcmp(argv[1], "vga") == 0 || strcmp(argv[1], "VGA") == 0)
            {
                printf("Iniciando el juego en resolucion VGA (640x480).\n");
                *resolAlto = ALTO_VENTANA_VGA;
                *resolAncho = ANCHO_VENTANA_VGA;
            }
            else if (strcmp(argv[1], "cga") == 0 || strcmp(argv[1], "CGA") == 0)
                printf("Iniciando el juego en resolucion CGA (320x200).\n");
            else
                printf("Las resoluciones validas son 'vga' o 'cga'. El juego se iniciara en resolucion CGA.\n");
        case 1:
            printf("Iniciando juego.\n");
            break;
        }
    }
}
