// Adrián Jesús Peña Rodríguez          3º C2

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include "modeloJerarquico.h"

double rotacionCuerpo, tCCSilla, rotCSilla, escala, rotSilla, rotCCS, mover;

silla::silla() {

    asiento = new modeloPLY("silla.ply");

};

void silla::dibujar(M_visual modo) {
    glPushMatrix();
        glRotatef(rotSilla,1.0,0.0,0.0);
        glTranslated(2.6,-1.0,0.0);
        glRotatef(270.0,1.0,0.0,0.0);
        glScalef(0.6,0.6,0.6);
        asiento->dibujar(modo);
    glPopMatrix();
};

cilindroSilla::cilindroSilla(){

    cilindro = new revolucion("cilindro.ply");
    asiento = new silla();

};

void cilindroSilla::dibujar(M_visual modo){
    glPushMatrix();
        glTranslated(1.0,0.0,0.0);
        glRotatef(270.0,0.0,0.0,1.0);
        glScalef(0.2,1.2,0.2);
        cilindro->dibujar(modo);
    glPopMatrix();

    asiento->dibujar(modo);

};

ccilindroSilla::ccilindroSilla() {
    cilSilla = new cilindroSilla();
    cilindro = new revolucion("cilindro.ply");
};

void ccilindroSilla::dibujar(M_visual modo){
    glPushMatrix();
        glTranslated(1.0,0.0,0.0);
        glRotatef(270.0,0.0,0.0,1.0);
        glScalef(0.2,1.2,0.2);
        cilindro->dibujar(modo);
    glPopMatrix();

    glPushMatrix();
        glTranslated(2.2,0.0,0.0);
        glRotatef(rotCSilla,0.0,0.0,1.0);        // Grado libertad de cilindro y silla
        cilSilla->dibujar(modo);
    glPopMatrix();

};

cccilindroSilla::cccilindroSilla() {
    ccilSilla = new ccilindroSilla();
    cilindro = new revolucion("cilindro.ply");
};

void cccilindroSilla::dibujar(M_visual modo){
    glPushMatrix();
        glTranslated(1.0,0.0,0.0);
        glRotatef(270.0,0.0,0.0,1.0);
        glScalef(0.2,1.2,0.2);
        cilindro->dibujar(modo);
    glPopMatrix();

    glPushMatrix();
        glTranslated(2.2,0.0,0.0);
        glRotatef(rotCSilla,0.0,0.0,1.0);        // Grado libertad de cilindro y silla
        ccilSilla->dibujar(modo);
    glPopMatrix();

};

sillasCuerpo::sillasCuerpo() {
    cilindro = new revolucion("cilindro.ply");
    ccilSillaD = new cccilindroSilla();
    ccilSillaP = new cccilindroSilla();
    ccilSillaI = new cccilindroSilla();
    ccilSillaC = new cccilindroSilla();
};

void sillasCuerpo::dibujar(M_visual modo) {

    glPushMatrix();
        glTranslated(0.0,tCCSilla,0.0);
        glTranslated(2.2,0.0,0.0);
        glRotatef(rotCCS,0.0,1.0,1.0);
        ccilSillaD->dibujar(modo);
    glPopMatrix();

    glPushMatrix();
        glRotatef(90.0,0.0,1.0,0.0);
        glTranslated(0.0,tCCSilla,0.0);
        glTranslated(2.2,0.0,0.0);
        glRotatef(rotCCS,0.0,1.0,1.0);
        ccilSillaP->dibujar(modo);
    glPopMatrix();

    glPushMatrix();
        glRotatef(180.0,0.0,1.0,0.0);
        glTranslated(0.0,tCCSilla,0.0);
        glTranslated(2.2,0.0,0.0);
        glRotatef(rotCCS,0.0,1.0,1.0);
        ccilSillaI->dibujar(modo);
    glPopMatrix();

    glPushMatrix();
        glRotatef(270.0,0.0,1.0,0.0);
        glTranslated(0.0,tCCSilla,0.0);
        glTranslated(2.2,0.0,0.0);
        glRotatef(rotCCS,0.0,1.0,1.0);
        ccilSillaC->dibujar(modo);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0.0,0.0,0.0);
        glScalef(2.5,4.0,2.5);
        cilindro->dibujar(modo);
    glPopMatrix();

};

