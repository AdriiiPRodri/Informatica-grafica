// Adrián Jesús Peña Rodríguez          3º C2

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include "material.h"

Material::Material(){

    material = false;

}

void Material::ponerMaterial(const float &r, const float &g, const float &b) {

    GLfloat color[4] = { r, g, b, 1.0 } ;
    // hace MA := (r, g, b), inicialmente (0.2,0.2,0.2)
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, color ) ;
    // hace MD := (r, g, b), inicialmente (0.8,0.8,0.8)
    GLfloat color1[4] = { r, g, b, 1.0 } ;
    glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, color1 ) ;
    // hace MS := (r, g, b), inicialmente (0,0,0)
    GLfloat color2[4] = { 1.0, 1.0, 1.0, 1.0 } ;
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, color2 ) ;

    material = true;

}

void Material::quitarMaterial() {

    GLfloat color[4] = { 0.2, 0.2, 0.2, 1.0 } ;
    // hace MA := (r, g, b), inicialmente (0.2,0.2,0.2)
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, color ) ;
    // hace MD := (r, g, b), inicialmente (0.8,0.8,0.8)
    GLfloat color1[4] = { 0.8, 0.8, 0.8, 1.0 } ;
    glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, color1 ) ;
    // hace MS := (r, g, b), inicialmente (0,0,0)
    //glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, color ) ;

    glDisable(GL_COLOR_MATERIAL);

    material = false;

}
