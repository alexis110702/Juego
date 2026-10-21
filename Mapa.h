#pragma once
#include <iostream>
#include "Bloque.h"

using namespace System::Drawing;

class CMapa {
  CBloque* mapa[MAX_FILAS][MAX_COLUMNAS];
  int nivel;
  void cargarMatriz(int matriz[MAX_FILAS][MAX_COLUMNAS]);

  public:
	CMapa();
	~CMapa();
	void setNivel(int nivel);
	int getNivel();
	CBloque* getBloque(int i, int j);
	CBloque* (*CMapa::getMapa())[MAX_COLUMNAS];
	void cargarNivel(int nivel);
	void nivel1();
	void nivel2();
	void nivel3();
	void nivel4();
	void nivel5();
	void DibujarMapa(Graphics^ g, Bitmap^ bmpPiso, Bitmap^ bmpBloques, Bitmap^ bmpTrofeo);
};

