// Adrián Jesús Peña Rodríguez          3º C2

#ifndef _CARAS_H
#define _CARAS_H
#include <GL/gl.h>
#include <GL/glut.h>

class caras {
public:
    int _0, _1, _2;
public:
    caras();
    caras(int x, int y, int z);

    caras& operator=(const caras &otherPoint);
    bool operator==(const caras &otherPoint);
    void imprimir();
};
#endif
