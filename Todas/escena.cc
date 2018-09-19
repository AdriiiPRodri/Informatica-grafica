// Adrián Jesús Peña Rodríguez          3º C2

#ifdef _WIN32
#include <windows.h>
#endif
#include <cstdio>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include "escena.h"

Escena::Escena(const std::string& name, const std::string& name2) {
    Front_plane = 50;
    Back_plane = 2000;
    Observer_distance = 4 * Front_plane;
    Observer_angle_x = Observer_angle_y = 0;
    ejes.changeAxisSize(5000);

    tetra = new Tetraedro(4);
    cubo = new Cubo(4);
    octaedro = new Octaedro(4);
    atracc = new modeloJerarquico();
    luz0 = new iluminacion(0);      // Luz 0, GL_LIGHT0
    luz1 = new iluminacion(1);      // Luz 1, GL_LIGHT1
    materialR = new Material();
    materialG = new Material();
    materialB = new Material();
    tab = new tablero(1.0, 4);
    camaras.push_back(new camara(BASICA));
    camaras.push_back(new camara(PERSPECTIVA));
    camaras.push_back(new camara(ORTOGONAL));

    if(!name.empty())
        obj = new modeloPLY(name);

    if(!name2.empty())
        obj_rev = new revolucion(name2);
    else
        obj_rev = new revolucion();

    vector<vertice> puntos;

    puntos.push_back( vertice(3, 5, 0.0) );
    puntos.push_back( vertice(3, 4, 0.0) );
    puntos.push_back( vertice(3, 3, 0.0) );
    puntos.push_back( vertice(2, 2, 0.0) );
    puntos.push_back( vertice(1.5f, 1, 0.0) );
    puntos.push_back( vertice(1, 0, 0.0) );

    obj_rev_examen = new revolucion(puntos);
}

void Escena::animarIndependiente() {
    if(atracc != nullptr && !desactiva) {
        atracc->animarIndependiente();
        glutPostRedisplay();
    }
}

void Escena::inicializar(int UI_window_width, int UI_window_height) {

    glClearColor(1, 1, 1, 1); // se indica cual sera el color para limpiar la ventana	(r,v,a,al)

    glEnable(GL_DEPTH_TEST); // se habilita el z-bufer   --- glEnable(GL_CULL_FACE) -> Probar

    glEnable(GL_NORMALIZE); // Deshabilitado por defecto

    this->change_projection();
    Width = UI_window_width / 10;
    Height = UI_window_height / 10;
    glViewport(0, 0, UI_window_width, UI_window_height);

}


//**************************************************************************
// Funcion que dibuja objetos en la escena
//***************************************************************************

void Escena::draw_objects() {

    glEnable(GL_CULL_FACE);

	if(figura == M_ROTACION){
        switch (modo) {
		    case LINES:
		        obj_rev->dibujar(LINES);
		        break;
		    case PUNTOS:
		        obj_rev->dibujar(PUNTOS);
		        break;
		    case FILL:
		        obj_rev->dibujar(FILL);
		        break;
		    case CHESS:
		        obj_rev->dibujar(CHESS);
		        break;
		    case MEZCLA:
		        obj_rev->dibujar(MEZCLA);
		        break;
		}
	}
    else if(figura == ROTACION_EXAMEN){
        switch (modo) {
		    case LINES:
		        obj_rev_examen->dibujar(LINES);
		        break;
		    case PUNTOS:
		        obj_rev_examen->dibujar(PUNTOS);
		        break;
		    case FILL:
		        obj_rev_examen->dibujar(FILL);
		        break;
		    case CHESS:
		        obj_rev_examen->dibujar(CHESS);
		        break;
		    case MEZCLA:
		        obj_rev_examen->dibujar(MEZCLA);
		        break;
		}
	}
	else
		switch (modo) {
		    case LINES:
		        if (figura == TETRA)
		            tetra->dibujar(LINES);
		        else if(figura == CUBO)
		            cubo->dibujar(LINES);
		        else if(figura == OCTAEDRO)
		            octaedro->dibujar(LINES);
		        else if(figura == MODELO && obj != nullptr)
		            obj->dibujar(LINES);
                else if(figura == JERARQUICO && atracc != nullptr)
		            atracc->dibujar(LINES);
                else if(figura == TABLERO)
                    tab->dibuja();
		        break;
		    default:
		        if (figura == TETRA)
		            tetra->dibujar(PUNTOS);
		        else if(figura == CUBO)
		            cubo->dibujar(PUNTOS);
		        else if(figura == OCTAEDRO)
		            octaedro->dibujar(PUNTOS);
		        else if(figura == MODELO && obj != nullptr)
		            obj->dibujar(PUNTOS);
                else if(figura == JERARQUICO && atracc != nullptr)
		            atracc->dibujar(PUNTOS);
                else if(figura == TABLERO)
                    tab->dibuja();
		        break;
		    case FILL:
		        if (figura == TETRA)
		            tetra->dibujar(FILL);
		        else if(figura == CUBO)
		            cubo->dibujar(FILL);
		        else if(figura == OCTAEDRO)
		            octaedro->dibujar(FILL);
		        else if(figura == MODELO && obj != nullptr)
		            obj->dibujar(FILL);
                else if(figura == JERARQUICO && atracc != nullptr)
		            atracc->dibujar(FILL);
                else if(figura == TABLERO)
                    tab->dibuja();
		        break;
		    case CHESS:
		        if (figura == TETRA)
		            tetra->dibujar(CHESS);
		        else if(figura == CUBO)
		            cubo->dibujar(CHESS);
		        else if(figura == OCTAEDRO)
		            octaedro->dibujar(CHESS);
		        else if(figura == MODELO && obj != nullptr)
		            obj->dibujar(CHESS);
                else if(figura == JERARQUICO && atracc != nullptr)
		            atracc->dibujar(CHESS);
                else if(figura == TABLERO)
                    tab->dibuja();
		        break;
		    case MEZCLA:
		        if (figura == TETRA)
		            tetra->dibujar(MEZCLA);
		        else if(figura == CUBO)
		            cubo->dibujar(MEZCLA);
		        else if(figura == OCTAEDRO)
		            octaedro->dibujar(MEZCLA);
		        else if(figura == MODELO && obj != nullptr)
		            obj->dibujar(MEZCLA);
                else if(figura == JERARQUICO && atracc != nullptr)
		            atracc->dibujar(MEZCLA);
                else if(figura == TABLERO)
                    tab->dibuja();
		        break;
		}

}

