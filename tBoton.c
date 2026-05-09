#include "tBoton.h"

void botonCrear(tBoton *p, int estado, int ancho, int alto, int pX, int pY, int colBorde, int colCentro, char text[], int colTexto)
{
    p->estado = estado;
    p->tamAncho = ancho;
    p->tamAlto = alto;
    p->posX = pX;
    p->posY = pY;
    p->colorBorde = colBorde;
    p->colorCentro = colCentro;
    p->colorTexto = colTexto;
    strcpy(p->texto, text);
}

void botonDibujar(tBoton *boton)
{
    int i, j;

    tCursorTexto cursor = {boton->posX + 2, boton->posY + 2};

    for (i = 0; i < boton->tamAncho; i++)
    {
        for (j = 0; j < boton->tamAlto; j++)
        {
            if (i == 0 || j == 0 || i == boton->tamAncho - 1 || j == boton->tamAlto - 1)
            {
                if (boton->estado == APUNTADO)
                    gbt_dibujar_pixel(boton->posX + i,boton->posY + j, COLOR_BOTON_APUNTADO);
                else
                    gbt_dibujar_pixel(boton->posX + i,boton->posY + j, boton->colorBorde);
            }
            else
                gbt_dibujar_pixel(boton->posX + i,boton->posY + j, boton->colorCentro);
        }
    }


    //Quizas conviene calcular cursor->posX para que siempre el texto este centrado

    escribirTexto(boton->texto, &cursor, boton->colorTexto);
}

void botonActualizarTodosInactivo(tBoton *p, int ce)
{
    int i;

    for (i = 0; i < ce; i++)
        (p + i)->estado = INACTIVO;
}
