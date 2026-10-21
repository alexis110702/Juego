# Guia: proyecto "Juego" del docente (Battle City)

Guia para resolver en el proyecto **Juego** (un solo proyecto, clases `C...` con `Comun.h`) las 4 tareas del docente. Trabaja en este orden; compila (Ctrl+Shift+B) despues de cada paso.

## Las tareas

- **a)** Crear los niveles 2, 3, 4 y 5 (segun `imagenes/nivel-2..5.png`).
- **b)** Crear el Jugador y el Enemigo en la clase `CControladora`.
- **c)** Cargar y dibujar el Jugador y UN Enemigo con `tanques.png`.
- **d)** Separar lo de (c) en sus clases (cada clase se dibuja a si misma).

## Resumen: que archivo toca cada tarea

| Paso | Tarea | Archivos |
|---|---|---|
| 1 | a | `Comun.h` (constante `MAX_NIVELES`) |
| 2 | a | `Mapa.h`, `Mapa.cpp` (cargarMatriz, cargarNivel, nivel2..5) |
| 3 | c, d | `Tanque.h`, `Tanque.cpp` (sprite base) |
| 4 | c, d | `Jugador.h`, `Jugador.cpp` (dibujar) |
| 5 | c, d | `Enemigo.h`, `Enemigo.cpp` (dibujar) |
| 6 | b | `Controladora.h`, `Controladora.cpp` (crear tanques, CambiarNivel, dibujar) |
| 7 | c | `Juego.h` (cargar tanques.png, transparencias, dibujar, teclas 1-5) |

## Paso 1: Comun.h (tarea a)

Agrega `#define MAX_NIVELES 5` debajo de `MAX_COLUMNAS`.

**`Comun.h`**

```cpp
#pragma once
#define MAX_FILAS 11
#define MAX_COLUMNAS 13
#define MAX_NIVELES 5

#define ANCHO_IMAGEN 64
#define ALTO_IMAGEN 64

enum ETipoBloque {
	piso = 1,
	destruible,
	noDestruible,
	agua,
	arbol,
	trofeo
};

enum EDireccion {
	ninguno,
	arriba,
	abajo,
	izquierda,
	derecha
};

class CComun {

};
```

## Paso 2: Mapa (tarea a)

Idea: en vez de repetir los `if` de cada nivel, una sola funcion `cargarMatriz` convierte una matriz de numeros en bloques. Cada `nivelN()` solo define su matriz. Codigos: 1 piso, 2 destruible, 3 no destruible, 4 agua, 5 arbol, 9 trofeo (la base, siempre abajo al centro).

Las imagenes de nivel son de 13x13 y `MAX_FILAS` es 11: se quitaron las 2 filas mas vacias y se agrego la base. Revisa el resultado comparando con las imagenes.

**`Mapa.h`**

```cpp
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
```

**`Mapa.cpp`**

