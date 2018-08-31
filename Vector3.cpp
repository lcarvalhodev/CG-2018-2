#include <iostream>
#include <cmath>
#include "Vector3.h"

using namespace std;

Vector3::Vector3(){
}

Vector3::Vector3(float uX, float uY, float uZ){
    this->x = uX;
    this->y = uY;
    this->z = uZ;
}

float Vector3::norma(){
    float n = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    return n;
}

void Vector3::normalizarVetor(){
    float n = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    
    if (n > 0){
        this->x = this->x / n;
        this->y = this->y / n;
        this->z = this->z / n;
    }
}

float Vector3::produtoEscalar(Vector3 v2){
    float e = (this->x * v2.x) + (this->y * v2.y) + (this->z * v2.z);
    return e;
}

void Vector3::showVector(){
    cout << "\nCoordenadas do vetor: " << this->x << ", " << this->y << ", " << this->z << ";" << endl;
}
