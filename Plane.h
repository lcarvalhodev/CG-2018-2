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


#ifndef _PLANE_H
#define _PLANE_H

#include "Object.h"
#include "Vect.h"
#include "math.h"
#include "Color.h"

class Plane : public Object{
    Vect normal;
    //distance from origin
    double distance;
    Color color;

    public:

    //general constructor
    Plane ();

    //another instance
    Plane (Vect, double, Color);

    //method functions

    //Gets
    Vect getPlaneNormal() {
        return normal;
    }
    double getPlaneDistance() {
        return distance;
    }
    virtual Color getColor() {
        return color;
    }

    //get normal in some point
    virtual Vect getNormalAt( Vect point){
        return normal;
    }

    //distance to thr ray oring to a point of intersection
    virtual double findIntersection(Ray ray){
        Vect ray_direction = ray.getRayDirection();
        
        double a = ray_direction.dotProduct(normal);

        //case of ray is parallel to the plane
        if ( a == 0 ) {
            return -1;
        }
        else {

            double b = normal.dotProduct(ray.getRayOrigin().vectAdd(normal.vectMult(distance).negative()));
            //distance to the ray origin to the point of intersection
            return -1*b/a;
        }
    }
};

// default X direction
Plane::Plane () {
    normal = Vect(1,0,0);
    distance = 0.0;
    color = Color(0.5,0.5,0.5, 0);
}

// not default origin and direction
Plane::Plane (Vect normalValue, double distanceValue, Color colorValue) {
    normal = normalValue;
    distance = distanceValue;
    color = colorValue;
}

#endif