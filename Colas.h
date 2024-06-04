#pragma once
#include "Figura.h"
#include "InfoJoc.h"

class NodoTipoFigura
{
public:
	NodoTipoFigura() :m_next(nullptr), m_valor() {}
	NodoTipoFigura(Figura valor);
	Figura& getValor() { return m_valor; }
	NodoTipoFigura* getNext() { return m_next; }
	void setValor(Figura valor) { m_valor = valor; }
	void setNext(NodoTipoFigura* next) { m_next = next; }

private:
	Figura m_valor;
	NodoTipoFigura* m_next;
};

class ColaTipoFigura
{
public:
	ColaTipoFigura();
	~ColaTipoFigura();
	void add(Figura tipoFigura);
	bool vacia() const { return (m_primero == nullptr); }
	void extraer();
	Figura& getPrimero() const { return m_primero->getValor(); }
	Figura& getUltimo() const { return m_ultimo->getValor(); }

private:
	int m_nMovimientos;
	NodoTipoFigura* m_primero;
	NodoTipoFigura* m_ultimo;

};


class NodoTipoMovimiento
{
public:
	NodoTipoMovimiento() :m_next(nullptr), m_valor(MOVIMIENTO_BAJAR) {}
	NodoTipoMovimiento(TiposMovimiento valor);
	TiposMovimiento& getValor() { return m_valor; }
	NodoTipoMovimiento* getNext() { return m_next; }
	void setValor(TiposMovimiento valor) { m_valor = valor; }
	void setNext(NodoTipoMovimiento* next) { m_next = next; }

private:
	TiposMovimiento m_valor;
	NodoTipoMovimiento* m_next;
};

class ColaTipoMovimiento
{
public:
	ColaTipoMovimiento();
	~ColaTipoMovimiento();
	void add(TiposMovimiento tipoMovimiento);
	bool vacia() const { return m_primero == nullptr; }
	void extraer();
	TiposMovimiento& getPrimero() const { return m_primero->getValor(); }
	TiposMovimiento& getUltimo() const { return m_ultimo->getValor(); }

private:
	int m_nMovimientos;
	NodoTipoMovimiento* m_primero;
	NodoTipoMovimiento* m_ultimo;
};

