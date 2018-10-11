#include "Material.h"

Material::Material(){
}


Material::Material(Vector3 env, Vector3 dif, Vector3 spec){
    this->environment = env;
    this->diffuse = dif;
    this->specular = spec;
}
