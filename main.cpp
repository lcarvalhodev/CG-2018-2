#include <iostream>
#include "Vector3.h"
#include "Sphere.h"
#include <math.h>
#include <GL/glut.h>
#include <GL/glext.h>

#define PI 3.141592

#define WINDOW_HEIGHT 500
#define WINDOW_WIDTH 500
#define WINDOW_POSITION -10

#define CAMERA_X 200
#define CAMERA_Y 250
#define CAMERA_Z -500

using namespace std;

Vector3 camera(CAMERA_X, CAMERA_Y, CAMERA_Z);

Vector3 iEnv(0.5, 0.5, 0.8);

Vector3 lightOrigin(20, 10, -400);
Vector3 lightColor(1, 1, 1);

Vector3 mat_env(0.3, 0.3, 0.3);
Vector3 mat_dif(0.8, 0.8, 0.8);
Vector3 mat_spec(0.6, 0.6, 0.6);
Material mat_teste(mat_env, mat_dif, mat_spec);

Vector3 mat_env2(0.8, 0, 0);
Vector3 mat_dif2(1, 1, 1);
Vector3 mat_spec2(0.5, 0.5, 0.5);
Material mat_teste2(mat_env2, mat_dif2, mat_spec2);

Vector3 origin1(200, 250, -50);
Sphere sphere1(origin1, 100, mat_teste);

Vector3 origin2(300, 300, -70);
Sphere sphere2(origin2, 200, mat_teste2);

Sphere spheres[] = {sphere1, sphere2};


float W = 50.0, H = 50.0;

//bool inter = true;
float x = 0.0, y = 0.0;
float raio = 10;
float x_centro = 0;
float y_centro = 0;

float circulo(float x){
    y = sqrt((raio*raio) - (x*x));
    return y;
}

void colorePonto(void){
   
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glEnable(GL_PROGRAM_POINT_SIZE_EXT);
    glPointSize(1);
    glLoadIdentity();   
    glBegin(GL_POINTS); 
    /*
    for(float x = -20000.0; x<=20000.0; x=x+0.1 ){
            y = circulo(x);
            if(inter)        
                glColor3f(1, 1, 1);
            else
                glColor3f(0, 0, 0); 
            glVertex3f(x, y, -1);
            glVertex3f(x, -y, -1);
        
    }
    */
    
    for (float i = 0; i < WINDOW_HEIGHT; i++){
        for (float j = 0; j < WINDOW_WIDTH; j++){
            Vector3 pixelAtual(i, j, WINDOW_POSITION);
            
            for (auto s: spheres){
                Vector3 cameraPixel(pixelAtual.x - camera.x, pixelAtual.y - camera.y, pixelAtual.z - camera.z);
                //bool inter = s.intersection(cameraPixel);
                
                float a = cameraPixel.dot(cameraPixel);
                
                Vector3 cameraSphereCenter(camera.x - s.center.x, camera.y - s.center.y, camera.z - s.center.z);
                float b = 2*(cameraPixel.dot(cameraSphereCenter));
                
                Vector3 cameraC(camera.x, camera.y, camera.z);
                Vector3 centerC(s.center.x, s.center.y, s.center.z);
                float c = cameraC.dot(cameraC) - 2 * cameraC.dot(centerC) + centerC.dot(centerC) - 2 * s.radius;
                float delta = ((b * b) - 4 * a * c);
                
                Vector3 cameraCenter(camera.x - s.center.x, camera.y - s.center.y, camera.z - s.center.z);
                
                if (delta > 0){
                    float stretch = min((-b + sqrt(delta))/(2*a), (-b - sqrt(delta))/(2*a));
                    cameraPixel *= stretch;
                    
                    Vector3 interceptedPoint(camera);
                    interceptedPoint += cameraPixel;
                    
                    Vector3 N(s.center.x - interceptedPoint.x, s.center.y - interceptedPoint.y, s.center.z - interceptedPoint.z);
                    N.normalizarVetor();
                    
                    Vector3 L(interceptedPoint.x - lightOrigin.x, interceptedPoint.y - lightOrigin.y, interceptedPoint.z - lightOrigin.z);
                    L.normalizarVetor();
                    
                    Vector3 k_env(s.material.environment);
                    Vector3 k_dif(s.material.diffuse);
                    Vector3 k_spec(s.material.specular);
                    
                    Vector3 lightRate(lightColor);
                    
                    Vector3 i_dif(lightRate);
                    i_dif.at(k_dif);
                    float f_dif = L.dot(N);
                    i_dif *= f_dif;
                    
                    Vector3 i_spec(lightRate);
                    i_spec.at(k_spec);
                    Vector3 r(N);
                    r *= (2 * L.dot(N));
                    r -= L;
                    
                    Vector3 v(camera.x - interceptedPoint.x, camera.y - interceptedPoint.y, camera.z - interceptedPoint.z);
                    v.normalizarVetor();
                    float f_spec = r.dot(v);
                    i_spec *= f_spec;
                    
                    Vector3 color(iEnv);
                    color.at(k_env);
                    color += i_dif;
                    color += i_spec;
                    
                    glColor3f(color.x, color.y, color.z);
                    break;
                } else {
                    glColor3f(iEnv.x, iEnv.y, iEnv.z);
                }
            }
            
            glVertex3f(i, j, 0);
        }
    }
    
    glEnd();    
    glFlush();
}

