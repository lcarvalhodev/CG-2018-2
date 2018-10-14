#ifndef _SPHERE_H
#define _SPHERE_H

#include "Object.h"
#include "Vect.h"
#include "math.h"
#include "Color.h"

// To render a sphere in 3D, we need the position of center and the radius

class Sphere : public Object{
    Vect center;
    double radius;
    Color color;

    public:

    //general constructor
    Sphere ();

    //another instance
    Sphere (Vect, double, Color);

    //method functions

    //Gets (using virtual values)
    Vect getSphereCenter() {return center;}
    double getSphereRadius() {return radius;}
    Color getSphereColor() {return color;}
};

// default origin 3d scene (0,0,0) and default radius 1, and default color gray
Sphere::Sphere () {
    center = Vect(0,0,0);
    radius = 1;
    color = Color(0.5,0.5,0.5, 0);
}

// not default origin and direction
Sphere::Sphere (Vect centerValue, double radiusValue, Color colorValue) {
    center = centerValue;
    radius = radiusValue;
    color = colorValue;
}

#endif