// Adrián Jesús Peña Rodríguez          3º C2

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include "cubo.h"

Cubo::Cubo(GLfloat tamanio){

    vertice a(0.0f,0.0f,tamanio), b(tamanio,0.0f,tamanio), c(0.0f,tamanio,tamanio), d(tamanio,tamanio,tamanio);
    vertice e(0.0f,0.0f,0.0f), f(tamanio,0.0f,0.0f), g(0.0f,tamanio,0.0f), h(tamanio,tamanio,0.0f);

    vertices.push_back(a);
    vertices.push_back(b);
    vertices.push_back(c);
    vertices.push_back(d);
    vertices.push_back(e);
    vertices.push_back(f);
    vertices.push_back(g);
    vertices.push_back(h);

    topologia.resize(12);

    topologia[0]._0 = 0; topologia[0]._1 = 1; topologia[0]._2 = 2;
    topologia[1]._0 = 1; topologia[1]._1 = 3; topologia[1]._2 = 2;
    topologia[2]._0 = 2; topologia[2]._1 = 3; topologia[2]._2 = 7;
    topologia[3]._0 = 2; topologia[3]._1 = 7; topologia[3]._2 = 6;
    topologia[4]._0 = 1; topologia[4]._1 = 7; topologia[4]._2 = 3;
    topologia[5]._0 = 1; topologia[5]._1 = 5; topologia[5]._2 = 7;
    topologia[6]._0 = 6; topologia[6]._1 = 7; topologia[6]._2 = 4;
    topologia[7]._0 = 7; topologia[7]._1 = 5; topologia[7]._2 = 4;
    topologia[8]._0 = 0; topologia[8]._1 = 4; topologia[8]._2 = 1;
    topologia[9]._0 = 1; topologia[9]._1 = 4; topologia[9]._2 = 5;
    topologia[10]._0 = 2; topologia[10]._1 = 6; topologia[10]._2 = 4;
    topologia[11]._0 = 0; topologia[11]._1 = 2; topologia[11]._2 = 4;

    calculoNVertices();

}
