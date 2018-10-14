#ifndef _VECT_H
#define _VECT_H

#include "math.h"


class Vect {
    double x,y,z;

    public:

    //general constructor
    Vect ();

    //another instance
    Vect (double,double,double);

    //method functions

    //Gets
    double getVectX() {return x; }
    double getVectY() {return y; }
    double getVectZ() {return z; }

    //magnitude
    double magnitude() {
        return sqrt((x*x) + (y*y) + (z*z));
    }

    //normalize vector
    Vect normalize(){
        double magnitude = sqrt((x*x) + (y*y) + (z*z));
        return Vect(x/magnitude, y/magnitude, z/magnitude);
    }

    //invert vector using negative values
    Vect negative(){
        return Vect (-x,-y,-z);
    }

    //Vect produts
    double dotProduct ( Vect v) {
        return x*v.getVectX() + y*v.getVectY() + z*v.getVectZ();
    }

    Vect crossProduct(Vect v) {
        return Vect(y*v.getVectZ() - z*v.getVectY(), z*v.getVectX() - x*v.getVectZ(), x*v.getVectY() - y*v.getVectX() );
    }

    //Add vects
    Vect vectAdd( Vect v ){
        return Vect (x+v.getVectX(), y+ v.getVectY(), z+v.getVectZ());
    }

    //multiply vects
    Vect vectMult( double scalar ) {
        return Vect ( x*scalar, y*scalar, z*scalar);
    }
};

Vect::Vect () {
    x=0;
    y=0;
    z=0;
}

Vect::Vect (double i, double j, double k) {
    x=i;
    y=j;
    z=k;
}

#endif