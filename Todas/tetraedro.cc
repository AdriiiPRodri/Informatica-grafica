// Adrián Jesús Peña Rodríguez          3º C2

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include "tetraedro.h"

Tetraedro::Tetraedro(GLfloat tamanio) {

    vertice a(0.0f,0.0f,0.0f), b(tamanio,0.0f,0.0f), c(tamanio/2,tamanio,tamanio/2), d(tamanio/2,0.0f,-tamanio);

    vertices.push_back(a);
    vertices.push_back(b);
    vertices.push_back(c);
    vertices.push_back(d);

    topologia.resize(4);

    topologia[0]._0 = 0; topologia[0]._1 = 1; topologia[0]._2 = 2;
    topologia[1]._0 = 1; topologia[1]._1 = 3; topologia[1]._2 = 2;
    topologia[2]._0 = 3; topologia[2]._1 = 0; topologia[2]._2 = 2;
    topologia[3]._0 = 3; topologia[3]._1 = 1; topologia[3]._2 = 0;

    calculoNVertices();

}
