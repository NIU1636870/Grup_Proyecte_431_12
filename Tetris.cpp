#include "Tetris.h"
#include "GraphicManager.h"

void Tetris::jugarPartida(Screen& pantalla)
{
    lecturaPuntuacion("puntuacion.txt");
    int opcion = -1;
    do
    {
        cout << "--- MENU PRINCIPAL ---" << endl;
        cout << "1. Juego modo normal" << endl;
        cout << "2. Juego modo test" << endl;
        cout << "3. Mostrar puntuaciones" << endl;
        cout << "4. Exit" << endl;
        cout << "----------------------------" << endl;

        cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            m_partida.inicializa(0, "data/Games/partida.txt", "", "");
            int puntos = m_partida.bucle(pantalla);
            string jugador = "";
            cout << "Escribe tu nombre: ";
            cin >> jugador;
            insertarPuntuacion(jugador, puntos);
            break;
        }
        case 2:
        {
            m_partida.inicializa(1, "data/Games/partida.txt", "data/Games/figures.txt", "data/Games/moviments.txt");
            int puntos = m_partida.bucle(pantalla);
            string jugador = "";
            cout << "Escribe tu nombre: ";
            cin >> jugador;
            insertarPuntuacion(jugador, puntos);
            break;
        }
        case 3:
        {
            mostrarPuntuacion();
            break;
        }
        case 4:
        default:
            break;
        }
    } while (opcion != 4);

    guardarPuntuacion("puntuacion.txt");
}

void Tetris::mostrarPuntuacion() const
{
    list<Puntos>::const_iterator iterador = m_puntuaciones.begin();
    cout << "---PUNTUACIONES---" << endl;
    while (iterador != m_puntuaciones.end())
    {
        cout << "Jugador: " << iterador->jugador << "     Puntuacion: " << iterador->puntos << endl;
        iterador++;
    }


}

void Tetris::insertarPuntuacion(const string& jugador, int puntos)
{
    list<Puntos>::iterator iterador = m_puntuaciones.begin();
    bool b = false;
    while (iterador != m_puntuaciones.end() && !b)
    {
        if (iterador->puntos < puntos)
            b = true;
        else
            iterador++;
    }

    Puntos nuevaPuntuacionJugador;
    nuevaPuntuacionJugador.puntos = puntos;
    nuevaPuntuacionJugador.jugador = jugador;
    m_puntuaciones.insert(iterador, nuevaPuntuacionJugador);

}

void Tetris::guardarPuntuacion(const string& nombreFichero) const
{
    ofstream output;
    output.open(nombreFichero);
    list<Puntos>::const_iterator iterador = m_puntuaciones.begin();
    while (iterador != m_puntuaciones.end())
    {
        output << iterador->jugador << " " << iterador->puntos << endl;
        iterador++;
    }
    output.close();
}

void Tetris::lecturaPuntuacion(const string& nombreFichero)
{
    ifstream input;
    input.open(nombreFichero);
    if (input.is_open())
    {
        string jugador = "";
        int puntos = -1;
        Puntos puntoNuevo;
        input >> puntoNuevo.jugador >> puntoNuevo.puntos;
        while (!input.eof())
        {
            m_puntuaciones.push_back(puntoNuevo);
            input >> puntoNuevo.jugador >> puntoNuevo.puntos;

        }
        input.close();
    }
}
