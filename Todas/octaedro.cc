// Adrián Jesús Peña Rodríguez          3º C2

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include "octaedro.h"

Octaedro::Octaedro(GLfloat tamanio){

    vertice a(0.0f,0.0f,0.0f), b(tamanio/2,-tamanio/2,0), c(tamanio/2,0,tamanio/2), d(tamanio,0,0);
    vertice e(tamanio/2, tamanio/2,0), f(tamanio/2,0.0f,-tamanio/2);

    vertices.push_back(a);
    vertices.push_back(b);
    vertices.push_back(c);
    vertices.push_back(d);
    vertices.push_back(e);
    vertices.push_back(f);

    topologia.resize(8);

    topologia[0]._0 = 0; topologia[0]._1 = 1; topologia[0]._2 = 2;
    topologia[1]._0 = 1; topologia[1]._1 = 3; topologia[1]._2 = 2;
    topologia[2]._0 = 0; topologia[2]._1 = 2; topologia[2]._2 = 4;
    topologia[3]._0 = 2; topologia[3]._1 = 3; topologia[3]._2 = 4;
    topologia[4]._0 = 5; topologia[4]._1 = 1; topologia[4]._2 = 0;
    topologia[5]._0 = 5; topologia[5]._1 = 0; topologia[5]._2 = 4;
    topologia[6]._0 = 3; topologia[6]._1 = 1; topologia[6]._2 = 5;
    topologia[7]._0 = 3; topologia[7]._1 = 5; topologia[7]._2 = 4;

    calculoNVertices();

}
