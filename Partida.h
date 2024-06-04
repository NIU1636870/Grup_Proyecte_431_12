#pragma once
#include <stdio.h>
#include <string>
#include "Colas.h"
#include "GraphicManager.h"
#include "InfoJoc.h"
#include "Joc.h"

using namespace std;

class Partida 
{
public:
    Partida() : m_gameOver(false), m_tiempo(0) {}

    void inicializa(int modo, const string& ficheroInicial, const string& ficheroFiguras,
        const string& ficheroMovimientos);

    bool getGameOver() const { return m_gameOver; }
    int bucle(Screen& screen);
    
    void actualiza(double deltaTime);
    void actualizarNormal(double deltaTime);
    void actualizarTest(double deltaTime);
    
    void movimientoBaixa();
    void movimientoBaixaFinal();
    
private:
    Joc m_joc;
    ColaTipoMovimiento m_colaMovimientos;
    ColaTipoFigura m_colaFiguras;
    bool m_gameOver;
    bool m_modoTestActivado;
    int m_puntuacion;
    float m_vel;
    int m_nivel;
    double m_tiempo;
};

