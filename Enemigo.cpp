#include "Enemigo.h"

CEnemigo::CEnemigo(short id, short tipo, int posx, int posy, int vidas) : CTanque(id, posx, posy, vidas) {
	this->tipo = static_cast<ETipoTanque>(tipo);
	this->setDireccion(EDireccion::abajo);
}

void CEnemigo::setTipo(ETipoTanque tipo) {
	this->tipo = tipo;
}
ETipoTanque CEnemigo::getTipo() {
	return this->tipo;
}

void CEnemigo::dibujar(Graphics^ g, Bitmap^ bmpTanques) {
	// En tanques.png los tanques enemigos (primera columna) forman grupos de 4 filas
	// (arriba, derecha, abajo, izquierda). El primer grupo empieza en y = 508 y
	// cada grupo siguiente esta 255 px mas abajo (uno por cada tipo de tanque).
	static const int desplazamientoY[4] = { 0, 64, 124, 191 };
	int grupo = static_cast<int>(this->tipo);
	if (grupo > 3) grupo = 3;   // la hoja trae 4 grupos: tipo5 reutiliza el ultimo
	int origenY = 508 + 255 * grupo + desplazamientoY[this->ordenSprite()];
	this->dibujarSprite(g, bmpTanques, 0, origenY);
}
