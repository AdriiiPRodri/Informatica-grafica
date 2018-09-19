// Adrián Jesús Peña Rodríguez          3º C2

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include "camara.h"
#include <iostream>

camara::camara(M_camara tipo){

    if(tipo == ORTOGONAL) {
        left = -10; right = 10; bottom = -10; top = 10; nearVal = -10; farVal = 10;
        gluOrtho2D(-6,6,-6,6);
        //glOrtho(-6,6,-6,6,-6,6);   // Xmin, Xmax, Ymin, Ymax, Zmin, Zmax
        glViewport(-10, -10, 30, 30 );     // Dos primeros esquina inferior izquierda, ancho, alto
    }

    modelo = tipo;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if(modelo == PERSPECTIVA) {
        posicion_defecto_x = 0;
        posicion_defecto_y = 60;
    }
    else if (modelo == BASICA) {
        posicion_defecto_x = posicion_defecto_y = 0;
    }
    else {
        posicion_defecto_x = 90;
        posicion_defecto_y = 0;
    }

    posicion_actual_x_m = posicion_actual_y_m = 0.0;

    distancia = 200.0;

    posicion_actual_x = posicion_defecto_x;
    posicion_actual_y = posicion_defecto_y;

}

double camara::getPosicionActualX() {
    return posicion_actual_x;
}

double camara::getPosicionActualY() {
    return posicion_actual_y;
}

void camara::setObservador() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(-posicion_actual_x_m, 0, 0);
    glTranslatef(0, -posicion_actual_y_m, 0);
    glTranslatef(0, 0, -distancia);

    if(modelo == PERSPECTIVA) {
        glRotatef(posicion_actual_x, 1, 0, 0);
        glRotatef(posicion_actual_y, 0, 1, 0);
    }
    else if (modelo == BASICA) {
        glRotatef(posicion_actual_x, 1, 0, 0);
        glRotatef(posicion_actual_y, 0, 1, 0);
    }
    else {
        glRotatef(posicion_actual_x, 1, 0, 0);
        glRotatef(posicion_actual_y, 0, 1, 0);
    }
}

void camara::setObservadorDefecto() {
    posicion_actual_x = posicion_defecto_x;
    posicion_actual_y = posicion_defecto_y;
    posicion_actual_x_m = 0.0;
    posicion_actual_y_m = 0.0;
}

void camara::setObservador(float distancia, float x, float y) {
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    glTranslatef(0, 0, -distancia);
    glRotatef(x, 1, 0, 0);
    glRotatef(y, 0, 1, 0);



    std::cout << -posicion_actual_x_m << " " << -posicion_actual_y_m << " " << std::endl;
}

void camara::moverIzquierda() {
    --posicion_actual_x_m;
}

void camara::moverDerecha() {
    ++posicion_actual_x_m;
}

void camara::moverArriba() {
    ++posicion_actual_y_m;
}

void camara::moverAbajo() {
    --posicion_actual_y_m;
}

void camara::rotarIzquierda() {
    posicion_actual_y--;
}

void camara::rotarDerecha() {
    posicion_actual_y++;
}

void camara::rotarArriba() {
    posicion_actual_x--;
}

void camara::rotarAbajo() {
    posicion_actual_x++;
}

void camara::zoomOrt(bool in) {

    if(in)
        distancia /= 1.2;
    else
        distancia *= 1.2;

    /*glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(in)
        glFrustum(++left, --right, ++bottom, --top, ++nearVal, --farVal);   //glFrustum(left, right, bottom, top, nearVal, farVal);
    else
        glFrustum(--left, ++right, --bottom, ++top, --nearVal, ++farVal);*/
}

bool camara::ortogonal() {
    if(modelo == ORTOGONAL)
        return true;
    else
        return false;
}
