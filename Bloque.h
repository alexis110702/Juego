#pragma once
#include "Comun.h"

class CBloque {
	int posX;
	int posY;
	ETipoBloque tipo;
	short durabilidad;

  public:
	CBloque(ETipoBloque tipo, int dureza);
	~CBloque();

	ETipoBloque getTipo();
	void setDurabilidad(short durabilidad);
	short getDurabilidad();
};
