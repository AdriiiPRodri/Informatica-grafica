// Adrián Jesús Peña Rodríguez          3º C2

#ifdef _WIN32
#include <windows.h>
#endif

#include "vertice.h"
#include <iostream>

vertice::vertice() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

vertice::vertice(GLfloat x, GLfloat y, GLfloat z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

vertice& vertice::operator=(const vertice &vertice) {
    if (&vertice != this) {
        x = vertice.x;
        y = vertice.y;
        z = vertice.z;
    }

    return *this;
}

vertice& vertice::operator+=(const vertice &vertice) {
    x += vertice.x;
    y += vertice.y;
    z += vertice.z;

    return *this;
}

bool vertice::operator==(const vertice &vertice) {
    if (&vertice != this)
        if(x != vertice.x || y != vertice.y || z != vertice.z)
            return false;

    return true;
}

void vertice::imprimir(){
    std::cout << this->x << " " << this->y << " " << this->z << std::endl;
}
