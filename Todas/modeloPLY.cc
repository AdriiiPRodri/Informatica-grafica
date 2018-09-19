// Adrián Jesús Peña Rodríguez          3º C2

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include "modeloPLY.h"

modeloPLY::modeloPLY(const std::string& nombre){

    _file_ply File_ply;

    File_ply.open(nombre);
    File_ply.read(vertices,topologia);

    calculoNVertices();

}
