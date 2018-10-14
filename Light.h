/*
Graphics Computer 2018.2
Federal University of Ceará

Team: Leandro Almeida de Carvalho (Leader)
      Letícia Fernandes
      Levi 
      Karen
      Kayron

Professor: Creto Vidal
Work: Build a RayTracer to render a snowman with a image background.
*/

#ifndef _LIGHT_H
#define _LIGHT_H

#include "Vect.h"
#include "Color.h"


//Light is made of vectors (Origin and Direction)

class Light {
    Vect position;
    Color color;

    public:

    //general constructor
    Light ();

    //another instance
    Light (Vect,Color);

    //method functions

    //Gets (using virtual values)
    Vect getLightPosition() {return position;}
    Color getLightColor() {return color;}
};

// default origin 3d scene (0,0,0) and default direction is X on plan
Light::Light () {
    position = Vect(0,0,0);
    color = Color(1,1,1, 0);
}

// not default origin and direction
Light::Light (Vect p, Color c) {
    position = p;
    color = c;
}

#endif