```cpp
#include "Mapa.h"

CMapa::CMapa() {
    for (int i = 0; i < MAX_FILAS; i++) {
        for (int j = 0; j < MAX_COLUMNAS; j++) {
            mapa[i][j] = nullptr;
        }
    }
    this->nivel = 1;
};

CMapa::~CMapa() {
    for (int i = 0; i < MAX_FILAS; i++) {
        for (int j = 0; j < MAX_COLUMNAS; j++) {
            delete mapa[i][j];
        }
    }
}

void CMapa::setNivel(int nivel) {
    this->nivel = nivel;
}

int CMapa::getNivel() {
    return this->nivel;
}

CBloque* CMapa::getBloque(int i, int j) {
    return mapa[i][j];
}

CBloque* (*CMapa::getMapa())[MAX_COLUMNAS] {
    return this->mapa;
}

// Convierte una matriz de numeros en bloques:
// 1 piso, 2 destruible, 3 no destruible, 4 agua, 5 arbol, 9 trofeo
void CMapa::cargarMatriz(int matriz[MAX_FILAS][MAX_COLUMNAS]) {
    for (int i = 0; i < MAX_FILAS; i++) {
        for (int j = 0; j < MAX_COLUMNAS; j++) {
            // si ya habia un bloque (por un nivel anterior) se libera
            delete mapa[i][j];
            switch (matriz[i][j]) {
            case 2:
                mapa[i][j] = new CBloque(ETipoBloque::destruible, 2);
                break;
            case 3:
                mapa[i][j] = new CBloque(ETipoBloque::noDestruible, -1);
                break;
            case 4:
                mapa[i][j] = new CBloque(ETipoBloque::agua, -1);
                break;
            case 5:
                mapa[i][j] = new CBloque(ETipoBloque::arbol, -1);
                break;
            case 9:
                mapa[i][j] = new CBloque(ETipoBloque::trofeo, 1);
                break;
            default:
                mapa[i][j] = new CBloque(ETipoBloque::piso, 0);
                break;
            }
        }
    }
}

void CMapa::cargarNivel(int nivel) {
    switch (nivel) {
    case 2: nivel2(); break;
    case 3: nivel3(); break;
    case 4: nivel4(); break;
    case 5: nivel5(); break;
    default: nivel1(); break;
    }
}

void CMapa::nivel1() {
    int tmpNivel1[MAX_FILAS][MAX_COLUMNAS] = {
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 2, 1, 2, 1, 2, 1, 1, 1, 2, 1, 2, 1,
      1, 2, 1, 2, 1, 3, 1, 2, 1, 2, 1, 2, 1,
      1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1,
      1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1,
      1, 1, 2, 2, 2, 1, 2, 1, 1, 1, 1, 2, 1,
      1, 1, 3, 1, 1, 1, 2, 1, 1, 2, 1, 3, 1,
      1, 1, 2, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1,
      1, 1, 1, 1, 1, 2, 2, 2, 1, 3, 1, 1, 1,
      1, 1, 1, 1, 1, 2, 9, 2, 1, 1, 1, 1, 1
    };

    std::cout << "Inicializando nivel 1\n";
    this->nivel = 1;
    cargarMatriz(tmpNivel1);
}

void CMapa::nivel2() {
    // Basado en imagenes/nivel-2.png
    int tmpNivel2[MAX_FILAS][MAX_COLUMNAS] = {
      1, 1, 2, 1, 2, 3, 1, 1, 3, 3, 3, 1, 1,
      3, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1,
      2, 1, 2, 2, 2, 1, 2, 2, 1, 4, 4, 1, 4,
      1, 1, 2, 1, 4, 4, 1, 4, 4, 4, 1, 2, 2,
      2, 2, 1, 1, 4, 2, 1, 2, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 3, 3, 1,
      4, 4, 4, 1, 4, 1, 3, 1, 2, 1, 3, 1, 1,
      1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 3, 2, 2,
      1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1,
      2, 2, 1, 1, 1, 2, 2, 2, 1, 1, 2, 1, 1,
      1, 1, 1, 1, 1, 2, 9, 2, 1, 1, 1, 1, 1
    };

    std::cout << "Inicializando nivel 2\n";
    this->nivel = 2;
    cargarMatriz(tmpNivel2);
}

void CMapa::nivel3() {
    // Basado en imagenes/nivel-3.png
    int tmpNivel3[MAX_FILAS][MAX_COLUMNAS] = {
      1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1,
      5, 5, 1, 1, 1, 2, 2, 2, 1, 1, 1, 5, 5,
      5, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 5,
      1, 1, 1, 2, 2, 5, 2, 5, 2, 2, 1, 1, 1,
      1, 1, 1, 2, 5, 5, 2, 5, 5, 2, 1, 1, 1,
      5, 1, 1, 2, 2, 2, 2, 2, 2, 2, 1, 1, 5,
      5, 5, 1, 1, 2, 5, 2, 5, 2, 1, 1, 5, 5,
      4, 4, 4, 1, 2, 2, 2, 2, 2, 1, 4, 4, 4,
      3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3,
      1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1,
      3, 3, 3, 3, 1, 2, 9, 2, 1, 3, 3, 3, 3
    };

    std::cout << "Inicializando nivel 3\n";
    this->nivel = 3;
    cargarMatriz(tmpNivel3);
}

void CMapa::nivel4() {
    // Basado en imagenes/nivel-4.png
    int tmpNivel4[MAX_FILAS][MAX_COLUMNAS] = {
      1, 5, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 5,
      5, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 3,
      3, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1,
      4, 1, 1, 1, 3, 1, 3, 1, 2, 1, 1, 1, 1,
      1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 4, 4,
      1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1,
      1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1,
      1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1,
      1, 2, 2, 1, 1, 2, 2, 1, 1, 2, 2, 1, 5,
      5, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 5, 5,
      3, 5, 1, 1, 1, 2, 9, 2, 1, 1, 5, 5, 3
    };

    std::cout << "Inicializando nivel 4\n";
    this->nivel = 4;
    cargarMatriz(tmpNivel4);
}

void CMapa::nivel5() {
    // Basado en imagenes/nivel-5.png
    int tmpNivel5[MAX_FILAS][MAX_COLUMNAS] = {
      1, 2, 2, 1, 1, 1, 2, 2, 2, 2, 1, 1, 2,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1,
      1, 4, 4, 2, 2, 4, 4, 4, 4, 3, 3, 4, 4,
      1, 4, 4, 2, 2, 4, 4, 4, 4, 3, 3, 4, 4,
      1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1,
      1, 2, 1, 2, 2, 1, 1, 1, 2, 2, 2, 2, 2,
      1, 2, 1, 2, 2, 2, 1, 1, 2, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 2, 2, 2,
      1, 2, 2, 2, 3, 1, 1, 2, 2, 1, 2, 2, 3,
      1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 2, 1, 1,
      1, 1, 2, 1, 1, 2, 9, 2, 1, 1, 2, 1, 1
    };

    std::cout << "Inicializando nivel 5\n";
    this->nivel = 5;
    cargarMatriz(tmpNivel5);
}

void CMapa::DibujarMapa(Graphics^ g, Bitmap^ bmpPiso, Bitmap^ bmpBloques, Bitmap^ bmpTrofeo) {
    int X = 0, Y = 0;
    for (int i = 0; i < MAX_FILAS; i++) {
        X = 0;
        for (int j = 0; j < MAX_COLUMNAS; j++) {
            if (getBloque(i, j)->getTipo() == ETipoBloque::piso) {
                Rectangle rectPiso = Rectangle(0 * ANCHO_IMAGEN, 0 * ALTO_IMAGEN, ANCHO_IMAGEN, ALTO_IMAGEN);
                Rectangle zoom = Rectangle(X, Y, ANCHO_IMAGEN * 1.0, ALTO_IMAGEN * 1.0);
                g->DrawImage(bmpPiso, zoom, rectPiso, GraphicsUnit::Pixel);
            }
            if (getBloque(i, j)->getTipo() == ETipoBloque::destruible) {
                Rectangle rectDestruible = Rectangle(1 * ANCHO_IMAGEN, 0 * ALTO_IMAGEN, ANCHO_IMAGEN, ALTO_IMAGEN);
                Rectangle zoom = Rectangle(X, Y, ANCHO_IMAGEN * 1.0, ALTO_IMAGEN * 1.0);
                g->DrawImage(bmpBloques, zoom, rectDestruible, GraphicsUnit::Pixel);
            }
            if (getBloque(i, j)->getTipo() == ETipoBloque::noDestruible) {
                Rectangle rectNoDestruible = Rectangle(0 * ANCHO_IMAGEN, 1 * ALTO_IMAGEN, ANCHO_IMAGEN, ALTO_IMAGEN);
                Rectangle zoom = Rectangle(X, Y, ANCHO_IMAGEN * 1.0, ALTO_IMAGEN * 1.0);
                g->DrawImage(bmpBloques, zoom, rectNoDestruible, GraphicsUnit::Pixel);
            }
            if (getBloque(i, j)->getTipo() == ETipoBloque::agua) {
                Rectangle rectAgua = Rectangle(2 * ANCHO_IMAGEN, 0 * ALTO_IMAGEN, ANCHO_IMAGEN, ALTO_IMAGEN);
                Rectangle zoom = Rectangle(X, Y, ANCHO_IMAGEN * 1.0, ALTO_IMAGEN * 1.0);
                g->DrawImage(bmpBloques, zoom, rectAgua, GraphicsUnit::Pixel);
            }
            if (getBloque(i, j)->getTipo() == ETipoBloque::arbol) {
                // el arbol tiene fondo transparente: primero se dibuja el piso
                Rectangle rectPiso = Rectangle(0 * ANCHO_IMAGEN, 0 * ALTO_IMAGEN, ANCHO_IMAGEN, ALTO_IMAGEN);
                Rectangle rectArbol = Rectangle(1 * ANCHO_IMAGEN, 1 * ALTO_IMAGEN, ANCHO_IMAGEN, ALTO_IMAGEN);
                Rectangle zoom = Rectangle(X, Y, ANCHO_IMAGEN * 1.0, ALTO_IMAGEN * 1.0);
                g->DrawImage(bmpPiso, zoom, rectPiso, GraphicsUnit::Pixel);
                g->DrawImage(bmpBloques, zoom, rectArbol, GraphicsUnit::Pixel);
            }
            if (getBloque(i, j)->getTipo() == ETipoBloque::trofeo) {
                Rectangle rectTrofeo = Rectangle(0 * ANCHO_IMAGEN, 0 * ALTO_IMAGEN, ANCHO_IMAGEN, ALTO_IMAGEN);
                Rectangle zoom = Rectangle(X, Y, ANCHO_IMAGEN * 1.0, ALTO_IMAGEN * 1.0);
                g->DrawImage(bmpTrofeo, zoom, rectTrofeo, GraphicsUnit::Pixel);
            }

            X += ANCHO_IMAGEN;
        }
        Y += ALTO_IMAGEN;
    }
}
```

