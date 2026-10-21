#pragma once
#include <string>
#include "Tanque.h"

class CJugador: public CTanque {
	std::string nombre;
	int puntuacion;
public:
	CJugador(short id, int posX, int posY, int vidas);
	void setNombre(std::string nombre);
	void setPuntuacion(int puntuacion);
	std::string getNombre();
	int getPuntuacion();

	void dibujar(Graphics^ g, Bitmap^ bmpTanques);
	void mover();
};

