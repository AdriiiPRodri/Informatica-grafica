// Adrián Jesús Peña Rodríguez          3º C2

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include "iluminacion.h"

/*
- Color difuso, que indica qué longitudes de onda refleja el material de forma difusa. Podemos
decir que es el color “base” del material.
- Color especular, que indica qué longitudes de onda refleja el material de forma especular, o
dicho de otra forma, el color de los brillos.
- Color ambiente, que se refiere al comportamiento del objeto cuando no le incide
directamente ninguna fuente de luz.
- Color de emisión, y se refiera a un comportamiento “artificial” que hace que se vea el objeto
incluso cuando no hay fuentes de luz activas. El objeto no iluminará a otros, no se convierte
en una fuente de luz, pero sí se vería en una escena a oscuras (algo así como las pegatinas
fluorescentes).
*/

iluminacion::iluminacion(const int &i){

    luces = false;
    activa = i;
    a = 0;
    b = 0;

}

void iluminacion::activarPanelLuces() {

    switch(activa) {
        case 0:
            glEnable(GL_LIGHT0);
            break;
        case 1:
            glEnable(GL_LIGHT1);
            break;
        case 2:
            glEnable(GL_LIGHT2);
            break;
        case 3:
            glEnable(GL_LIGHT3);
            break;
        case 4:
            glEnable(GL_LIGHT4);
            break;
        case 5:
            glEnable(GL_LIGHT5);
            break;
        case 6:
            glEnable(GL_LIGHT6);
            break;
        case 7:
            glEnable(GL_LIGHT7);
            break;
    }

    glEnable(GL_LIGHTING); // Activa el modelo de iluminación local

    luces = true;

}

void iluminacion::desactivarPanelLuces() {

    cambiaColor(0.0, 0.0, 0.0);

    switch(activa) {
        case 0:
            glDisable(GL_LIGHT0);
            break;
        case 1:
            glDisable(GL_LIGHT1);
            break;
        case 2:
            glDisable(GL_LIGHT2);
            break;
        case 3:
            glDisable(GL_LIGHT3);
            break;
        case 4:
            glDisable(GL_LIGHT4);
            break;
        case 5:
            glDisable(GL_LIGHT5);
            break;
        case 6:
            glDisable(GL_LIGHT6);
            break;
        case 7:
            glDisable(GL_LIGHT7);
            break;
    }

    glDisable(GL_LIGHTING); // Activa el modelo de iluminación local
    luces = false;

}

void iluminacion::mueveLuz(const float &x, const float &y, const float &z) {

    const GLfloat posf[4] = { x, y, z, 0.0 } ; // (x,y,z,w)
    const GLfloat posa[4] = { x, y, z, 1.0 } ; // (x,y,z,w)

    switch(activa) {
        case 0:
            glLightfv( GL_LIGHT0, GL_POSITION, posf );
            break;
        case 1:
            glLightfv( GL_LIGHT1, GL_POSITION, posa );
            break;
        case 2:
            glLightfv( GL_LIGHT2, GL_POSITION, posf );
            break;
        case 3:
            glLightfv( GL_LIGHT3, GL_POSITION, posa );
            break;
        case 4:
            glLightfv( GL_LIGHT4, GL_POSITION, posf );
            break;
        case 5:
            glLightfv( GL_LIGHT5, GL_POSITION, posa );
            break;
        case 6:
            glLightfv( GL_LIGHT6, GL_POSITION, posf );
            break;
        case 7:
            glLightfv( GL_LIGHT7, GL_POSITION, posa );
            break;
    }

}

void iluminacion::rotaLuz(const int &eje) {
    float ej[4] = {0.0, 0.0, 0.0, 0.0};
    float ej1[4] = {0.0, 0.0, 0.0, 0.0};        // El último número hace referencia a si es posional (0) o no (1)

    if(eje == 0) {
        ej[0] = 1.0;
        ej1[0] = 1.0;
    }
    else if(eje == 1) {
        ej[1] = 1.0;
        ej1[2] = 1.0;
    }
    else {
        ej[2] = 1.0;
        ej1[2] = 1.0;
    }

    glMatrixMode( GL_MODELVIEW ) ;
    glPushMatrix() ;
    glLoadIdentity() ;
    if(eje == 0) {
        glRotatef( a, 0.0, 0.0, -1.0 ) ;
        glRotatef( b, 0.0, 1.0, 0.0 ) ;
    }
    else if(eje == 1) {
        glRotatef( a, 0.0, 0.0, 1.0 ) ;
        glRotatef( b, 0.0, -1.0, 0.0 ) ;
    }
    else {
        glRotatef( a, 0.0, 1.0, 0.0 ) ;
        glRotatef( b, -1.0, 0.0, 0.0 ) ;
    }

    switch(activa) {
        case 0:
            glLightfv( GL_LIGHT0, GL_POSITION, ej );
            break;
        case 1:
            glLightfv( GL_LIGHT1, GL_POSITION, ej1 );
            break;
        case 2:
            glLightfv( GL_LIGHT2, GL_POSITION, ej );
            break;
        case 3:
            glLightfv( GL_LIGHT3, GL_POSITION, ej1 );
            break;
        case 4:
            glLightfv( GL_LIGHT4, GL_POSITION, ej );
            break;
        case 5:
            glLightfv( GL_LIGHT5, GL_POSITION, ej1 );
            break;
        case 6:
            glLightfv( GL_LIGHT6, GL_POSITION, ej );
            break;
        case 7:
            glLightfv( GL_LIGHT7, GL_POSITION, ej1 );
            break;
    }
    glPopMatrix() ;

    a += 5;
    b += 5;

    if(a == 360)
        a = 0;
    if(b == 360)
        b = 0;
}

