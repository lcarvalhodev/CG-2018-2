#ifndef _VECTOR3_H_
#define _VECTOR3_H_

class Vector3{
public:
    // declaração das coordenadas x, y e z do vetor.
    float x, y, z;
    
    // construtores da classe Vector3, um sem argumentos que seta x, y e z para zero, e outro que recebe os 3 valores.
    Vector3();
    Vector3(float uX, float uY, float uZ);
    
    // atributos estáticos dos vetores que apontam para as respectivas direções.
    static Vector3 UP;
    static Vector3 DOWN;
    static Vector3 LEFT;
    static Vector3 RIGHT;
    static Vector3 BACK;
    static Vector3 FORWARD;
    static Vector3 ONE;
    static Vector3 ZERO;
    
    // operador + que será usado para somar 2 vetores.
    Vector3 operator+(Vector3 v2){
        return Vector3(x + v2.x, y + v2.y, z + v2.z);
    }
    // operador - que será usado para subtrair 2 vetores.
    Vector3 operator-(Vector3 v2){
        return Vector3(x - v2.x, y - v2.y, z - v2.z);
    }
    // operador *= que será usado para multiplicar o proprio vetor por uma escalar e.
    void operator*=(float e){
        x *= e;
        y *= e;
        z *= e;
    }
    // operador * que multiplica um vetor por uma escalar e e retorna o resultado em um novo vetor.
    Vector3 operator*(float e){
        return Vector3(x * e, y * e, z * e);
    }
    // operador /= que divide o proprio vetor por uma escalar e.
    void operator/=(float e){
        x /= e;
        y /= e;
        z /= e;
    }
    // operador / que divide o vetor por uma escalar e e retorna o resultado em um novo vetor.
    Vector3 operator/(float e){
        return Vector3(x / e, y / e, z / e);
    }
    // operador %= que faz o produto vetorial entre o proprio vetor por um vetor v2 e coloca o resultado no proprio vetor.
    void operator%=(Vector3 v2){
        *this = cross(v2);
    }
    // operador % que faz o produto vetorial entre o proprio vetor e um vetor v2 e retorna o resultado em um novo vetor.
    Vector3 operator%(Vector3 v2){
        return Vector3(y * v2.z - z * v2.y,
                       z * v2.x - x * v2.z,
                       x * v2.y - y * v2.x);
    }
    // operador == que retorna true se os valores dos 2 vetores forem iguais (precisão de 6 casas decimais) e false caso contrario.
    bool operator==(Vector3 v2){
        if (x == v2.x && y == v2.y && z == v2.z){
            return true;
        } else {
            return false;
        }
    }
    // operador != que retorna false se os valores dos 2 vetores forem iguais (precisão de 6 casas decimais) e true caso contrario.
    bool operator!=(Vector3 v2){
        if (x == v2.x && y == v2.y && z == v2.z){
            return false;
        } else {
            return true;
        }
    }
    
    // declaração de métodos que respectivamente retornam a norma do vetor, normaliza o vetor, retorna o produto escalar do vetor com um vetor v2,
    // retorna um vetor com o produto vetorial do proprio vetor com um vetor v2, retorna o angulo entre 2 vetores, retorna o vetor refletido em relação
    // a normal de um plano e um método que printa as coordenadas x, y e z do vetor.
    float norma();
    void normalizarVetor();
    float dot(Vector3 v2);
    Vector3 cross(Vector3 v2);
    float angle(Vector3 v2);
    Vector3 reflect(Vector3 normal);
    void showVector();
};
#endif // _VECTOR3_H_