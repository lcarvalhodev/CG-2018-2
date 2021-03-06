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

#ifndef _SPHERE_H
#define _SPHERE_H

#include "Object.h"
#include "Vect.h"
#include "math.h"
#include "Color.h"

// To render a sphere in 3D, we need the position of center and the radius
// This class is a subclass of class Object

class Sphere : public Object{
    
    //attributes for Sphere
    Vect center;
    double radius;
    Color color;

    public:

    //general constructor
    Sphere ();

    //another instance
    Sphere (Vect, double, Color);

    //method functions

    //Getters 
    Vect getSphereCenter() {
        return center;
    }
    double getSphereRadius() {
        return radius;
    }
    virtual Color getColor() {
        return color;
    }

    //Setters 
    void setSphereCenter(Vect centerValue) {
        center = centerValue;
    }
    void setSphereRadius(double radiusValue) {
        radius = radiusValue;
    }
    virtual void setColor( Color colorValue) {
        color = colorValue;
    }
    

    //Get Normal at some point
    virtual Vect getNormalAt(Vect point){
        //normal always points away from the center of a sphere
        Vect normal_Vect = point.vectAdd(center.negative()).normalize();
        return normal_Vect;
    }

    //Find intersection return a double representing the distance of the ray to the point of intersection
    virtual double findIntersection(Ray ray) {
        Vect ray_origin = ray.getRayOrigin();
        double ray_origin_x = ray_origin.getCoordinateX();
        double ray_origin_y = ray_origin.getCoordinateY();
        double ray_origin_z = ray_origin.getCoordinateZ();

        Vect ray_direction = ray.getRayDirection();
        double ray_direction_x = ray_direction.getCoordinateX();
        double ray_direction_y = ray_direction.getCoordinateY();
        double ray_direction_z = ray_direction.getCoordinateZ();

        Vect sphere_center = center;
        double sphere_center_x = sphere_center.getCoordinateX();
        double sphere_center_y = sphere_center.getCoordinateY();
        double sphere_center_z = sphere_center.getCoordinateZ();

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
                //the second root is the smallest positive root
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