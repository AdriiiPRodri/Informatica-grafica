// Adrián Jesús Peña Rodríguez          3º C2

#ifndef _VERTICE_H
#define _VERTICE_H
#include <GL/gl.h>
#include <GL/glut.h>

class vertice {
public:
    float x, y, z;
public:
    vertice();
    vertice(GLfloat x, GLfloat y, GLfloat z);

    vertice& operator=(const vertice &otherPoint);
    vertice& operator+=(const vertice &otherPoint);
    bool operator==(const vertice &otherPoint);
    void imprimir();
};
#endif
