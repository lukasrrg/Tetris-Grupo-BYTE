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

    gbt_borrar_backbuffer(N);

    gbt_procesar_entrada();
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

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