void iluminacion::cambiaColor(const float &r, const float &g, const float &b) {

    const float caf[4] = { r, g, b, 1.0 };   // color ambiental de la fuente
    const float cdf[4] = { r, g, b, 1.0 };   // color difuso de la fuente
    const float csf[4] = { r, g, b, 1.0 };   // color especular de la fuente

    switch(activa) {
        case 0:
            glLightfv( GL_LIGHT0, GL_AMBIENT, caf ) ;   // hace SiA := (ra, ga, ba)
            glLightfv( GL_LIGHT0, GL_DIFFUSE, cdf ) ;   // hace SiD := (rd, gd, bd)
            glLightfv( GL_LIGHT0, GL_SPECULAR, csf ) ;  // hace SiS := (rs, gs, bs)
            break;
        case 1:
            glLightfv( GL_LIGHT1, GL_AMBIENT, caf ) ;   // hace SiA := (ra, ga, ba)
            glLightfv( GL_LIGHT1, GL_DIFFUSE, cdf ) ;   // hace SiD := (rd, gd, bd)
            glLightfv( GL_LIGHT1, GL_SPECULAR, csf ) ;  // hace SiS := (rs, gs, bs)
            break;
        case 2:
            glLightfv( GL_LIGHT2, GL_AMBIENT, caf ) ;   // hace SiA := (ra, ga, ba)
            glLightfv( GL_LIGHT2, GL_DIFFUSE, cdf ) ;   // hace SiD := (rd, gd, bd)
            glLightfv( GL_LIGHT2, GL_SPECULAR, csf ) ;  // hace SiS := (rs, gs, bs)
            break;
        case 3:
            glLightfv( GL_LIGHT3, GL_AMBIENT, caf ) ;   // hace SiA := (ra, ga, ba)
            glLightfv( GL_LIGHT3, GL_DIFFUSE, cdf ) ;   // hace SiD := (rd, gd, bd)
            glLightfv( GL_LIGHT3, GL_SPECULAR, csf ) ;  // hace SiS := (rs, gs, bs)
            break;
        case 4:
            glLightfv( GL_LIGHT4, GL_AMBIENT, caf ) ;   // hace SiA := (ra, ga, ba)
            glLightfv( GL_LIGHT4, GL_DIFFUSE, cdf ) ;   // hace SiD := (rd, gd, bd)
            glLightfv( GL_LIGHT4, GL_SPECULAR, csf ) ;  // hace SiS := (rs, gs, bs)
            break;
        case 5:
            glLightfv( GL_LIGHT5, GL_AMBIENT, caf ) ;   // hace SiA := (ra, ga, ba)
            glLightfv( GL_LIGHT5, GL_DIFFUSE, cdf ) ;   // hace SiD := (rd, gd, bd)
            glLightfv( GL_LIGHT5, GL_SPECULAR, csf ) ;  // hace SiS := (rs, gs, bs)
            break;
        case 6:
            glLightfv( GL_LIGHT6, GL_AMBIENT, caf ) ;   // hace SiA := (ra, ga, ba)
            glLightfv( GL_LIGHT6, GL_DIFFUSE, cdf ) ;   // hace SiD := (rd, gd, bd)
            glLightfv( GL_LIGHT6, GL_SPECULAR, csf ) ;  // hace SiS := (rs, gs, bs)
            break;
        case 7:
            glLightfv( GL_LIGHT7, GL_AMBIENT, caf ) ;   // hace SiA := (ra, ga, ba)
            glLightfv( GL_LIGHT7, GL_DIFFUSE, cdf ) ;   // hace SiD := (rd, gd, bd)
            glLightfv( GL_LIGHT7, GL_SPECULAR, csf ) ;  // hace SiS := (rs, gs, bs)
            break;
    }

}
