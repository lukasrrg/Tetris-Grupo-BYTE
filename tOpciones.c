#include "tOpciones.h"

void opcionesGuardar(const tOpciones *op)
{
    FILE *f = fopen(OPCIONES_BIN, "wb");
    if (f)
    {
        fwrite(op, sizeof(tOpciones), 1, f);
        fclose(f);
    }
}

void opcionesCargar(tOpciones *op)
{
    FILE *f = fopen(OPCIONES_BIN, "rb");
    if (f)
    {
        fread(op, sizeof(tOpciones), 1, f);
        fclose(f);
    }
    else
    {
        // Si no existe el archivo, carga los valores default
        op->resolAncho  = ANCHO_VENTANA_CGA;
        op->resolAlto   = ALTO_VENTANA_CGA;
        op->velCaida    = VEL_CAIDA_DEFAULT;
        op->anchoGrilla = ANCHO_GRILLA_DEFAULT;
        op->paleta      = 0;
        return;
    }

    // Normalizar valores por si el archivo viene de una version anterior
    if (op->resolAncho != ANCHO_VENTANA_CGA && op->resolAncho != ANCHO_VENTANA_VGA)
        op->resolAncho = ANCHO_VENTANA_CGA;
    if (op->resolAlto != ALTO_VENTANA_CGA && op->resolAlto != ALTO_VENTANA_VGA)
        op->resolAlto = ALTO_VENTANA_CGA;
    if (op->velCaida <= 0)
        op->velCaida = VEL_CAIDA_DEFAULT;
    if (op->anchoGrilla < ANCHO_GRILLA_MIN || op->anchoGrilla > ANCHO_GRILLA_MAX)
        op->anchoGrilla = ANCHO_GRILLA_DEFAULT;
}
