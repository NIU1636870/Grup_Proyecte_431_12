#include "InfoJoc.h"
#include "GraphicManager.h"
#include "Partida.h"

void Partida::inicializa(int modo, const string& ficheroInicial, const string& ficheroFiguras, const string& ficheroMovimientos) {
    m_nivel = 1;
    m_vel = VELOCIDAD;
    m_gameOver = false;
    m_modoTestActivado = modo;
    m_puntuacion = 0;

    m_joc.inicialitza(ficheroInicial);

    if (modo == 1) {
        ifstream fs;

        fs.open(ficheroFiguras);
        if (fs.is_open()) {
            Figura figura;
            while (fs >> figura) {
                m_colaFiguras.add(figura);
            }
            fs.close();
        }

        fs.open(ficheroMovimientos);
        if (fs.is_open()) {
            int movs;
            while (fs >> movs) {
                m_colaMovimientos.add(static_cast<TiposMovimiento>(movs));
            }
            fs.close();
        }
    }
}

int Partida::bucle(Screen& pantalla) {
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;

    do {
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());

        pantalla.processEvents();
        actualiza(deltaTime);
        pantalla.update();
    } while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE) && !getGameOver());

    return m_puntuacion;
}

void Partida::actualiza(double deltaTime) {
    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER, false);

    if (m_modoTestActivado) {
        actualizarTest(deltaTime);
    }
    else {
        actualizarNormal(deltaTime);
    }

    if (m_puntuacion / (PUNTUACION_POR_NIVEL * m_nivel) == 1) {
        m_nivel++;
        m_vel -= 0.1;
    }
    m_joc.dibujarGraphic();

    string titulo = "Nivel " + to_string(m_nivel) + "    Puntuacion: " + to_string(m_puntuacion);
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER, POS_Y_TAULER - 60, 1.0, titulo);
}

void Partida::actualizarNormal(double deltaTime) {
    if (Keyboard_GetKeyTrg(KEYBOARD_RIGHT)) {
        m_joc.mouFigura(1);
    }
    if (Keyboard_GetKeyTrg(KEYBOARD_LEFT)) {
        m_joc.mouFigura(-1);
    }
    if (Keyboard_GetKeyTrg(KEYBOARD_UP)) {
        m_joc.giraFigura(GIRO_SENT_ANTI_HORARIO);
    }
    if (Keyboard_GetKeyTrg(KEYBOARD_DOWN)) {
        m_joc.giraFigura(GIRO_SENT_HORARIO);
    }
    if (Keyboard_GetKeyTrg(KEYBOARD_SPACE)) {
        int completas = m_joc.dejarCaerFigura();
        m_puntuacion += PUNTUACION_POR_FILA * completas;
        if (completas > 1) {
            m_puntuacion += PUNTOS_EXTRA * completas;
        }
        m_puntuacion += PUNTUACION_POR_CAIDA;
        if (!m_joc.nuevaFigura()) {
            m_gameOver = true;
        }
    }

    m_tiempo += deltaTime;
    if (m_tiempo > m_vel) {
        int completas = m_joc.baixaFigura();
        if (completas != -1) {
            if (!m_joc.nuevaFigura()) {
                m_gameOver = true;
            }
            m_puntuacion += PUNTUACION_POR_FILA * completas;
            if (completas > 1) {
                m_puntuacion += PUNTOS_EXTRA * completas;
            }
            m_puntuacion += PUNTUACION_POR_CAIDA;
        }
        m_tiempo = 0.0;
    }
}

void Partida::actualizarTest(double deltaTime) {
    m_tiempo += deltaTime;
    if (m_tiempo > m_vel) {
        if (m_colaMovimientos.vacia()) {
            m_gameOver = true;
        }
        else {
            TiposMovimiento movimiento = m_colaMovimientos.getPrimero();
            m_colaMovimientos.extraer();

            switch (movimiento) {
            case MOVIMIENTO_IZQ:
                m_joc.mouFigura(-1);
                break;
            case MOVIMIENTO_DERECHA:
                m_joc.mouFigura(1);
                break;
            case MOVIMIENTO_GIRO_HORARIO:
                m_joc.giraFigura(GIRO_SENT_HORARIO);
                break;
            case MOVIMIENTO_GIRO_ANTI_HORARIO:
                m_joc.giraFigura(GIRO_SENT_ANTI_HORARIO);
                break;
            case MOVIMIENTO_BAJAR:
                movimientoBaixa();
                break;
            case MOVIMIENTO_BAJAR_FINAL:
                movimientoBaixaFinal();
                break;
            }
            m_tiempo = 0.0;
        }
    }
}

void Partida::movimientoBaixaFinal() {
    int completas = m_joc.dejarCaerFigura();
    m_puntuacion += PUNTUACION_POR_FILA * completas;
    if (completas > 1) {
        m_puntuacion += completas * PUNTOS_EXTRA;
    }
    m_puntuacion += PUNTUACION_POR_CAIDA;

    if (m_colaFiguras.vacia()) {
        m_gameOver = true;
    }
    else {
        Figura f = m_colaFiguras.getPrimero();
        m_colaFiguras.extraer();
        if (!m_joc.nuevaFigura(f)) {
            m_gameOver = true;
        }
    }
}

void Partida::movimientoBaixa() {
    int completas = m_joc.baixaFigura();
    if (completas == -1) {
        return;
    }
    if (!m_joc.nuevaFigura()) {
        m_gameOver = true;
    }
    m_puntuacion += PUNTUACION_POR_FILA * completas;
    if (completas > 1) {
        m_puntuacion += PUNTOS_EXTRA * completas;
    }
    m_puntuacion += PUNTUACION_POR_CAIDA;
}
