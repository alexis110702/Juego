#include "Controladora.h"

CControladora::CControladora() {
	mapa = new CMapa();
	jugador = nullptr;
	enemigo = nullptr;
}

CControladora::~CControladora() {
	delete mapa;
	delete jugador;
	delete enemigo;
}

void CControladora::Inicializar() {
	CambiarNivel(1);
};

void CControladora::CambiarNivel(int nivel) {
	mapa->cargarNivel(nivel);
	crearTanques();
}

// Crea el jugador y UN enemigo en sus posiciones iniciales
void CControladora::crearTanques() {
	delete jugador;
	delete enemigo;

	// Jugador: ultima fila, a la izquierda de la base (columna 4)
	jugador = new CJugador(1, 4 * ANCHO_IMAGEN, (MAX_FILAS - 1) * ALTO_IMAGEN, 3);
	// Enemigo tipo 1: esquina superior izquierda
	enemigo = new CEnemigo(1, static_cast<short>(ETipoTanque::tipo1), 0, 0, 1);
}

void CControladora::DibujarMapa(Graphics^ g, Bitmap^ bmpPiso, Bitmap^ bmpBloques, Bitmap^ bmpTrofeo) {
	mapa->DibujarMapa(g, bmpPiso, bmpBloques, bmpTrofeo);
};

void CControladora::DibujarJugador(Graphics^ g, Bitmap^ bmpTanques) {
	if (jugador != nullptr) jugador->dibujar(g, bmpTanques);
}

void CControladora::DibujarEnemigo(Graphics^ g, Bitmap^ bmpTanques) {
	if (enemigo != nullptr) enemigo->dibujar(g, bmpTanques);
}
