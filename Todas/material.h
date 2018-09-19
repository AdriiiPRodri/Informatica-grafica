// Adrián Jesús Peña Rodríguez          3º C2

#ifndef _MATERIAL_H
#define _MATERIAL_H

class Material {
public:
    bool material;
public:
    Material();
    void ponerMaterial(const float &r, const float &g, const float &b);
    void quitarMaterial();
};
#endif
