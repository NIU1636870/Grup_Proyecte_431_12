#include "Colas.h"

NodoTipoMovimiento::NodoTipoMovimiento(TiposMovimiento valor)
    : m_valor(valor), m_next(nullptr) {}

void ColaTipoMovimiento::extraer()
{
    if (m_primero == nullptr)
    {
        // La cola está vacía, no se hace nada
    }
    else if (m_primero == m_ultimo)
    {
        delete m_primero;
        m_primero = nullptr;
        m_ultimo = nullptr;
    }
    else
    {
        NodoTipoMovimiento* temp = m_primero;
        m_primero = m_primero->getNext();
        delete temp;
        m_nMovimientos--;
    }
}

void ColaTipoMovimiento::add(TiposMovimiento tipoMovimiento)
{
    NodoTipoMovimiento* nuevo = new NodoTipoMovimiento(tipoMovimiento);

    if (m_primero == nullptr)
    {
        m_primero = nuevo;
        m_ultimo = nuevo;
    }
    else
    {
        m_ultimo->setNext(nuevo);
        m_ultimo = nuevo;
        m_nMovimientos++;
    }
}

ColaTipoMovimiento::~ColaTipoMovimiento()
{
    NodoTipoMovimiento* siguiente = nullptr;
    NodoTipoMovimiento* actual = m_primero;

    while (actual != nullptr)
    {
        siguiente = actual->getNext();
        delete actual;
        actual = siguiente;
    }

    m_primero = nullptr;
    m_ultimo = nullptr;
}

ColaTipoMovimiento::ColaTipoMovimiento() : m_primero(nullptr), m_ultimo(nullptr), m_nMovimientos(0) {}

NodoTipoFigura::NodoTipoFigura(Figura valor)
    : m_valor(valor), m_next(nullptr) {}

void ColaTipoFigura::extraer()
{
    if (m_primero == nullptr)
    {
        // La cola está vacía, no se hace nada
    }
    else if (m_primero == m_ultimo)
    {
        delete m_primero;
        m_primero = nullptr;
        m_ultimo = nullptr;
    }
    else
    {
        NodoTipoFigura* temp = m_primero;
        m_primero = m_primero->getNext();
        delete temp;
        m_nMovimientos--;
    }
}

void ColaTipoFigura::add(Figura tipoFigura)
{
    NodoTipoFigura* nuevo = new NodoTipoFigura(tipoFigura);

    if (m_primero == nullptr)
    {
        m_primero = nuevo;
        m_ultimo = nuevo;
    }
    else
    {
        m_ultimo->setNext(nuevo);
        m_ultimo = nuevo;
        m_nMovimientos++;
    }
}

ColaTipoFigura::~ColaTipoFigura()
{
    NodoTipoFigura* siguiente = nullptr;
    NodoTipoFigura* actual = m_primero;

    while (actual != nullptr)
    {
        siguiente = actual->getNext();
        delete actual;
        actual = siguiente;
    }

    m_primero = nullptr;
    m_ultimo = nullptr;
}

ColaTipoFigura::ColaTipoFigura()
    : m_primero(nullptr), m_ultimo(nullptr), m_nMovimientos(0) {}
