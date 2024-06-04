#pragma once
#include "InfoJoc.h"
#include "Figura.h"

typedef enum {
	BUIDA = 0,
	OCUPADA,
	OCUPADA_PER_FIGURA,
} Casilla;

const int MAX_FILAS = N_FILES_TAULER;
const int MAX_COLUMNAS = N_COL_TAULER;

class Tauler
{
public:
	Tauler() { crearMatrixTablero(); }
	bool ComprobarColision(const Figura& f);
	void PonerFigura(const Figura& f);
	int eliminarCompletas();
	Tauler& operator=(const Tauler& tauler);
	ColorFigura getCasillaTablero(int x, int y) const { return m_tauler[x][y]; }
	void setCasilla(int x, int y, ColorFigura colorFigura) { m_tauler[x][y] = colorFigura; }

private:
	ColorFigura m_tauler[MAX_FILAS][MAX_COLUMNAS];
	void crearMatrixTablero();
};
