#include "Figura.h"

int calcularLados(const TipusFigura& tipoFigura) {
    switch (tipoFigura) {
    case FIGURA_J:
    case FIGURA_L:
    case FIGURA_T:
    case FIGURA_S:
    case FIGURA_Z:
        return 3;
    case FIGURA_I:
        return 4;
    case FIGURA_O:
        return 2;
    default:
        return 0;
    }
}

void Figura::aliberarMatrix() {
    if (m_matrix) {
        for (int i = 0; i < m_dimension; ++i) {
            delete[] m_matrix[i];
        }
        delete[] m_matrix;
        m_matrix = nullptr;
    }
}

Figura::Figura(const Figura& f2) : m_matrix(nullptr), m_dimension(f2.m_dimension),
m_posicion(f2.m_posicion), m_tipoFigura(f2.m_tipoFigura) {
    if (f2.getMatrix()) {
        crearMatrixFiguras();
        for (int i = 0; i < m_dimension; ++i) {
            for (int j = 0; j < m_dimension; ++j) {
                m_matrix[i][j] = f2.getMatrix()[i][j];
            }
        }
    }
}

void Figura::crearMatrixFiguras() {
    if (!m_matrix && m_tipoFigura != NO_FIGURA) {
        m_matrix = nuevaMatrixDinamica(m_dimension, m_dimension);
        switch (m_tipoFigura) {
        case FIGURA_I:
            for (int i = 0; i < 4; ++i) m_matrix[1][i] = COLOR_BLAUCEL;
            break;
        case FIGURA_J:
            m_matrix[0][0] = COLOR_BLAUFOSC;
            for (int i = 0; i < 3; ++i) m_matrix[1][i] = COLOR_BLAUFOSC;
            break;
        case FIGURA_L:
            m_matrix[0][2] = COLOR_TARONJA;
            for (int i = 0; i < 3; ++i) m_matrix[1][i] = COLOR_TARONJA;
            break;
        case FIGURA_O:
            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 2; ++j) {
                    m_matrix[i][j] = COLOR_GROC;
                }
            }
            break;
        case FIGURA_S:
            m_matrix[0][1] = COLOR_VERD;
            m_matrix[0][2] = COLOR_VERD;
            m_matrix[1][0] = COLOR_VERD;
            m_matrix[1][1] = COLOR_VERD;
            break;
        case FIGURA_T:
            m_matrix[0][1] = COLOR_MAGENTA;
            m_matrix[1][0] = COLOR_MAGENTA;
            m_matrix[1][1] = COLOR_MAGENTA;
            m_matrix[1][2] = COLOR_MAGENTA;
            break;
        case FIGURA_Z:
            m_matrix[0][0] = COLOR_VERMELL;
            m_matrix[0][1] = COLOR_VERMELL;
            m_matrix[1][1] = COLOR_VERMELL;
            m_matrix[1][2] = COLOR_VERMELL;
            break;
        default:
            break;
        }
    }
}

void Figura::invertirMatrix(const bool& bColumnas, const bool& bFilas) {
    ColorFigura aux[N_FILES_MAX][N_COLUMNES_MAX];
    for (int i = 0; i < m_dimension; ++i) {
        for (int j = 0; j < m_dimension; ++j) {
            if (bColumnas) {
                aux[i][j] = m_matrix[i][m_dimension - 1 - j];
            }
            else if (bFilas) {
                aux[i][j] = m_matrix[m_dimension - 1 - i][j];
            }
        }
    }
    for (int i = 0; i < m_dimension; ++i) {
        for (int j = 0; j < m_dimension; ++j) {
            m_matrix[i][j] = aux[i][j];
        }
    }
}

void Figura::transposarMatrix() {
    ColorFigura aux[N_FILES_MAX][N_COLUMNES_MAX];
    for (int i = 0; i < m_dimension; ++i) {
        for (int j = 0; j < m_dimension; ++j) {
            aux[i][j] = m_matrix[j][i];
        }
    }
    for (int i = 0; i < m_dimension; ++i) {
        for (int j = 0; j < m_dimension; ++j) {
            m_matrix[i][j] = aux[i][j];
        }
    }
}

void Figura::girar(const Direccion& direccion) {
    transposarMatrix();
    if (direccion == GIRO_SENT_HORARIO) {
        invertirMatrix(true, false);
    }
    else if (direccion == GIRO_SENT_ANTI_HORARIO) {
        invertirMatrix(false, true);
    }
}

ColorFigura** Figura::nuevaMatrixDinamica(int nFilas, int nColumnas) {
    ColorFigura** matriu = new ColorFigura * [nFilas];
    for (int i = 0; i < nFilas; ++i) {
        matriu[i] = new ColorFigura[nColumnas];
    }
    for (int i = 0; i < nFilas; ++i) {
        for (int j = 0; j < nColumnas; ++j) {
            matriu[i][j] = COLOR_NEGRE;
        }
    }
    return matriu;
}

Figura Figura::operator=(const Figura& f2) {
    if (this != &f2) {
        aliberarMatrix();
        m_dimension = f2.m_dimension;
        m_posicion = f2.m_posicion;
        m_tipoFigura = f2.m_tipoFigura;
        if (f2.getMatrix()) {
            crearMatrixFiguras();
            for (int i = 0; i < m_dimension; ++i) {
                for (int j = 0; j < m_dimension; ++j) {
                    m_matrix[i][j] = f2.getMatrix()[i][j];
                }
            }
        }
    }
    return *this;
}

istream& operator>>(istream& entrada, Figura& figura) {
    int tipus, y, x, nGirs;
    entrada >> tipus >> y >> x >> nGirs;
    if (tipus != -1) {
        PosicionFigura pos = { x - 1, y - 1 };
        figura = Figura(static_cast<TipusFigura>(tipus), pos);
        for (int i = 0; i < nGirs; ++i) {
            figura.girar(GIRO_SENT_HORARIO);
        }
    }
    return entrada;
}

Figura::~Figura() {
    aliberarMatrix();
}