## Paso 3: Tanque (tareas c y d)

`CTanque` conoce su posicion y direccion, asi que aqui van los dos ayudantes: `ordenSprite()` (arriba, derecha, abajo, izquierda es el orden de filas en `tanques.png`) y `dibujarSprite()` que recorta una ventana de 64x64. En el constructor la direccion inicial es `arriba`. Agrega ademas `using namespace System::Drawing;` en `Tanque.h`.

**`Tanque.h`**

```cpp
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
```

**`Tanque.cpp`**

```cpp
#include "Tanque.h"

CTanque::CTanque(short id, int posX, int posY, int vidas) {
	this->id = id;
	this->vidas = vidas;
	this->direccion = EDireccion::arriba;
	this->velocidad = 10;
	this->posX = posX;
	this->posY = posY;
}

CTanque::~CTanque() {}

void CTanque::setId(short id) {
	this->id = id;
}
void CTanque::setVidas(short vidas) {
	this->vidas = vidas;
}
void CTanque::setDireccion(EDireccion direccion) {
	this->direccion = direccion;
}
void CTanque::setVelocidad(short velocidad) {
	this->velocidad = velocidad;
}
void CTanque::setX(int posX) {
	this->posX = posX;
}
void CTanque::setY(int posY) {
	this->posY = posY;
}

short CTanque::getId() {
	return this->id;
}
short CTanque::getVidas() {
	return this->vidas;
}
EDireccion CTanque::getDireccion() {
	return this->direccion;
}
short CTanque::getVelocidad() {
	return this->velocidad;
}
int CTanque::getX() {
	return this->posX;
}
int CTanque::getY() {
	return this->posY;
}

int CTanque::ordenSprite() {
	switch (this->direccion) {
	case EDireccion::arriba:
		return 0;
	case EDireccion::derecha:
		return 1;
	case EDireccion::abajo:
		return 2;
	case EDireccion::izquierda:
		return 3;
	default:
		return 0;
	}
}

void CTanque::dibujarSprite(Graphics^ g, Bitmap^ bmpTanques, int origenX, int origenY) {
	Rectangle origen = Rectangle(origenX, origenY, ANCHO_IMAGEN, ALTO_IMAGEN);
	Rectangle destino = Rectangle(this->posX, this->posY, ANCHO_IMAGEN, ALTO_IMAGEN);
	g->DrawImage(bmpTanques, destino, origen, GraphicsUnit::Pixel);
}
```

