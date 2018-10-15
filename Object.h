/*
Graphics Computer 2018.2
Federal University of Ceará

Team: Leandro Almeida de Carvalho (Leader)
      Letícia Fernandes
      Levi Tavares
      Karen Raiany
      Kayron Melo

Professor: Creto Vidal
Work: Build a RayTracer to render a snowman with a image background.
*/


#ifndef _OBJECT_H
#define _OBJECT_H

#include "Vect.h"
#include "Ray.h"
#include "Color.h"

// This class will be base to all other object class like sphere or plane
class Object {

    public:

    //general constructor
    Object ();

    //Get color
    virtual Color getColor() {
        return Color( 0.0, 0.0 ,0.0 , 0); 
    }

    virtual Vect getNormalAt(Vect intersection_position){ 
        return Vect(0,0,0);
    }

    // method to find intersection
    virtual double findIntersection( Ray ray){
        return 0;
    }
};

Object::Object () {}


#endif