// Adrián Jesús Peña Rodríguez          3º C2

#ifndef _REVOLUCION_H
#define _REVOLUCION_H
#include "objeto3d.h"

class revolucion : public objeto3d {
private:
    int nvertperfil;
    int numero_perfiles;
    bool tapas;
public:
    revolucion();
    revolucion(vector<vertice> &puntos);
    revolucion(const std::string& nombre);
    void comprobarOrden();
    float convRadianes(float grados);
    void detectaTapa();
    void cambiaTapas();
    void generarRevoluciones();
    void cambiarRevoluciones(bool sentido);
};
#endif
