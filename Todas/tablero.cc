// Adrián Jesús Peña Rodríguez          3º C2

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include "tablero.h"
#include <algorithm>

tablero::tablero(GLfloat tamanio, const int &m){

    vertice a(0.0, 0.0, 0.0);
    grados = 90;
    float incremento = 1.0;
    float contador = 0.0;
    int contador_topologia = 0;
    float altura = 0.0;
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    topologia.resize(2 * m * m);

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < m; j++) {
            if(j == 0) {
                /******** Primera columna del tablero ********/
                a.x = 0.0;  a.y = altura;   a.z = 0.0;
                if(find(vertices.begin(), vertices.end(), a) == vertices.end()) {
                    vertices.push_back(a);
                }
                topologia[contador_topologia]._0 = distance(vertices.begin(), find(vertices.begin(), vertices.end(), a));
                a.x = incremento;  a.y = altura;   a.z = 0.0;
                if(find(vertices.begin(), vertices.end(), a) == vertices.end()) {
                    vertices.push_back(a);
                }
                topologia[contador_topologia]._1 = distance(vertices.begin(), find(vertices.begin(), vertices.end(), a));
                a.x = 0.0;  a.y = altura + incremento;   a.z = 0.0;
                if(find(vertices.begin(), vertices.end(), a) == vertices.end()) {
                    vertices.push_back(a);
                }
                topologia[contador_topologia]._2 = distance(vertices.begin(), find(vertices.begin(), vertices.end(), a));

                a.x = incremento;  a.y = altura;   a.z = 0.0;
                if(find(vertices.begin(), vertices.end(), a) == vertices.end()) {
                    vertices.push_back(a);
                }
                topologia[contador_topologia + 1]._0 = distance(vertices.begin(), find(vertices.begin(), vertices.end(), a));
                a.x = incremento;  a.y = altura + incremento;   a.z = 0.0;
                if(find(vertices.begin(), vertices.end(), a) == vertices.end()) {
                    vertices.push_back(a);
                }
                topologia[contador_topologia + 1]._1 = distance(vertices.begin(), find(vertices.begin(), vertices.end(), a));
                a.x = 0.0;  a.y = altura + incremento;   a.z = 0.0;
                if(find(vertices.begin(), vertices.end(), a) == vertices.end()) {
                    vertices.push_back(a);
                }
                topologia[contador_topologia + 1]._2 = distance(vertices.begin(), find(vertices.begin(), vertices.end(), a));

                /*********************************************/
            }
            else {
                a.x = contador;  a.y = altura;   a.z = 0.0;
                if(find(vertices.begin(), vertices.end(), a) == vertices.end()) {
                    vertices.push_back(a);
                }
                topologia[contador_topologia]._0 = distance(vertices.begin(), find(vertices.begin(), vertices.end(), a));
                a.x = contador + incremento;  a.y = altura;   a.z = 0.0;
                if(find(vertices.begin(), vertices.end(), a) == vertices.end()) {
                    vertices.push_back(a);
                }
                topologia[contador_topologia]._1 = distance(vertices.begin(), find(vertices.begin(), vertices.end(), a));
                a.x = contador;  a.y = altura + incremento;   a.z = 0.0;
                if(find(vertices.begin(), vertices.end(), a) == vertices.end()) {
                    vertices.push_back(a);
                }
                topologia[contador_topologia]._2 = distance(vertices.begin(), find(vertices.begin(), vertices.end(), a));

                a.x = contador + incremento;  a.y = altura;   a.z = 0.0;
                if(find(vertices.begin(), vertices.end(), a) == vertices.end()) {
                    vertices.push_back(a);
                }
                topologia[contador_topologia + 1]._0 = distance(vertices.begin(), find(vertices.begin(), vertices.end(), a));
                a.x = contador + incremento;  a.y = altura + incremento;   a.z = 0.0;
                if(find(vertices.begin(), vertices.end(), a) == vertices.end()) {
                    vertices.push_back(a);
                }
                topologia[contador_topologia + 1]._1 = distance(vertices.begin(), find(vertices.begin(), vertices.end(), a));
                a.x = contador;  a.y = altura + incremento;   a.z = 0.0;
                if(find(vertices.begin(), vertices.end(), a) == vertices.end()) {
                    vertices.push_back(a);
                }
                topologia[contador_topologia + 1]._2 = distance(vertices.begin(), find(vertices.begin(), vertices.end(), a));

            }

            contador += incremento;
            contador_topologia += 2;
        }

        contador = 0.0;
        altura += incremento;
    }

    calculoNVertices();

}

void tablero::colocaTextura() {
    vector<float> coord;

    coord.push_back(0.0);
    coord.push_back(0.0);

    coordenadas.push_back(coord);

    coord.push_back(1.0);
    coord.push_back(0.0);

    coordenadas.push_back(coord);

    coord.push_back(0.0);
    coord.push_back(1.0);

    coordenadas.push_back(coord);

    coord.push_back(1.0);
    coord.push_back(1.0);

    coordenadas.push_back(coord);

    std::vector<unsigned char> data;

    CImg<unsigned char> imagen;
    imagen.load("./textura.jpg");

    for (long y = 0; y < imagen.height(); y ++)
       for (long x = 0; x < imagen.width(); x ++) {
     	 unsigned char *r = imagen.data(x, y, 0, 0);  // (x, y, z, color)
     	 unsigned char *g = imagen.data(x, y, 0, 1);
     	 unsigned char *b = imagen.data(x, y, 0, 2);
     	 data.push_back(*r);
     	 data.push_back(*g);
     	 data.push_back(*b);
       }

    glGenTextures(1, &textura_id);
    glBindTexture(GL_TEXTURE_2D, textura_id);

    glActiveTexture(GL_TEXTURE0);
    glEnable( GL_TEXTURE_GEN_S ); // desactivado inicialmente, se usan para que no tener que indicar coordenadas de textura
    glEnable( GL_TEXTURE_GEN_T ); // desactivado inicialmente
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // luces
    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);

    // TRASFIERE LOS DATOS A GPU
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagen.width(), imagen.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, &data[0]);
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, imagen.width(), imagen.height(), GL_RGB, GL_UNSIGNED_BYTE, &data[0]);
}

void tablero::rotarTextura() {
    glMatrixMode(GL_TEXTURE);
    //glLoadIdentity();
    glRotatef(grados,0.0,0.0,1.0);
    glMatrixMode(GL_MODELVIEW);
}

void tablero::moverTextura(const float &x, const float &y) {
    double aleatorio = ((double)rand() / (double)RAND_MAX);
    glMatrixMode(GL_TEXTURE);
    //glLoadIdentity();
    glTranslatef(x, y, 0.0);
    glMatrixMode(GL_MODELVIEW);
}

void tablero::dibuja() {

    int num_tri = topologia.size();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState( GL_NORMAL_ARRAY );
    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
    glNormalPointer(GL_FLOAT, 0, &normalesVertices[0]);
    glEnableClientState (GL_TEXTURE_COORD_ARRAY_EXT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textura_id);               // Cambia el IDENTIFICADOR de la TEXTURA activa
    glTexCoordPointer(2, GL_FLOAT, 0, &coordenadas[0]);

    glDrawElements(GL_TRIANGLES, 3 * num_tri, GL_UNSIGNED_INT, &topologia[0]);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

}

void tablero::libera_textura() {
   glDeleteTextures(1, &textura_id);
}