## Paso 4: Jugador (tareas c y d)

El tanque amarillo esta en la primera columna de `tanques.png`; una fila por direccion (y = 0, 64, 128, 192).

**`Jugador.h`**

```cpp
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
```

**`Jugador.cpp`**

```cpp
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
```

## Paso 5: Enemigo (tareas c y d)

Los enemigos empiezan en y = 508 y cada tipo esta 255 px mas abajo. Dentro de cada grupo, las 4 direcciones estan en y + 0, 64, 124, 191. Ahora el constructor guarda el tipo y la direccion inicial es `abajo`.

**`Enemigo.h`**

```cpp
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
```

**`Enemigo.cpp`**

```cpp
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
```

## Paso 6: Controladora (tarea b)

La controladora crea al Jugador (columna 4, ultima fila, a la izquierda de la base) y a UN Enemigo tipo1 en la esquina superior izquierda. Los recrea en cada `CambiarNivel`. Solo reenvia el dibujo: cada clase se dibuja a si misma.

**`Controladora.h`**

```cpp
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
```

**`Controladora.cpp`**

```cpp
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
```

## Paso 7: Juego.h (tarea c)

Cambios en el formulario (el resto queda igual):

1. En el campo de bitmaps agrega `Bitmap^ bmpTanques = gcnew Bitmap("imagenes\\tanques.png");`
2. En `Load`, hazlos transparentes:
```cpp
bmpTanques->MakeTransparent(bmpTanques->GetPixel(0, 0));      // fondo amarillo
bmpBloques->MakeTransparent(Color::FromArgb(255, 81, 241));   // fondo rosado del arbol
```
3. En el `Tick`, despues de `DibujarMapa(...)`:
```cpp
controladora->DibujarJugador(buffer->Graphics, bmpTanques);
controladora->DibujarEnemigo(buffer->Graphics, bmpTanques);
```
4. En `KeyDown`, antes del cierre del `switch`, para probar los niveles:
```cpp
case Keys::D1: case Keys::NumPad1: controladora->CambiarNivel(1); break;
case Keys::D2: case Keys::NumPad2: controladora->CambiarNivel(2); break;
case Keys::D3: case Keys::NumPad3: controladora->CambiarNivel(3); break;
case Keys::D4: case Keys::NumPad4: controladora->CambiarNivel(4); break;
case Keys::D5: case Keys::NumPad5: controladora->CambiarNivel(5); break;
```

## Comprobacion final

Ejecuta: se ve el nivel 1, el tanque amarillo abajo a la izquierda de la base y un enemigo arriba a la izquierda. Con 1 a 5 cambias de nivel. Si el arbol sale con fondo rosado o el tanque con fondo amarillo, falta el `MakeTransparent`.

_No lo compile en Visual Studio; la logica se probo con g++ y un Graphics simulado._
