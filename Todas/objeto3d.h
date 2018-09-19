// Adrián Jesús Peña Rodríguez          3º C2

#ifndef _OBJETO3D_H
#define _OBJETO3D_H
#include <vector>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <string>
#include "vertice.h"
#include "caras.h"
#include "file_ply_stl.h"

enum M_visual {
    PUNTOS, LINES, FILL, CHESS, MEZCLA
};

enum Color {
    ROJO, VERDE, AZUL, GRIS
};

enum Figura {
    TETRA, CUBO, OCTAEDRO, MODELO, M_ROTACION, ROTACION_EXAMEN, JERARQUICO, TABLERO
};

class objeto3d {
protected:
    std::vector<vertice> vertices; // Tupla con los vertices correspondientes a nuestros triangulos, sin repetir vertices
    std::vector<caras> topologia; // Tupla que contiene a nuestros triangulos
    std::vector<float> color; // Vector de colores
    std::vector<vertice> normalesVertices;   // Vector de normales de los vertices que forman el objeto3d
public:
    objeto3d();
    objeto3d(std::vector<vertice> &vert, std::vector<caras> &topo);
    objeto3d(const objeto3d &otrafigura);
    std::vector<caras> CarasImpares();
    std::vector<caras> CarasPares();
    void cambiarColor(Color col = GRIS);
    void normalizar(vertice &normaliza);
    void calculoNVertices();
    void dibujar(M_visual modo);
};
#endif