void Escena::dibujar() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar la pantalla
    change_observer();
    draw_axis();
    if(luz0->luces)
        luz0->activarPanelLuces();
    else
        luz0->desactivarPanelLuces();

    if(luz1->luces)
        luz1->activarPanelLuces();
    else
        luz1->desactivarPanelLuces();
    draw_objects();
}

int Escena::teclaPulsada(unsigned char Tecla1, int x, int y) {

    std::cout << "Tecla " << Tecla1 << std::endl;

    if (toupper(Tecla1) == 'Q')
        return 1;
    else if (Tecla1 == '1')
        figura = TETRA;
    else if (Tecla1 == '2')
        figura = CUBO;
    else if(Tecla1 == '3')
        figura = OCTAEDRO;
    else if(Tecla1 == '4' && obj != nullptr) {
        figura = MODELO;
    }
	else if(Tecla1 == '5')
		figura = M_ROTACION;
    else if(Tecla1 == '6')
        figura = ROTACION_EXAMEN;
    else if(Tecla1 == '7')
        figura = JERARQUICO;
    else if(Tecla1 == '0') {
        figura = TABLERO;
        tab->colocaTextura();
        tab->rotarTextura();
    }
    else if(Tecla1 == '8') {
        if(figura == TABLERO)
            tab->rotarTextura();
    }
    else if(Tecla1 == '9') {
        if(figura == TABLERO)
            tab->moverTextura(((double) rand() / (RAND_MAX)), ((double) rand() / (RAND_MAX)));
    }
    else if(Tecla1 == '+') {
        obj_rev->cambiarRevoluciones(1);

        if(obj_rev_examen != nullptr)
            obj_rev_examen->cambiarRevoluciones(1);
    }
    else if(Tecla1 == '-') {
		obj_rev->cambiarRevoluciones(0);

        if(obj_rev_examen != nullptr)
            obj_rev_examen->cambiarRevoluciones(0);
    }
    else if(Tecla1 == '*') {
        desactiva = true;

        if(atracc != nullptr)
            atracc->animar();
    }
    else if (toupper(Tecla1) == 'I') {
        if(!luz0->luces)
            luz0->luces = true;
        else
            luz0->luces = false;

        if(!luz1->luces)
            luz1->luces = true;
        else
            luz1->luces = false;
    }
    else if (toupper(Tecla1) == 'Z') {
        if(!flat) {
            glShadeModel(GL_FLAT);
            flat = true;
            cout << "Modo de sombreado flat" << endl;
        }
        else {
            glShadeModel(GL_SMOOTH);
            flat = false;
            cout << "Modo de sombreado smooth" << endl;
        }
    }
    else if (toupper(Tecla1) == 'F')
        modo = FILL;
    else if (toupper(Tecla1) == 'L')
        modo = LINES;
    else if (toupper(Tecla1) == 'P')
        modo = PUNTOS;
    else if (toupper(Tecla1) == 'C')
        modo = CHESS;
    else if (toupper(Tecla1) == 'M')
        modo = MEZCLA;
    else if (toupper(Tecla1) == 'T') {
        obj_rev->cambiaTapas();

        if(obj_rev_examen != nullptr)
            obj_rev_examen->cambiaTapas();
    }
    else if (toupper(Tecla1) == 'A')
        camaras[camaraActiva]->moverIzquierda();
    else if (toupper(Tecla1) == 'D')
        camaras[camaraActiva]->moverDerecha();
    else if (toupper(Tecla1) == 'W')
        camaras[camaraActiva]->moverArriba();
    else if (toupper(Tecla1) == 'S')
        camaras[camaraActiva]->moverAbajo();
    else if (toupper(Tecla1) == 'R')
        camaras[camaraActiva]->setObservadorDefecto();

    return 0;
}

