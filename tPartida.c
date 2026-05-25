#include "tPartida.h"
#include <string.h>

void partidaGuardar(const tPartida *p)
{
    FILE *f = fopen(PARTIDAS_BIN, "rb");
    tPartida buf[MAX_PARTIDAS];
    int cant = 0;
    bool encontrado = false;

    if (f)
    {
        while (fread(&buf[cant], sizeof(tPartida), 1, f) == 1)
            cant++;
        fclose(f);
    }

    int i;
    for (i = 0; i < cant; i++)
    {
        if (strcmp(buf[i].nombre, p->nombre) == 0 && buf[i].modoDeluxe == p->modoDeluxe)
        {
            buf[i] = *p;
            encontrado = true;
            break;
        }
    }

    if (!encontrado && cant < MAX_PARTIDAS)
        buf[cant++] = *p;

    f = fopen(PARTIDAS_BIN, "wb");
    if (f)
    {
        fwrite(buf, sizeof(tPartida), cant, f);
        fclose(f);
    }
}

bool partidaExiste(const char *nombre, bool modoDeluxe)
{
    FILE *f = fopen(PARTIDAS_BIN, "rb");
    if (!f) return false;

    tPartida temp;
    while (fread(&temp, sizeof(tPartida), 1, f) == 1)
    {
        if (strcmp(temp.nombre, nombre) == 0 && temp.modoDeluxe == modoDeluxe)
        {
            fclose(f);
            return true;
        }
    }
    fclose(f);
    return false;
}

bool partidaCargar(const char *nombre, bool modoDeluxe, tPartida *p)
{
    FILE *f = fopen(PARTIDAS_BIN, "rb");
    if (!f) return false;

    tPartida temp;
    while (fread(&temp, sizeof(tPartida), 1, f) == 1)
    {
        if (strcmp(temp.nombre, nombre) == 0 && temp.modoDeluxe == modoDeluxe)
        {
            *p = temp;
            fclose(f);
            return true;
        }
    }
    fclose(f);
    return false;
}

void partidaSerializarGrilla(tPartida *p, const tGrilla *grilla)
{
    int fila, col;
    tMino *mino;

    for (fila = 0; fila < grilla->alto; fila++)
    {
        for (col = 0; col < grilla->anchoGrilla; col++)
        {
            mino = *(grilla->matMinos + fila) + col;
            int idx = fila * ANCHO_GRILLA_MAX + col;
            p->matMinos[idx].estado = mino->estado;
            p->matMinos[idx].color  = mino->color;
        }
    }
}

void partidaRestaurarGrilla(const tPartida *p, tGrilla *grilla, int resolAncho, int resolAlto)
{
    // grillaCrear ya inicializó posiciones correctas; solo restauramos estado y color
    int fila, col;
    tMino *mino;

    for (fila = 0; fila < ALTO_GRILLA_TOTAL; fila++)
    {
        for (col = 0; col < grilla->anchoGrilla; col++)
        {
            mino = *(grilla->matMinos + fila) + col;
            int idx = fila * ANCHO_GRILLA_MAX + col;
            mino->estado = p->matMinos[idx].estado;
            mino->color  = p->matMinos[idx].color;
        }
    }
}
