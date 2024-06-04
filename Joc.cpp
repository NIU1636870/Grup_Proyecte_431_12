#include <iostream>
#include <fstream>
#include "InfoJoc.h"
#include "GraphicManager.h"
#include "Joc.h"

void Joc::inicialitza(const string& fichero) {
    *this = Joc();
    ifstream fs(fichero);

    if (fs.is_open()) {
        int colorFigura;
        fs >> m_figura;
        for (int i = 0; i < N_FILES_TAULER; ++i) {
            for (int j = 0; j < N_COL_TAULER; ++j) {
                fs >> colorFigura;
                m_tauler.setCasilla(i, j, static_cast<ColorFigura>(colorFigura));
            }
        }
        fs.close();
    }
}

bool Joc::giraFigura(Direccion dir) {
    Figura auxFigura(m_figura);
    auxFigura.girar(dir);

    if (m_tauler.ComprobarColision(auxFigura)) {
        return false;
    }
    else {
        m_figura.girar(dir);
        return true;
    }
}

bool Joc::mouFigura(int dir) {
    Figura auxFigura(m_figura);
    PosicionFigura posicion = auxFigura.getPosicion();
    posicion.x += dir;
    auxFigura.setPosicio(posicion);

    if (m_tauler.ComprobarColision(auxFigura)) {
        return false;
    }
    else {
        m_figura.setPosicio(posicion);
        return true;
    }
}

int Joc::baixaFigura() {
    Figura auxFigura(m_figura);
    PosicionFigura posicion = auxFigura.getPosicion();
    posicion.y++;
    auxFigura.setPosicio(posicion);

    if (!m_tauler.ComprobarColision(auxFigura)) {
        m_figura.setPosicio(posicion);
        return -1;
    }
    else {
        m_tauler.PonerFigura(m_figura);
        int completas = m_tauler.eliminarCompletas();
        m_figura = Figura();
        return completas;
    }
}

int Joc::dejarCaerFigura() {
    int filasCompletas;
    do {
        filasCompletas = baixaFigura();
    } while (filasCompletas == -1);
    return filasCompletas;
}

void Joc::escriuTauler(const string& fichero) {
    Tauler aux = m_tauler;
    aux.PonerFigura(m_figura);
    ofstream fs(fichero);

    if (fs.is_open()) {
        for (int i = 0; i < MAX_FILAS; ++i) {
            for (int j = 0; j < MAX_COLUMNAS; ++j) {
                fs << aux.getCasillaTablero(i, j);
            }
            fs << endl;
        }
        fs.close();
    }
}

void Joc::dibujarGraphic() {
    for (int i = 0; i < MAX_FILAS; ++i) {
        for (int j = 0; j < MAX_COLUMNAS; ++j) {
            ColorFigura colorFigura = m_tauler.getCasillaTablero(i, j);
            if (colorFigura != NO_COLOR && colorFigura != COLOR_NEGRE) {
                GraphicManager::getInstance()->drawSprite(
                    static_cast<IMAGE_NAME>(colorFigura + 1),
                    POS_X_TAULER + ((j + 1) * MIDA_QUADRAT),
                    POS_Y_TAULER + (i * MIDA_QUADRAT), false
                );
            }
        }
    }

    for (int i = 0; i < m_figura.getDimensionMatrix(); ++i) {
        for (int j = 0; j < m_figura.getDimensionMatrix(); ++j) {
            ColorFigura colorFigura = m_figura.getMatrix()[i][j];
            if (colorFigura != COLOR_NEGRE) {
                PosicionFigura pos = m_figura.getPosicion();
                GraphicManager::getInstance()->drawSprite(
                    static_cast<IMAGE_NAME>(colorFigura + 1),
                    POS_X_TAULER + ((j + pos.x + 1) * MIDA_QUADRAT),
                    POS_Y_TAULER + ((i + pos.y) * MIDA_QUADRAT), false
                );
            }
        }
    }
}

bool Joc::nuevaFigura() {
    PosicionFigura posicion{ 5, 0 };
    TipusFigura tipo = static_cast<TipusFigura>(rand() % (N_TIPUS_FIGURES - 1) + 1);
    Figura figuraNueva(tipo, posicion);

    if (m_tauler.ComprobarColision(figuraNueva)) {
        return false;
    }
    else {
        m_figura = figuraNueva;
        return true;
    }
}

bool Joc::nuevaFigura(Figura& f) {
    PosicionFigura posicion{ 5, 0 };
    f.setPosicio(posicion);

    if (m_tauler.ComprobarColision(f)) {
        return false;
    }
    else {
        m_figura = f;
        return true;
    }
}
