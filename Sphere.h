#ifndef _SPHERE_H_
#define _SPHERE_H_
#include "Vector3.h"

// classe esfera que contém como atributos o raio e vetor centro.
class Sphere{
public:
    Sphere();
    Sphere(Vector3 c, float r);
    // o método intersection utiliza a fórmula para checar se há interseção de um vetor p dado como parametro
    // e retorna true se há interseção entre o vetor e a esfera e false caso não haja.
    bool intersection(Vector3 p);
    
    Vector3 center;
    float radius;
};

#endif // _SPHERE_H_
