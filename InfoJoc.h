#ifndef INFO_JOC_H
#define INFO_JOC_H

using namespace std;

const int PUNTOS_EXTRA = 25;
const int PUNTUACION_POR_NIVEL = 1000;
const int PUNTUACION_POR_FILA = 100;
const int PUNTUACION_POR_CAIDA = 10;
const float VELOCIDAD = 0.7;

typedef enum
{
    TECLA_ESQUERRA,
    TECLA_DRETA,
    TECLA_AMUNT,    
    TECLA_ABAIX, 
    TECLA_ESPAI, 
    TECLA_ESCAPE,
    NO_TECLA
} TipusTecla;

const int N_TIPUS_FIGURES = 7;

typedef enum
{
    MOVIMIENTO_IZQ = 0,
    MOVIMIENTO_DERECHA,
    MOVIMIENTO_GIRO_HORARIO,
    MOVIMIENTO_GIRO_ANTI_HORARIO,
    MOVIMIENTO_BAJAR,
    MOVIMIENTO_BAJAR_FINAL,
} TiposMovimiento;

typedef enum
{
    COLOR_NEGRE = 0,
    COLOR_GROC,
    COLOR_BLAUCEL,
    COLOR_MAGENTA,
    COLOR_TARONJA,
    COLOR_BLAUFOSC,
    COLOR_VERMELL,
    COLOR_VERD,
    NO_COLOR
} ColorFigura;

typedef enum
{
    NO_FIGURA = 0,
    FIGURA_O,
    FIGURA_I,
    FIGURA_T,
    FIGURA_L,
    FIGURA_J,
    FIGURA_Z,
    FIGURA_S
} TipusFigura;

const int SCREEN_SIZE_X = 600;
const int SCREEN_SIZE_Y = 700;
const int MIDA_QUADRAT = 26;
const int N_FILES_TAULER = 21;
const int N_COL_TAULER = 11;
const int POS_X_TAULER = 120;
const int POS_Y_TAULER = 100;

#endif