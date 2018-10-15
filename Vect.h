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

    //Getters coordinates from a Vect
    double getCoordinateX() {return x; }
    double getCoordinateY() {return y; }
    double getCoordinateZ() {return z; }

    //Setters
    void setVectX(double xValue) {x=xValue; }
    void setVectY(double yValue) {y=yValue; }
    void setVectZ(double zValue) {z=zValue; }

    //magnitude function
    double magnitude() {
        return sqrt((x*x) + (y*y) + (z*z));
    }

    //normalize vector function
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
        return x*v.getCoordinateX() + y*v.getCoordinateY() + z*v.getCoordinateZ();
    }

    Vect crossProduct(Vect v) {
        return Vect(y*v.getCoordinateZ() - z*v.getCoordinateY(), z*v.getCoordinateX() - x*v.getCoordinateZ(), x*v.getCoordinateY() - y*v.getCoordinateX() );
    }

    //Add vects
    Vect vectAdd( Vect v ){
        return Vect (x+v.getCoordinateX(), y+ v.getCoordinateY(), z+v.getCoordinateZ());
    }

    //multiply vects
    Vect vectMult( double scalar ) {
        return Vect ( x*scalar, y*scalar, z*scalar);
    }
};

//default values for Vect
Vect::Vect () {
    x=0;
    y=0;
    z=0;
}

//initializing vector with defined values
Vect::Vect (double i, double j, double k) {
    x=i;
    y=j;
    z=k;
}

#endif