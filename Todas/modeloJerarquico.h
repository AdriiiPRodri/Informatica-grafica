// Adrián Jesús Peña Rodríguez          3º C2

#ifndef _MODELOJERARQUICO_H
#define _MODELOJERARQUICO_H
#include "octaedro.h"
#include "revolucion.h"
#include "modeloPLY.h"
#include "iluminacion.h"
#include "material.h"

extern double rotacionCuerpo, tCCSilla, rotCSilla, escala, rotSilla, rotCCS;

class silla : public objeto3d {
private:
    modeloPLY* asiento;
public:
    silla();
    void dibujar(M_visual modo);
};

class cilindroSilla : public objeto3d {
private:
    silla* asiento;
    revolucion* cilindro;
public:
    cilindroSilla();
    void dibujar(M_visual modo);
};

class ccilindroSilla : public objeto3d {
private:
    cilindroSilla* cilSilla;
    revolucion* cilindro;
public:
    ccilindroSilla();
    void dibujar(M_visual modo);
};

class cccilindroSilla : public objeto3d {
private:
    ccilindroSilla* ccilSilla;
    revolucion* cilindro;
public:
    cccilindroSilla();
    void dibujar(M_visual modo);
};

class sillasCuerpo : public objeto3d {
private:
    cccilindroSilla* ccilSillaD;
    cccilindroSilla* ccilSillaP;
    cccilindroSilla* ccilSillaI;
    cccilindroSilla* ccilSillaC;
    revolucion* cilindro;
public:
    sillasCuerpo();
    void dibujar(M_visual modo);
};

class sillasCuerpoTecho : public objeto3d {
private:
    sillasCuerpo* cuerpoSilla;
    revolucion* techo;
public:
    sillasCuerpoTecho();
    void dibujar(M_visual modo);
};

class modeloJerarquico : public objeto3d {
private:
    sillasCuerpoTecho* cuerpo;
    revolucion* base;
    Octaedro* suelo;
    iluminacion* luz_jerarquico;
    Material* color_suelo;
    double topeCS, topeCCS, topeT, topeDerecha;
    bool ascenderCS, ascenderCCS, ascenderT, ascenderCombinado, moverDerecha;
public:
    modeloJerarquico();
    void dibujar(M_visual modo);
    void animar();
    void animarIndependiente();
};

#endif