sillasCuerpoTecho::sillasCuerpoTecho() {
    cuerpoSilla = new sillasCuerpo();
    techo = new revolucion("cilindro_punta.ply");
};

void sillasCuerpoTecho::dibujar(M_visual modo) {
    glPushMatrix();
        glTranslated(0.0,4.0,0.0);
        glScalef(1.0,escala,1.0);
        glScalef(5.0,0.4,5.0);
        techo->dibujar(modo);
    glPopMatrix();

    glPushMatrix();
        cuerpoSilla->dibujar(modo);
    glPopMatrix();
};

modeloJerarquico::modeloJerarquico(){

    topeCS = 40;
    topeCCS = 1.5;
    topeT = 3.0;
    topeDerecha = 20.0;

    rotacionCuerpo = tCCSilla = rotCSilla = rotSilla = rotCCS = mover = 0;
    escala = 1.0;

    ascenderCS = ascenderCCS = ascenderCombinado = ascenderT = moverDerecha = true;

    cuerpo = new sillasCuerpoTecho();
    base = new revolucion("cilindro.ply");
    suelo = new Octaedro();

    luz_jerarquico= new iluminacion(3);     // Luz 3, posicional
    color_suelo = new Material();
};

void modeloJerarquico::dibujar(M_visual modo){

    glPushMatrix();
        glTranslated(mover,-4.0,0.0);
        glScalef(5.0,0.8,5.0);
        base->dibujar(modo);
    glPopMatrix();

    glPushMatrix();
        glTranslated(mover,0.0,0.0);
        glRotatef(rotacionCuerpo,0.0,1.0,0.0);
        cuerpo->dibujar(modo);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-15.0,-10.0,-4.8);
        glScalef(30.0,10.0,30.0);
        suelo->cambiarColor();  // Por defecto gris
        //color_suelo->ponerMaterial(0.5,0.5,0.5);
        suelo->dibujar(FILL);
        //color_suelo->quitarMaterial();
    glPopMatrix();

    luz_jerarquico->activarPanelLuces();
    luz_jerarquico->cambiaColor(1.0, 1.0, 1.0);
    luz_jerarquico->mueveLuz(mover,7.0+escala,0.0);

};

void modeloJerarquico::animar() {

    if(mover == topeDerecha)
        moverDerecha = false;
    else if(mover == -topeDerecha)
        moverDerecha = true;

    if(rotCSilla == topeCS)
        ascenderCS = false;
    else if(rotCSilla == -topeCS)
        ascenderCS = true;

    if(std::abs(tCCSilla - topeCCS) < 0.001)
        ascenderCCS = false;
    else if(std::abs(tCCSilla + topeCCS) < 0.001)
        ascenderCCS = true;

    if(std::abs(escala - topeT) < 0.001)
        ascenderT = false;
    else if(std::abs(escala + 0.5) < 0.999)
        ascenderT = true;

    if(ascenderCS)
        rotCSilla += 5;
    else
        rotCSilla -= 5;

    if(moverDerecha)
        mover += 1.0;
    else
        mover -= 1.0;

    if(ascenderT)
        escala += 0.1;
    else
        escala -= 0.1;

    if(ascenderCCS)
        tCCSilla += 0.1;
    else
        tCCSilla -= 0.1;

    if(rotCCS == 30)
        ascenderCombinado = false;
    else if(rotCCS == 0)
        ascenderCombinado = true;

    if(ascenderCombinado)
        rotCCS+=3;
    else
        rotCCS-=3;

    if(rotacionCuerpo == 360) {
        rotacionCuerpo = 0;
        rotSilla = 0;
    }

    rotacionCuerpo+=3;
    rotSilla+=3;

};

void modeloJerarquico::animarIndependiente() {

    if(std::abs(tCCSilla - topeCCS) < 0.001)
        ascenderCCS = false;
    else if(std::abs(tCCSilla + topeCCS) < 0.001)
        ascenderCCS = true;

    if(ascenderCCS)
        tCCSilla += 0.1;
    else
        tCCSilla -= 0.1;

};
