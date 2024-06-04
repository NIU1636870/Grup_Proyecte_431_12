#include "Tauler.h"

void Tauler::crearMatrixTablero() {
    for (int i = 0; i < MAX_FILAS; ++i) {
        for (int j = 0; j < MAX_COLUMNAS; ++j) {
            m_tauler[i][j] = NO_COLOR;
        }
    }
}

int Tauler::eliminarCompletas() {
    int filasCompletas = 0;

    for (int i = 0; i < N_FILES_TAULER; ++i) {
        bool estaCompleta = true;

        for (int j = 0; j < N_COL_TAULER; ++j) {
            if (m_tauler[i][j] == COLOR_NEGRE) {
                estaCompleta = false;
                break;
            }
        }

        if (estaCompleta) {
            for (int k = i; k > 0; --k) {
                for (int l = 0; l < N_COL_TAULER; ++l) {
                    m_tauler[k][l] = m_tauler[k - 1][l];
                }
            }
            for (int l = 0; l < N_COL_TAULER; ++l) {
                m_tauler[0][l] = COLOR_NEGRE;
            }
            --i;
            ++filasCompletas;
        }
    }
    return filasCompletas;
}

void Tauler::PonerFigura(const Figura& f) {
    if (f.getMatrix() == nullptr) return;

    int x = f.getPosicion().x;
    int y = f.getPosicion().y;

    for (int i = 0; i < f.getDimensionMatrix(); ++i) {
        for (int j = 0; j < f.getDimensionMatrix(); ++j) {
            if (f.getMatrix()[i][j] != COLOR_NEGRE && j + x >= 0 && y + i >= 0 && j + x < MAX_COLUMNAS && y + i < MAX_FILAS) {
                m_tauler[y + i][x + j] = f.getMatrix()[i][j];
            }
        }
    }
}

bool Tauler::ComprobarColision(const Figura& f) {
    if (f.getMatrix() == nullptr) return false;

    int x = f.getPosicion().x;
    int y = f.getPosicion().y;

    for (int i = 0; i < f.getDimensionMatrix(); ++i) {
        for (int j = 0; j < f.getDimensionMatrix(); ++j) {
            if (f.getMatrix()[i][j] != COLOR_NEGRE) {
                if (i + y < 0 || j + x < 0 || j + x >= MAX_COLUMNAS || i + y >= MAX_FILAS) {
                    return true;
                }
                if (m_tauler[i + y][j + x] != COLOR_NEGRE) {
                    return true;
                }
            }
        }
    }
    return false;
}

Tauler& Tauler::operator=(const Tauler& tauler2) {
    if (this != &tauler2) {
        for (int i = 0; i < MAX_FILAS; ++i) {
            for (int j = 0; j < MAX_COLUMNAS; ++j) {
                m_tauler[i][j] = tauler2.m_tauler[i][j];
            }
        }
    }
    return *this;
}
