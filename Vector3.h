class Vector3{
public:
    float x, y, z;
    Vector3();
    Vector3(float uX, float uY, float uZ);
    
    Vector3 operator+(Vector3 v2){
        return Vector3(x + v2.x, y + v2.y, z + v2.z);
    }
    Vector3 operator-(Vector3 v2){
        return Vector3(x - v2.x, y - v2.y, z - v2.z);
    }
    void operator*=(float e){
        x *= e;
        y *= e;
        z *= e;
    }
    Vector3 operator*(float e){
        return Vector3(x * e, y * e, z * e);
    }
    void operator/=(float e){
        x /= e;
        y /= e;
        z /= e;
    }
    Vector3 operator/(float e){
        return Vector3(x / e, y / e, z / e);
    }
    
    Vector3 produtoVetorial(Vector3 v2){
        return Vector3(y * v2.z - z * v2.y,
                       z * v2.x - x * v2.z,
                       x * v2.y - y * v2.x);
    }
    
    void operator%=(Vector3 v2){
        *this = produtoVetorial(v2);
    }
    
    Vector3 operator%(Vector3 v2){
        return Vector3(y * v2.z - z * v2.y,
                       z * v2.x - x * v2.z,
                       x * v2.y - y * v2.x);
    }
    
    float norma();
    void normalizarVetor();
    float produtoEscalar(Vector3 v2);
    void showVector();
};
