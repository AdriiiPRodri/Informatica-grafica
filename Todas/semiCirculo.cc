// Adrián Jesús Peña Rodríguez          3º C2

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include "semiCirculo.h"
#include <iostream>

semiCirculo::semiCirculo(GLfloat tamanio){

    vertice inicial(tamanio,0.0f,0.0f);

    for(double i = tamanio; i >= 0; i-=0.01){
        vertices.push_back(vertice(cos(convRadianes(i)), sin(convRadianes(i)), 0.0f));
        vertices.push_back(vertice(cos(convRadianes(i)), sin(convRadianes(-i)), 0.0f));
    }

    //std::cout << vertices.size() << std::endl;

    semiC = new revolucion(vertices);

    calculoNVertices();

}

float semiCirculo::convRadianes(float degrees) {
    return (degrees * M_PI / 180);
}
