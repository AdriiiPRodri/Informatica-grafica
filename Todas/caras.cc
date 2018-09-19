// Adrián Jesús Peña Rodríguez          3º C2

#ifdef _WIN32
#include <windows.h>
#endif

#include "caras.h"
#include <iostream>

caras::caras() {
    this->_0 = 0;
    this->_1 = 0;
    this->_2 = 0;
}

caras::caras(int x, int y, int z) {
    this->_0 = x;
    this->_1 = y;
    this->_2 = z;
}

caras& caras::operator=(const caras &caras) {
    if (&caras != this) {
        _0 = caras._0;
        _1 = caras._1;
        _2 = caras._2;
    }

    return *this;
}

bool caras::operator==(const caras &caras) {
    if (&caras != this)
        if(_0 != caras._0 || _1 != caras._1 || _2 != caras._2)
            return false;

    return true;
}

void caras::imprimir(){
    std::cout << this->_0 << " " << this->_1 << " " << this->_2 << std::endl;
}
