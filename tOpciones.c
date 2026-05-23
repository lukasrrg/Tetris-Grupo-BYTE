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
    }
}
