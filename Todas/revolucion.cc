// Adrián Jesús Peña Rodríguez          3º C2

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include "revolucion.h"

revolucion::revolucion(){

    vertices.push_back( vertice(1.0f, -1.4f, 0.0) );
    vertices.push_back( vertice(1.0f, -1.1f, 0.0) );
    vertices.push_back( vertice(0.5f, -0.7f, 0.0) );
    vertices.push_back( vertice(0.4f, 0.4f, 0.0) );
    vertices.push_back( vertice(0.4f, 0.5f, 0.0) );
    vertices.push_back( vertice(0.5f, 0.6f, 0.0) );
    vertices.push_back( vertice(0.3f, 0.6f, 0.0) );
    vertices.push_back( vertice(0.5f, 0.8f, 0.0) );
    vertices.push_back( vertice(0.55f, 1.0f, 0.0) );
    vertices.push_back( vertice(0.5f, 1.2f, 0.0) );
    vertices.push_back( vertice(0.3f, 1.4f, 0.0) );

    comprobarOrden();

    nvertperfil = vertices.size();
    numero_perfiles = 10;

    generarRevoluciones();
    detectaTapa();

    calculoNVertices();

}

revolucion::revolucion(vector<vertice> &puntos){

    vertices = puntos;

    comprobarOrden();

    nvertperfil = vertices.size();
    numero_perfiles = 10;

    generarRevoluciones();
    detectaTapa();

    calculoNVertices();


}

revolucion::revolucion(const std::string& nombre){
    _file_ply File_ply;

    File_ply.open(nombre);
    File_ply.read(vertices,topologia);

    comprobarOrden();

    nvertperfil = vertices.size();
    numero_perfiles = 10;

    generarRevoluciones();
    detectaTapa();

    calculoNVertices();

}

void revolucion::comprobarOrden(){
    vector<vertice> auxiliar;
    bool invertir = false;

    if(vertices[0].y > vertices.back().y)
        invertir = true;

    if(invertir){
        for(int i = vertices.size() - 1; i >= 0; i--)
            auxiliar.push_back(vertices[i]);

        vertices = auxiliar;
    }

}

float revolucion::convRadianes(float degrees) {
    return (degrees * M_PI / 180);
}

void revolucion::detectaTapa(){
    for(int i = 0; i < vertices.size(); i++)
        if(vertices[i].x == 0 && vertices[i].z == 0)
            tapas = true;

    tapas = false;

}

void revolucion::cambiaTapas(){

    if(!tapas){
        tapas = true;

        float altura_superior = vertices[nvertperfil - 1].y;

        vertices.push_back(
            vertice(
                0,
                altura_superior,
                0
            )
        );    // Tapa superior

        for(int i = nvertperfil - 1; i <= numero_perfiles * nvertperfil; i += nvertperfil)
            topologia.push_back(
                caras(
                    i + nvertperfil,
                    vertices.size() - 1,
                    i
                )
            );

        float altura_inferior = vertices[0].y;

        vertices.push_back(
            vertice(
                0,
                altura_inferior,
                0
            )
        );    // Tapa inferior

        for(int i = 0; i < numero_perfiles * nvertperfil; i += nvertperfil)
            topologia.push_back(
                caras(
                    i,
                    vertices.size() - 1,
                    i + nvertperfil
                )
            );
    }
    else{
        tapas = false;

        topologia.clear();
        generarRevoluciones();
    }

}

void revolucion::generarRevoluciones() {

    float grados = 360.0 / numero_perfiles;
    float radianes;

    topologia.clear();
    tapas = false;
    vertices.resize(nvertperfil);

    for (int j = 1; j <= numero_perfiles; j++) {
        radianes = convRadianes(grados * j);

        for (int i = 0; i < nvertperfil; i++) {
            vertices.push_back(
                vertice(
                    cos(radianes) * vertices[i].x + sin(radianes) * vertices[i].z,
                    vertices[i].y,
                    -sin(radianes) * vertices[i].x + cos(radianes) * vertices[i].z
                )
            );
        }
    }

    for (int i = 0; i < numero_perfiles; i++) {
        for (int j = 0; j < nvertperfil - 1; j++) {
            topologia.push_back(
                caras(
                    j + 1 + nvertperfil * i,
                    j + nvertperfil * i,
                    j + nvertperfil * (i + 1)
                )
            );
            topologia.push_back(
                caras(
                    j + nvertperfil * (i + 1),
                    j + 1 + nvertperfil * (i + 1),
                    j + 1 + nvertperfil * i
                )
            );
        }
    }

}

void revolucion::cambiarRevoluciones(bool sentido) {
    bool tapa = tapas;

    if(sentido){
        numero_perfiles++;
        generarRevoluciones();
        if(tapa)
            cambiaTapas();
    }
    else{
        if(numero_perfiles > 3){
            numero_perfiles--;
            generarRevoluciones();
            if(tapa)
                cambiaTapas();
        }
    }
}
