#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "Vector3.h"

class Material{
public:
    Material();
    Material(Vector3 env, Vector3 dif, Vector3 spec);
    
    Vector3 environment;
    Vector3 diffuse;
    Vector3 specular;

};

#endif // _MATERIAL_H_
