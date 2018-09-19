// Adrián Jesús Peña Rodríguez          3º C2

#ifndef _ILUMINACION_H
#define _ILUMINACION_H

class iluminacion {
public:
    bool luces;
    int activa;
    int a, b;
public:
    iluminacion(const int &i);
    void activarPanelLuces();
    void desactivarPanelLuces();
    void mueveLuz(const float &x, const float &y, const float &z);
    void rotaLuz(const int &eje);
    void cambiaColor(const float &r, const float &g, const float &b);
};
#endif
