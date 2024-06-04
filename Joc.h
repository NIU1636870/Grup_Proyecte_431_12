#pragma once
#include "Tauler.h"

class Joc
{
public:
	void inicialitza(const string& fichero);
	bool giraFigura(Direccion dir);
	bool mouFigura(int dir);
	int baixaFigura();
	void escriuTauler(const string& fichero);
	bool nuevaFigura();
	bool nuevaFigura(Figura& f);
	void dibujarGraphic();
	int dejarCaerFigura();
private:
	Figura m_figura;
	Tauler m_tauler;
};

