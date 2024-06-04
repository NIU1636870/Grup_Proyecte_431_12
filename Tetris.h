#pragma once
#include <string>
#include <list>
#include <iostream>
#include <list>
#include "GraphicManager.h"
#include "Partida.h"

struct Puntos
{
	string jugador;
	int puntos;

};

class Tetris
{
public:
	void mostrarPuntuacion() const;
	void jugarPartida(Screen& pantalla);

private:
	void insertarPuntuacion(const string& jugador, int puntos);
	void guardarPuntuacion(const string& nombreFichero) const;
	void lecturaPuntuacion(const string& nombreFichero);

	Partida m_partida;
	std::list<Puntos> m_puntuaciones;
};
