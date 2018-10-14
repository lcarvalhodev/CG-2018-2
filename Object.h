#ifndef _OBJECT_H
#define _OBJECT_H

#include "Vect.h"
#include "Ray.h"
#include "Color.h"

// This class will be base to all other obect class
class Object {

    public:

    //general constructor
    Object ();

    //Get color
    Color getObjectColor() {return Color( 0.0, 0.0 ,0.0 , 0); }

    // method to find intersection
    double findIntersectiom( Ray ray){
        return 0;
    }
};

Object::Object () {}


#endif