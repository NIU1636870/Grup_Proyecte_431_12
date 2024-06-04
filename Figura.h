#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "InfoJoc.h"

const int N_COLUMNES_MAX = 4;
const int N_FILES_MAX = 4;
typedef enum { GIRO_SENT_HORARIO = 0, GIRO_SENT_ANTI_HORARIO } Direccion;

int calcularLados(const TipusFigura& tipoFigura);
typedef struct
{
	int x;
	int y;
} PosicionFigura;

class Figura
{
public:
	Figura() : m_dimension(0), m_matrix(nullptr), m_posicion({ 0,0 }), m_tipoFigura(NO_FIGURA) {}
	Figura(TipusFigura tipus, const PosicionFigura& posicio) : m_matrix(nullptr), m_posicion(posicio), m_dimension(calcularLados(tipus)), m_tipoFigura(tipus) { crearMatrixFiguras(); }
	Figura(const Figura& f2);
	~Figura();
	int getDimensionMatrix() const { return m_dimension; }
	PosicionFigura getPosicion() const { return m_posicion; }
	ColorFigura** getMatrix() const { return m_matrix; }
	void setPosicio(const PosicionFigura& posicio) { m_posicion = posicio; }
	Figura operator=(const Figura& f2);
	void girar(const Direccion& direccion);
	void aliberarMatrix();

private:
	PosicionFigura m_posicion;
	ColorFigura** m_matrix;
	int m_dimension;
	TipusFigura m_tipoFigura;

	ColorFigura** nuevaMatrixDinamica(int nFilas, int nColumnas);
	void crearMatrixFiguras();
	void invertirMatrix(const bool& bColumnas, const bool& bFilas);
	void transposarMatrix();
};

istream& operator>>(istream& in, Figura& f);