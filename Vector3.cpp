#include <iostream>
#include <cmath>
#include "Vector3.h"
#define PI 3.141592

using namespace std;

// abaixo estão as implementações dos métodos declarados no Vector3.h e a atribuição estática dos vetores que apontam nas direções especificadas.
Vector3::Vector3(){
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vector3::Vector3(float uX, float uY, float uZ){
    this->x = uX;
    this->y = uY;
    this->z = uZ;
}

Vector3 Vector3::UP = Vector3(0, 1, 0);
Vector3 Vector3::DOWN = Vector3(0, -1, 0);
Vector3 Vector3::LEFT = Vector3(-1, 0, 0);
Vector3 Vector3::RIGHT = Vector3(1, 0, 0);
Vector3 Vector3::BACK = Vector3(0, 0, -1);
Vector3 Vector3::FORWARD = Vector3(0, 0, 1);
Vector3 Vector3::ONE = Vector3(1, 1, 1);
Vector3 Vector3::ZERO = Vector3(0, 0, 0);

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

Vector3 Vector3::produtoVetorial(Vector3 v2){
    return Vector3(y * v2.z - z * v2.y,
                    z * v2.x - x * v2.z,
                    x * v2.y - y * v2.x);
}

float Vector3::produtoEscalar(Vector3 v2){
    float e = (this->x * v2.x) + (this->y * v2.y) + (this->z * v2.z);
    return e;
}

float Vector3::angle(Vector3 v2){
    float e = (this->x * v2.x) + (this->y * v2.y) + (this->z * v2.z);
    float n1 = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    float n2 = sqrt(v2.x * v2.x + v2.y * v2.y + v2.z * v2.z);
    float rad = acos(e / (n1 * n2));
    float degree = (180 * rad) / PI;
    
    return degree;
}

Vector3 Vector3::reflect(Vector3 normal){
    float e1 = this->produtoEscalar(normal);
    float e2 = e1 * 2;
    Vector3 v1 = normal * e2;
    Vector3 res = *this - v1;
    
    return res;
}

void Vector3::showVector(){
    cout << "\nCoordenadas do vetor: " << this->x << ", " << this->y << ", " << this->z << ";" << endl;
}
