// Adrián Jesús Peña Rodríguez          3º C2

#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "tetraedro.h"
#include "cubo.h"
#include "octaedro.h"
#include "modeloPLY.h"
#include "objeto3d.h"
#include "revolucion.h"
#include "modeloJerarquico.h"
#include "iluminacion.h"
#include "material.h"
#include "tablero.h"
#include "camara.h"

class Escena {
private:

    Tetraedro *tetra;
    Cubo *cubo;
    Octaedro *octaedro;
    modeloPLY *obj;
    revolucion *obj_rev;
    revolucion *obj_rev_examen;
    modeloJerarquico *atracc;
    iluminacion *luz0;
    iluminacion *luz1;
    Material *materialR;
    Material *materialG;
    Material *materialB;
    tablero *tab;
    int camaraActiva = 0;
    vector<camara *> camaras;

    Figura figura;
    M_visual modo;
    bool desactiva = false;
    bool flat = false;

    // tama�o de los ejes
#define AXIS_SIZE 5000
    Ejes ejes;

    // variables que definen la posicion de la camara en coordenadas polares
    GLfloat Observer_distance;
    GLfloat Observer_angle_x;
    GLfloat Observer_angle_y;

    // variables que controlan la ventana y la transformacion de perspectiva
    GLfloat Width, Height, Front_plane, Back_plane;

private:
    void clear_window();
    void draw_axis();
    void draw_objects();

    //Transformaci�n de c�mara
    void change_projection();
    void change_observer();


public:
    Escena(const std::string& name, const std::string& name2);
    void animarIndependiente();
    void inicializar(int UI_window_width, int UI_window_height);
    void redimensionar(int newWidth, int newHeight);

    // Dibujar
    void dibujar();

    // Interacci�n con la escena
    int teclaPulsada(unsigned char Tecla1, int x, int y);
    void teclaEspecial(int Tecla1, int x, int y);
};
#endif
