#ifndef TAULER_H
#define TAULER_H
#include "Figura.h"

const int MAX_FILA = 8;
const int MAX_COL = 8;

class Tauler
{
public:
    Tauler() {}
    bool esMovimientoValido(Figura figura, int dirX, int dirY);
    void colocarFigura(Figura figura);
    void eliminarFilasCompletas();
    
private:
    ColorFigura tauler[MAX_FILA][MAX_COL];
    
};
#endif