void init(void){
    //glClearColor((0%255)/255., (0%255)/255., (0%255)/255., 0.0);
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

// exemplo do professor pra pintar de acordo com o tamanho da tela
void resize(int w, int h)
{
    /*
    int wsize = w, hsize = h;
    if (h >= w)
    {
        hsize = w*H/W;
        glViewport(0, (h-hsize)/2, wsize, hsize);
    }
    else if (h < w)
    {
        wsize = h*W/H;
        glViewport((w-wsize)/2, 0,  wsize, hsize);
    }
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-W/2, W/2, -H/2, H/2, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW); */
    
    
    
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT, -500.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
}

void keyInput(unsigned char key, int x, int y) {
    switch(key) {
        case 27:
            exit(0);
            break;
        default:
            break;
    }
}

int main(int argc, char **argv){
    
    

    glutInit(&argc, argv);
    
    
    /*
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(000, 100);
    glutCreateWindow("Snow Man");
    glutDisplayFunc(colorePonto);
    glutReshapeFunc(resize);
    */
    
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Snow Man");
    glutDisplayFunc(colorePonto);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
   
   
    init();
    glutMainLoop();
     
     /*
    
    // abaixo está a criação de uns vetores e uns testes para os métodos implementados.
    Vector3 vetor1(7, 3, 5);
    Vector3 vetor2(-8, 4, 2);
    Vector3 vetor3(3, 0, -2);
    Vector3 vetor4(1, -2, 2);
    Vector3 vetor5 = vetor3 + vetor4;
    Vector3 vetor6 = vetor2 - vetor1;
    Vector3 vetor7 = vetor3 * 4;
    Vector3 vetor8 = vetor2 / 2;
    Vector3 vetor9(1, 2, -2);
    Vector3 vetor10(3, 0, 1);
    
    cout << "Vetor 1: " << endl;
    vetor1.showVector();
    cout << "\nVetor 2: " << endl;
    vetor2.showVector();
    cout << "\nVetor 3: " << endl;
    vetor3.showVector();
    cout << "\nVetor 4: " << endl;
    vetor4.showVector();
    cout << "\nVetor 5: " << endl;
    vetor5.showVector();
    cout << "\nVetor 6: " << endl;
    vetor6.showVector();
    cout << "\nVetor 7: " << endl;
    vetor7.showVector();
    cout << "\nVetor 8: " << endl;
    vetor8.showVector();
    cout << "\nVetor 9: " << endl;
    vetor9.showVector();
    cout << "\nVetor 10: " << endl;
    vetor10.showVector();
    
    cout << endl << "====================================================================" << endl;
    
    vetor1 *= 2;
    cout << "\nVetor 1 multiplicado por 2: " << endl;
    vetor1.showVector();
    
    cout << endl << "====================================================================" << endl;
    
    vetor2 /= 2;
    cout << "\nVetor 2 dividido por 2: " << endl;
    vetor2.showVector();
    
    cout << endl << "====================================================================" << endl;
    
    cout << "\nNorma do vetor 3: " << vetor3.norma() << endl;
    
    vetor4.normalizarVetor();
    cout << "\nVetor 4 normalizado: " << endl;
    vetor4.showVector();
    
    cout << endl << "====================================================================" << endl;
    
    cout << "\nProduto escalar entre vetor1 e vetor2: " << vetor1.dot(vetor2) << endl;
    
    cout << endl << "====================================================================" << endl;
    
    // há 3 maneiras de se gerar um produto vetorial entre 2 vetores:
    // utilizarei o vetor9 e vetor 10 cujo produto vetorial é (2, -7, -6) para formar o vetor11 e vetor12 que devem ter o mesmo valor.
    // na terceira maneira irei modificar diretamente o vetor9 para ser o produto vetorial dele com o vetor10.
    Vector3 vetor11 = vetor9.cross(vetor10);
    Vector3 vetor12 = vetor9 % vetor10;
    
    cout << "\nVetor 11: " << endl;
    vetor11.showVector();
    cout << "\nVetor 12: " << endl;
    vetor12.showVector();
    
    vetor9 %= vetor10;
    
    cout << "\nVetor 9 que foi modificado para ser o produto vetorial dele com o vetor 10: " << endl;
    vetor9.showVector();
    
    cout << "\nVetor UP: " << endl;
    Vector3::UP.showVector();
    
    cout << "\nVetor DOWN: " << endl;
    Vector3::DOWN.showVector();
    
    if (vetor1 != vetor2){
        cout << "\nVetor 1 é diferente do vetor 2." << endl;
    } else {
        cout << "\nVetor 1 é igual ao vetor 2." << endl;
    }
    
    Vector3 vetor13(3, 0, 1);
    
    if (vetor10 == vetor13){
        cout << "\nVetor 10 é igual ao vetor 13." << endl;
    } else {
        cout << "\nVetor 10 é diferente do vetor 13." << endl;
    }
    
    cout << "\nO angulo entre LEFT e UP é: " << Vector3::LEFT.angle(Vector3::UP) << " graus." << endl;
    
    Vector3 vetor14 = vetor13.reflect(vetor4);
    cout << "\nO vetor 13 refletido em relação a normal do vetor 4 é: " << endl;
    vetor14.showVector();
    
    Vector3 vetor15;
    vetor15.showVector();
    
    */
    
    
    cout << endl;
    
    return 0;
}