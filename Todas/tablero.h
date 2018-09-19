// Adrián Jesús Peña Rodríguez          3º C2

#ifndef _TABLERO_H
#define _TABLERO_H
#include "objeto3d.h"

// ----------------------------------------------------------------------
// NECESARIO PARA CARGAR LAS IMÁGENES DE DISCO
#include "CImg.h"
using namespace cimg_library;
// ----------------------------------------------------------------------

class tablero : public objeto3d {
private:
    std::vector<unsigned char> data;
    std::vector<vector<float>> coordenadas;
    GLuint textura_id;
    int grados;
    int tam;
public:
    tablero(const GLfloat tamanio = 1.0f, const int &m = 4);
    void colocaTextura();
    void rotarTextura();
    void moverTextura(const float &x, const float &y);
    void dibuja();
    void libera_textura();
};
#endif
