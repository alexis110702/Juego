#pragma once
#include "Tanque.h"

enum ETipoTanque {
	tipo1,
	tipo2,
	tipo3,
	tipo4,
	tipo5
};

class CEnemigo: public CTanque {
	ETipoTanque tipo;
public:
	CEnemigo(short id, short tipo, int posx, int posy, int vidas);
	void setTipo(ETipoTanque tipo);
	ETipoTanque getTipo();

	void dibujar(Graphics^ g, Bitmap^ bmpTanques);
};

