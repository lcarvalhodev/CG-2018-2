#ifndef _CAMERA_H
#define _CAMERA_H

#include "Vect.h"


//Camera is 4 vector (position, direction, right and down)

class Camera {
    Vect camPos;
    Vect camDir;
    Vect camRight;
    Vect camDown;

    public:

    //general constructor
    Camera ();

    //another instance
    Camera (Vect,Vect,Vect,Vect);

    //method functions

    //Gets
    Vect getCameraPosition() {return camPos;}
    Vect getCameraDirection() {return camDir;}
    Vect getCameraRight() {return camRight;}
    Vect getCameraDown() {return camDown;}

};

// default Camera is Z direction
Camera::Camera () {
    camPos = Vect(0,0,0);
    camDir = Vect(0,0,1);
    camRight = Vect(0,0,0);
    camDown = Vect(0,0,0);
}

// not default pos,dir,right and down
Camera::Camera (Vect pos, Vect dir,Vect right, Vect down) {
    camPos = pos;
    camDir = dir;
    camRight = right;
    camDown = down;
}

#endif