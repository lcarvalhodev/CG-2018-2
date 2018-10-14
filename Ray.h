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

#ifndef _RAY_H
#define _RAY_H

#include "Vect.h"


//Ray is made of vectors (Origin and Direction)

class Ray {
    Vect origin;
    Vect direction;

    public:

    //general constructor
    Ray ();

    //another instance
    Ray (Vect,Vect);

    //method functions

    //Gets
    Vect getRayOrigin() {return origin;}
    Vect getRayDirection() {return direction;}
};

// default origin 3d scene (0,0,0) and default direction is X on plan
Ray::Ray () {
    origin = Vect(0,0,0);
    direction = Vect(1,0,0);
}

// not default origin and direction
Ray::Ray (Vect o, Vect d) {
    origin = o;
    direction = d;
}

#endif