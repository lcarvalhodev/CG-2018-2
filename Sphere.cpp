#include "Sphere.h"

Sphere::Sphere(){
}

Sphere::Sphere(Vector3 c, float r, Material m){
    this->center = c;
    this->radius = r;
    this->material = m;
}

bool Sphere::intersection(Vector3 p){
    float a = p.dot(p);
    float b = 2*(p.dot(this->center));
    float c = this->center.dot(this->center);
    c -= (this->radius * this->radius);
    float delta = ((b * b) - 4 * a * c);
    bool inter = false;
    if (delta > 0){
        inter = true;
    }
    return inter;
}