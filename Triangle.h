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


#ifndef _TRIANGLE_H
#define _TRIANGLE_H

#include "Object.h"
#include "Vect.h"
#include "math.h"
#include "Color.h"

class Triangle : public Object{
    Vect A,B,C;
    Vect normal;
    //distance from origin
    double distance;
    Color color;

    public:

    //general constructor
    Triangle ();

    //another instance
    Triangle (Vect, Vect, Vect, Color);

    //method functions

    //Gets
    Vect getTriangleNormal() {
        Vect CA (C.getCoordinateX() - A.getCoordinateX(), C.getCoordinateY() - A.getCoordinateY(), C.getCoordinateZ() - A.getCoordinateZ());
        Vect BA (B.getCoordinateX() - A.getCoordinateX(), B.getCoordinateY() - A.getCoordinateY(), B.getCoordinateZ() - A.getCoordinateZ());
        normal = CA.crossProduct(BA).normalize();
        return normal;
    }
    double getTriangleDistance() {
        normal = getTriangleNormal();
        distance = normal.dotProduct(A);
        return distance;
    }
    virtual Color getColor() {
        return color;
    }

    //get normal in some point
    virtual Vect getNormalAt( Vect point){
        normal = getTriangleNormal();
        return normal;
    }

    //distance to thr ray oring to a point of intersection
    virtual double findIntersection(Ray ray){
        Vect ray_direction = ray.getRayDirection();
        Vect ray_origin = ray.getRayOrigin();

        normal = getTriangleNormal();
        distance = getTriangleDistance();

        
        double a = ray_direction.dotProduct(normal);

        //case of ray is parallel to the Triangle
        if ( a == 0 ) {
            return -1;
        }
        else {
            double b = normal.dotProduct(ray.getRayOrigin().vectAdd(normal.vectMult(distance).negative()));
            double distanceToPlane = -1*b/a;
            double Qx = ray_direction.vectMult(distanceToPlane).getCoordinateX() + ray_origin.getCoordinateX();
            double Qy = ray_direction.vectMult(distanceToPlane).getCoordinateY() + ray_origin.getCoordinateY();
            double Qz = ray_direction.vectMult(distanceToPlane).getCoordinateZ() + ray_origin.getCoordinateZ();

            Vect Q (Qx,Qy,Qz);

            Vect CA (C.getCoordinateX() - A.getCoordinateX(), C.getCoordinateY() - A.getCoordinateY(), C.getCoordinateZ() - A.getCoordinateZ());
            Vect QA (Q.getCoordinateX() - A.getCoordinateX(), Q.getCoordinateY() - A.getCoordinateY(), Q.getCoordinateZ() - A.getCoordinateZ());
            double test1 = (CA.crossProduct(QA)).dotProduct(normal);

            Vect BC (B.getCoordinateX() - C.getCoordinateX(), B.getCoordinateY() - C.getCoordinateY(), B.getCoordinateZ() - C.getCoordinateZ());
            Vect QC (Q.getCoordinateX() - C.getCoordinateX(), Q.getCoordinateY() - C.getCoordinateY(), Q.getCoordinateZ() - C.getCoordinateZ());
            double test2 = (BC.crossProduct(QC)).dotProduct(normal);

            Vect AB (A.getCoordinateX() - B.getCoordinateX(), A.getCoordinateY() - B.getCoordinateY(), A.getCoordinateZ() - B.getCoordinateZ());
            Vect QB (Q.getCoordinateX() - B.getCoordinateX(), Q.getCoordinateY() - B.getCoordinateY(), Q.getCoordinateZ() - B.getCoordinateZ());
            double test3 = (AB.crossProduct(QB)).dotProduct(normal);
            
            if((test1 >= 0 ) && (test2 >= 0 ) && (test3 >= 0 ) ){
                return -1*b/a;
                //inside the triangle
            }
            else { return -1; }

            //distance to the ray origin to the point of intersection
            return -1*b/a;
        }
    }
};

// default X direction
Triangle::Triangle () {
    A = Vect(1,0,0);
    B = Vect(0,1,0);
    C = Vect(0,0,1);
    color = Color(0.5,0.5,0.5, 0);
}

// not default origin and direction
Triangle::Triangle (Vect pointA, Vect pointB, Vect pointC, Color colorValue) {
    A = pointA;
    B = pointB;
    C = pointC;
    color = colorValue;
}

#endif