void Escena::teclaEspecial(int Tecla1, int x, int y) {
    switch (Tecla1) {
        case GLUT_KEY_LEFT: camaras[camaraActiva]->rotarIzquierda();
            break;
        case GLUT_KEY_RIGHT: camaras[camaraActiva]->rotarDerecha();
            break;
        case GLUT_KEY_UP: camaras[camaraActiva]->rotarArriba();
            break;
        case GLUT_KEY_DOWN: camaras[camaraActiva]->rotarAbajo();
            break;
        case GLUT_KEY_PAGE_UP: if(camaras[camaraActiva]->ortogonal()) camaras[camaraActiva]->zoomOrt(true);
            break;
        case GLUT_KEY_PAGE_DOWN: if(camaras[camaraActiva]->ortogonal()) camaras[camaraActiva]->zoomOrt(false);
            break;
        case GLUT_KEY_F1:
            if(luz0 != nullptr && luz0->luces) {
                luz0->cambiaColor(1.0, 1.0, 1.0);
                luz0->rotaLuz(0);
            }
            break;
        case GLUT_KEY_F2:
            if(luz1 != nullptr) {
                luz1->cambiaColor(1.0, 0.0, 0.0);
                luz1->rotaLuz(1);
            }
            break;
        case GLUT_KEY_F5:
            if(materialR != nullptr && !materialR->material) {
                materialG->quitarMaterial();
                materialB->quitarMaterial();
                materialR->ponerMaterial(1.0, 0.0, 0.0);
            }
            else if(materialR->material)
                materialR->quitarMaterial();
            break;
        case GLUT_KEY_F6:
            if(materialG != nullptr && !materialG->material) {
                materialR->quitarMaterial();
                materialB->quitarMaterial();
                materialG->ponerMaterial(0.0, 1.0, 0.0);
            }
            else if(materialG->material)
                materialG->quitarMaterial();
            break;
        case GLUT_KEY_F7:
            if(materialB != nullptr && !materialB->material) {
                materialR->quitarMaterial();
                materialG->quitarMaterial();
                materialB->ponerMaterial(0.0, 0.0, 1.0);
            }
            else if(materialB->material)
                materialB->quitarMaterial();
            break;
        case GLUT_KEY_F8:
            camaraActiva = 0;
            camaras[camaraActiva]->setObservador(200, camaras[camaraActiva]->getPosicionActualX(), camaras[camaraActiva]->getPosicionActualY());
            break;
        case GLUT_KEY_F9:
            camaraActiva = 1;
            camaras[camaraActiva]->setObservador(200, camaras[camaraActiva]->getPosicionActualX(), camaras[camaraActiva]->getPosicionActualY());
            break;
        case GLUT_KEY_F10:
            camaraActiva = 2;
            camaras[camaraActiva]->setObservador(200, camaras[camaraActiva]->getPosicionActualX(), camaras[camaraActiva]->getPosicionActualY());
            break;

    }

    std::cout << Observer_distance << std::endl;
}


//**************************************************************************
// Funcion para definir la transformaci�n de proyeccion
//***************************************************************************

void Escena::change_projection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    Width /= 25;
    Height /= 25;
    glFrustum(-Width, Width, -Height, Height, Front_plane, Back_plane);
}

void Escena::redimensionar(int newWidth, int newHeight) {
    change_projection();
    Width = newWidth / 10;
    Height = newHeight / 10;
    glViewport(0, 0, newWidth, newHeight);
}


//**************************************************************************
// Funcion para definir la transformaci�n de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer() {

    // posicion del observador
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    /*glTranslatef(0, 0, -Observer_distance);
    /*glRotatef(Observer_angle_x, 1, 0, 0);
    glRotatef(Observer_angle_y, 0, 1, 0);*/
    camaras[camaraActiva]->setObservador();
}


//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void Escena::draw_axis() {
    glDisable(GL_LIGHTING);
    ejes.draw();
}
