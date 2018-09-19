// Adrián Jesús Peña Rodríguez          3º C2

#ifndef _CAMARA_H
#define _CAMARA_H

enum M_camara {
    ORTOGONAL, PERSPECTIVA, BASICA
};

class camara {
private:
    int posicion_defecto_x, posicion_defecto_y, posicion_actual_x, posicion_actual_y;
    double left, right, bottom, top, nearVal, farVal, distancia, posicion_actual_x_m, posicion_actual_y_m;
    M_camara modelo;
public:
    camara(M_camara tipo = BASICA);
    double getPosicionActualX();
    double getPosicionActualY();
    void setObservadorDefecto();
    void setObservador();
    void setObservador(float distancia, float x, float y);
    void moverIzquierda();
    void moverDerecha();
    void moverArriba();
    void moverAbajo();
    void rotarIzquierda();
    void rotarDerecha();
    void rotarArriba();
    void rotarAbajo();
    void zoomOrt(bool in);
    bool ortogonal();
};
#endif
