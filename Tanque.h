#pragma once
#include "Comun.h"

using namespace System::Drawing;

class CTanque {
	short id;
	short vidas;
	EDireccion direccion;
	short velocidad;
	int posX;
	int posY;
	short powerups[99];
protected:
	// Orden en que aparecen las direcciones en tanques.png: arriba, derecha, abajo, izquierda
	int ordenSprite();
	// Dibuja en (posX, posY) el recuadro de 64x64 que empieza en (origenX, origenY) de tanques.png
	void dibujarSprite(Graphics^ g, Bitmap^ bmpTanques, int origenX, int origenY);
public:
	CTanque(short id, int posX, int posY, int vidas);
	~CTanque();
	void setId(short id);
	void setVidas(short vidas);
	void setDireccion(EDireccion direccion);
	void setVelocidad(short velocidad);
	void setX(int posX);
	void setY(int posY);

	short getId();
	short getVidas();
	EDireccion getDireccion();
	short getVelocidad();
	int getX();
	int getY();
};

