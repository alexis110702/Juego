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