// Adrián Jesús Peña Rodríguez          3º C2

#ifndef _SEMICIRCULO_H
#define _SEMICIRCULO_H
#include "objeto3d.h"
#include "revolucion.h"

class semiCirculo : public objeto3d {
private:
    revolucion* semiC;
public:
    semiCirculo(GLfloat tamanio = 1.0f);
    float convRadianes(float degrees);
};
#endif
