#pragma once
#include "Mapa.h"
#include "Jugador.h"
#include "Enemigo.h"

class CControladora {
private:
	CMapa* mapa;
	CJugador* jugador;
	CEnemigo* enemigo;
	void crearTanques();
public:
	CControladora();
	~CControladora();

	void Inicializar();
	void CambiarNivel(int nivel);
	void DibujarMapa(Graphics^ g, Bitmap^ bmpPiso, Bitmap^ bmpBloques, Bitmap^ bmpTrofeo);
	void DibujarJugador(Graphics^ g, Bitmap^ bmpTanques);
	void DibujarEnemigo(Graphics^ g, Bitmap^ bmpTanques);
};

