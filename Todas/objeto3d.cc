// Adrián Jesús Peña Rodríguez          3º C2

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include "objeto3d.h"
#include <iostream>

objeto3d::objeto3d(){

}

objeto3d::objeto3d(std::vector<vertice> &vert, std::vector<caras> &topo) {

    vertices = vert;
    topologia = topo;

}

objeto3d::objeto3d(const objeto3d &otrafigura) {

    vertices = otrafigura.vertices;
    topologia = otrafigura.topologia;

}

std::vector<caras> objeto3d::CarasImpares() {

    std::vector<caras> devolver;

    for (int i = 1; i < topologia.size(); i = i + 2)
        devolver.push_back(topologia[i]);

    return devolver;
}

std::vector<caras> objeto3d::CarasPares() {

    std::vector<caras> devolver;

    for (int i = 0; i < topologia.size(); i = i + 2)
        devolver.push_back(topologia[i]);

    return devolver;
}

void objeto3d::cambiarColor(Color col) {

    color.clear();
    int num_ver = vertices.size();

    switch (col) {
        case GRIS:
            for(int i = 0; i < num_ver; i++) {
                color.push_back(0.5f); color.push_back(0.5f); color.push_back(0.5f);
            }
            break;
        case ROJO:
            for(int i = 0; i < num_ver; i++) {
                color.push_back(1.0f); color.push_back(0.0f); color.push_back(0.0f);
            }
            break;
        case VERDE:
            for(int i = 0; i < num_ver; i++) {
                color.push_back(0.0f); color.push_back(1.0f); color.push_back(0.0f);
            }
            break;
        case AZUL:
            for(int i = 0; i < num_ver; i++) {
                color.push_back(0.0f); color.push_back(0.0f); color.push_back(1.0f);
            }
            break;
    }

}

void objeto3d::normalizar(vertice &normaliza) {
    float modulo;

    modulo = sqrt(normaliza.x * normaliza.x + normaliza.y * normaliza.y + normaliza.z * normaliza.z);
    normaliza.x /= modulo;
    normaliza.y /= modulo;
    normaliza.z /= modulo;
}

void objeto3d::calculoNVertices() {
    vertice a, b;
    vertice normalCara;   // Vector de normales de las caras que forman el objeto3d

    normalesVertices.assign(vertices.size(), normalCara);

    for(int i = 0; i < topologia.size(); i++) {
        a.x = vertices[topologia[i]._1].x - vertices[topologia[i]._0].x;
        a.y = vertices[topologia[i]._1].y - vertices[topologia[i]._0].y;
        a.z = vertices[topologia[i]._1].z - vertices[topologia[i]._0].z;

        b.x = vertices[topologia[i]._2].x - vertices[topologia[i]._0].x;
        b.y = vertices[topologia[i]._2].y - vertices[topologia[i]._0].y;
        b.z = vertices[topologia[i]._2].z - vertices[topologia[i]._0].z;

        normalCara.x = a.y * b.z - a.z * b.y;
        normalCara.y = a.z * b.x - a.x * b.z;
        normalCara.z = a.x * b.y - a.y * b.x;

        normalesVertices[topologia[i]._0] += normalCara;
        normalesVertices[topologia[i]._1] += normalCara;
        normalesVertices[topologia[i]._2] += normalCara;

    }

    for(int i = 0; i < normalesVertices.size(); i++)
        normalizar(normalesVertices[i]);

    //for(int i = 0; i < normalesVertices.size(); i++)
    //    cout << normalesVertices[i].x << " " << normalesVertices[i].y << " " << normalesVertices[i].z << endl;

}

void objeto3d::dibujar(M_visual modo) {

    int num_tri = topologia.size();

    switch(modo){
        case PUNTOS:
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            break;
        case LINES:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            break;
        default:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            break;
    }

    //for(int i = 0; i < vertices.size(); i++)
    //    vertices[i].imprimir();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState( GL_NORMAL_ARRAY );
    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
    glNormalPointer(GL_FLOAT, 0, &normalesVertices[0]);

    if (modo == CHESS) {
        CarasPares();
        cambiarColor(ROJO);
        glColorPointer( 3, GL_FLOAT, 0, &color[0] );
        glDrawElements(GL_TRIANGLES, 3 * (num_tri / 2), GL_UNSIGNED_INT, &CarasPares()[0]);
        CarasImpares();
        cambiarColor(AZUL);
        glColorPointer( 3, GL_FLOAT, 0, &color[0] );
        glDrawElements(GL_TRIANGLES, 3 * (num_tri / 2), GL_UNSIGNED_INT, &CarasImpares()[0]);
    }
    else if(modo == MEZCLA){

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        cambiarColor(ROJO);
        glColorPointer( 3, GL_FLOAT, 0, &color[0] );
        glLineWidth(5.0);
        glDrawElements(GL_TRIANGLES, 3 * num_tri, GL_UNSIGNED_INT, &topologia[0]);
        glLineWidth(1.0);

        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        cambiarColor(VERDE);
        glColorPointer( 3, GL_FLOAT, 0, &color[0] );
        glPointSize(5.0);
        glDrawElements(GL_TRIANGLES, 3 * num_tri, GL_UNSIGNED_INT, &topologia[0]);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        cambiarColor(AZUL);
        glColorPointer( 3, GL_FLOAT, 0, &color[0] );
        glDrawElements(GL_TRIANGLES, 3 * num_tri, GL_UNSIGNED_INT, &topologia[0]);
    }
    else{
        glPointSize(5.0);
        glLineWidth(5.0);
        cambiarColor(AZUL);
        glColorPointer( 3, GL_FLOAT, 0, &color[0] );
        glDrawElements(GL_TRIANGLES, 3 * num_tri, GL_UNSIGNED_INT, &topologia[0]);
        glLineWidth(1.0);
    }

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

}
