#include "Jugador.h"

CJugador::CJugador(short id, int posX, int posY, int vidas) : CTanque(id, posX, posY, vidas) {
	this->nombre = "";
	this->puntuacion = 0;
	this->setDireccion(EDireccion::arriba);
}

void CJugador::setNombre(std::string nombre) {
	this->nombre = nombre;
}
void CJugador::setPuntuacion(int puntuacion) {
	this->puntuacion = puntuacion;
}
std::string CJugador::getNombre() {
	return this->nombre;
}
int CJugador::getPuntuacion() {
	return this->puntuacion;
}

void CJugador::dibujar(Graphics^ g, Bitmap^ bmpTanques) {
	// Tanque amarillo (primera columna de tanques.png): una fila por direccion
	// en el orden arriba, derecha, abajo, izquierda
	static const int origenY[4] = { 0, 64, 128, 192 };
	this->dibujarSprite(g, bmpTanques, 0, origenY[this->ordenSprite()]);
}
void CJugador::mover() {

}
