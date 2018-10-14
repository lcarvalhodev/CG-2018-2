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

    //Gets 
    Vect getSphereCenter() {return center;}
    double getSphereRadius() {return radius;}
    virtual Color getColor() {return color;}

    //Get Normal at some point
    Vect getNormalAt(Vect point){
        //normal always points away from the center of a sphere
        Vect normal_Vect = point.vectAdd(center.negative()).normalize();
        return normal_Vect;
    }

    //Find intersection return a double representing th distance of the ray to the point of intersection
    virtual double findIntersection(Ray ray) {
        Vect ray_origin = ray.getRayOrigin();
        double ray_origin_x = ray_origin.getVectX();
        double ray_origin_y = ray_origin.getVectY();
        double ray_origin_z = ray_origin.getVectZ();

        Vect ray_direction = ray.getRayDirection();
        double ray_direction_x = ray_direction.getVectX();
        double ray_direction_y = ray_direction.getVectY();
        double ray_direction_z = ray_direction.getVectZ();

        Vect sphere_center = center;
        double sphere_center_x = sphere_center.getVectX();
        double sphere_center_y = sphere_center.getVectY();
        double sphere_center_z = sphere_center.getVectZ();

        double a = 1; //normalized
        double b = (2*(ray_origin_x - sphere_center_x)*ray_direction_x) + (2*(ray_origin_y - sphere_center_y)*ray_direction_y) + (2*(ray_origin_z - sphere_center_z)*ray_direction_z);
        double c = pow(ray_origin_x - sphere_center_x,2) + pow(ray_origin_y - sphere_center_y,2) + pow(ray_origin_z - sphere_center_z,2) - (radius*radius); 

        double discriminant = b*b - 4*c;

        
        if (discriminant > 0) {
            //the ray intersect the sphere

            //two roots to verify wich is closer to the camera
            double root_1 = ((-1*b - sqrt(discriminant))/ 2) - 0.001;

            if(root_1 > 0 ){
                //the first root is the smallest positive root
                return root_1;
            }

            else{
                //the second root is teh smallest positive root
                double root_2 = ((sqrt(discriminant) - b)/2) - 0.001;
                return root_2;
            }
        }
        //in case of discriminant is not greater than zero
        else{
            //the ray missed the sphere
            return -1;
        }
        
    }
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