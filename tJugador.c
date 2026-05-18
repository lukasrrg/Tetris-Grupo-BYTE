#include "tJugador.h"

bool jugadorExiste(const char *nombre)
{
    FILE *f = fopen(JUGADORES,"rb");
    if (!f) return false;

    tJugador temp;
        while (fread(&temp, sizeof(tJugador), 1, f) == 1)
    {
        if (strcmp(temp.nombre, nombre) == 0)
        {
            fclose(f);
            return true;
        }
    }
    fclose(f);
    return false;
}

void jugadorGuardar(const tJugador *jugador)
{
    // Leer todos los jugadores existentes
    FILE *f = fopen(JUGADORES, "rb");
    tJugador buf[100];
    int cant = 0;
    bool encontrado = false;

    if (f)
    {
        while (fread(&buf[cant], sizeof(tJugador), 1, f) == 1)
            cant++;
        fclose(f);
    }

    // Si ya existe, sobreescribe su entrada
    int i;
    for (i = 0; i < cant; i++)
    {
        if (strcmp(buf[i].nombre, jugador->nombre) == 0)
        {
            buf[i] = *jugador;
            encontrado = true;
            break;
        }
    }

    // Si no existe, se agrega al final
    if (!encontrado)
        buf[cant++] = *jugador;

    // Reescribir el archivo completo
    f = fopen(JUGADORES, "wb");
    if (f)
    {
        fwrite(buf, sizeof(tJugador), cant, f);
        fclose(f);
    }
}

