/*
Graphics Computer 2018.2
Federal University of Ceará

Team: Leandro Almeida de Carvalho (Leader)
      Letícia Fernandes
      Levi 
      Karen
      Kayron

Professor: Creto Vidal
Work: Build a RayTracer to render a snowman with a image background.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Vect.h"
#include "Ray.h"
#include "Camera.h"
#include "Color.h"
#include "Light.h"
#include "Sphere.h" 
#include "Object.h"
#include "Source.h"
#include "Plane.h"       


using namespace std;

//struct to RGB (colors)
struct RGBType {
    double r;
    double g;
    double b;
};

//function to save image
void saveBMP (const char *filename, int w, int h, int dpi, RGBType *data) {
    FILE *f;
    int k = w*h;
    int s = 4*k;
    int filesize = 54 + s;

    double factor = 39.375;
    int m = static_cast<int>(factor);

    int ppm = dpi*m;  

    unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0,0,0, 54,0,0,0};
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0};

    bmpfileheader[ 2] = (unsigned char)(filesize);
    bmpfileheader[ 3] = (unsigned char)(filesize>>8);
    bmpfileheader[ 4] = (unsigned char)(filesize>>16);
    bmpfileheader[ 5] = (unsigned char)(filesize>>24);

    bmpinfoheader[ 4] = (unsigned char)(w);
    bmpinfoheader[ 5] = (unsigned char)(w>>8);
    bmpinfoheader[ 6] = (unsigned char)(w>>16);
    bmpinfoheader[ 7] = (unsigned char)(w>>24);

    bmpinfoheader[ 8] = (unsigned char)(h);
    bmpinfoheader[ 9] = (unsigned char)(h>>8);
    bmpinfoheader[10] = (unsigned char)(h>>16);
    bmpinfoheader[11] = (unsigned char)(h>>24);

    bmpinfoheader[21] = (unsigned char)(s);
    bmpinfoheader[22] = (unsigned char)(s>>8);
    bmpinfoheader[23] = (unsigned char)(s>>16);
    bmpinfoheader[24] = (unsigned char)(s>>24);

    bmpinfoheader[25] = (unsigned char)(ppm);
    bmpinfoheader[26] = (unsigned char)(ppm>>8);
    bmpinfoheader[27] = (unsigned char)(ppm>>16);
    bmpinfoheader[28] = (unsigned char)(ppm>>24);

    bmpinfoheader[29] = (unsigned char)(ppm);
    bmpinfoheader[30] = (unsigned char)(ppm>>8);
    bmpinfoheader[31] = (unsigned char)(ppm>>16);
    bmpinfoheader[32] = (unsigned char)(ppm>>24);

    f = fopen(filename,"wb");

    fwrite(bmpfileheader,1,14,f);
    fwrite(bmpinfoheader,1,40,f);

    
    for(int i = 0; i < k; i++){
        
        //rgb colors
        RGBType rgb = data[i];
        double red = (data[i].r)*255;
        double green = (data[i].g)*255;
        double blue = (data[i].b)*255;

        unsigned char color[3] = {(int)floor(blue),(int)floor(green),(int)floor(red)};

        fwrite(color,1,3,f);
    }

    //close file
    fclose(f);
}

//function to sort all intersection vect and return the index of winning object ( closer to the camera)
int winningObjectIndex(vector<double> object_intersections){
    int index_of_minimum_value;

    //prevent unnecessary calculation
    
    if (object_intersections.size() == 0 ) {
        //if there are no intersections
        return -1;
    }
    else if ( object_intersections.size() == 1 ){
        
        if (object_intersections.at(0) > 0 ) {
            //if that intersection is greater than zero then its our index of minimum value
            return 0;
        }
        else {
            //otherwise the only intersection value is negative
            return -1;
        }
        
    }
    else{
        //otherwise there is more than one intersection 
        // first find tha maximum value

        double max = 0;
        for(int i=0; i< object_intersections.size(); i++){
            if(max < object_intersections.at(i)){
                max = object_intersections.at(i);
            }
        }

        //find the minimum using the max
        
        if (max > 0) {
            //only positives
            for (int index = 0; index < object_intersections.size(); index++){
                
                if (object_intersections.at(index) >0 && object_intersections.at(index) <= max ) {
                    max = object_intersections.at(index);
                    index_of_minimum_value = index;
                }
            }
            return index_of_minimum_value;
        }
        else{
            //all intersections are negative
            return -1;
        }
    }
}

Color getcolorAt(Vect intersection_position, Vect intersecting_ray_direction, vector<Object*> scene_objects, int index_of_winning_object, vector<Source*> light_sources, double accuracy, double ambienteLight){

    Color winning_object_color = scene_objects.at(index_of_winning_object)->getColor();
    Vect winning_object_normal = scene_objects.at(index_of_winning_object)->getNormalAt(intersection_position);

    Color final_color = winning_object_color.colorScalar(ambienteLight);

    for(int light_index = 0; light_index < light_sources.size(); light_index ++){
        Vect light_direction = light_sources.at(light_index)->getLightPosition().vectAdd(intersection_position.negative()).normalize();

        float cosine_angle = winning_object_normal.dotProduct(light_direction);

        if (cosine_angle > 0 ){
            //test for shadows
            bool shadowed = false;

            Vect distance_to_light = light_sources.at(light_index)->getLightPosition().vectAdd(intersection_position.negative()).normalize();

            float distance_to_light_magnitude = distance_to_light.magnitude();

            //verify if ray of light intersects with another ray to create a shadow
            Ray shadow_ray (intersection_position, light_sources.at(light_index)->getLightPosition().vectAdd(intersection_position.negative()).normalize());

            //vector of intersection values
            vector<double> secondary_intersections;

            //loop to find this intersections
            for(int object_index= 0; object_index < scene_objects.size() && shadowed == false ; object_index++){
                secondary_intersections.push_back(scene_objects.at(object_index)->findIntersection(shadow_ray));
            }

            //loop fro secondary_intersections
            for(int c=0; c<secondary_intersections.size(); c++){
                if(secondary_intersections.at(c) > accuracy){
                    if(secondary_intersections.at(c) <= distance_to_light_magnitude ){
                        shadowed=true;
                    }
                    break;
                }
            }

            if(shadowed == false){
                final_color = final_color.colorAdd(winning_object_color.colorMult(light_sources.at(light_index)->getLightColor()).colorScalar(cosine_angle));

                if(winning_object_color.getColorSpecial() > 0 && winning_object_color.getColorSpecial() <=1){
                    //special 0-1
                    double dot1 = winning_object_normal.dotProduct(intersecting_ray_direction.negative());
                    Vect scalar1 = winning_object_normal.vectMult(dot1);
                    Vect add1 = scalar1.vectAdd(intersecting_ray_direction);
                    Vect scalar2 = add1.vectMult(2);
                    Vect add2 = intersecting_ray_direction.negative().vectAdd(scalar2);
                    Vect reflection_direction = add2.normalize();

                    double specular = reflection_direction.dotProduct(light_direction);
                    if(specular > 0){
                        specular = pow(specular,10);
                        final_color = final_color.colorAdd(light_sources.at(light_index)->getLightColor().colorScalar(specular*winning_object_color.getColorSpecial()));
                    }


                }

            }
        }
    }
    return final_color.clip();
}

//global variable to index actual pixel
int thisone;

int main(int argc, char const *argv[])
{
    cout << "Rendering ... " << endl;

    //dpi
    int dpi = 72;
    
    //dimens for image
    int width = 640;
    int height= 480;

    //aspect ratio
    double aspectRatio = (double)width/(double)height;

    //values for light
    double ambienteLight = 0.2;
    double accuracy = 0.000001;

    //total of pixels
    int n = width * height;

    //RGBType
    RGBType *pixels = new RGBType[n];

    // Directions X,Y,Z
    Vect X (1,0,0);
    Vect Y (0,1,0);
    Vect Z (0,0,1);

    //all coordinates from spheres in scene
    Vect O (0,0,0);
    Vect O2 (0,1.5,0);
    Vect O3 (O.getVectX(),O.getVectY(),O.getVectZ()-0.97);
    Vect O4 (O.getVectX(),O.getVectY() +0.25,O.getVectZ()-0.97);
    Vect O5 (O.getVectX(),O.getVectY() +0.5,O.getVectZ()-0.94);
    Vect O6 (O2.getVectX() + 0.2 ,O2.getVectY()+ 0.05,O.getVectZ()-0.55);
    Vect O7 (O2.getVectX() - 0.2 ,O2.getVectY() + 0.05,O.getVectZ()-0.55);
    Vect O8 (O2.getVectX() ,O2.getVectY() - 0.15 ,O.getVectZ()-0.55);

    //Camera position
    //first parameter aproxximately of camera - second parameter view of height - third parameter is the rotation
    Vect camPos (0,1,-6);

    //Camera
    Vect look_at (0,0,0);

    // Vect diff between is the difference between camPos and the coordinates of Vect look_at
    Vect diff_btw(camPos.getVectX() - look_at.getVectX(), camPos.getVectY() - look_at.getVectY(), camPos.getVectZ() - look_at.getVectZ() );

    //Getting the opposite direction
    Vect camDir = diff_btw.negative().normalize(); 

    Vect camRight = Y.crossProduct(camDir).normalize();

    Vect camDown = camRight.crossProduct(camDir);

    //Instance of camera
    Camera scene_cam (camPos, camDir, camRight, camDown);

    //Colors lights
    Color white_light (1.0,1.0,1.0,0);
    Color pretty_green(0.5,1.0,0.5,0.3);
    Color maroon (0.5,0.25,0.25,0);
    Color gray(0.5,0.5,0.5,0);
    Color black(0.0,0.0,0.0,0.0);

    //light position firstparameter represents x (right and left), second paramter represents y
    Vect light_position (0,10,-12);
    Light scene_light (light_position, white_light);

    //multiples lights
    vector<Source*> light_sources;
    light_sources.push_back(dynamic_cast<Source*>(&scene_light));

    //Scene objects

    //Sphere instance to test snowman
    //The snowman is made by two white spheres

    Sphere scene_sphere (O ,1,white_light);
    Sphere scene_sphere2 ( O2, 0.6, white_light);
    Sphere scene_sphere3 ( O3, scene_sphere.getSphereRadius()/12, pretty_green);
    Sphere scene_sphere4 ( O4, scene_sphere.getSphereRadius()/12, pretty_green);
    Sphere scene_sphere5 ( O5, scene_sphere.getSphereRadius()/12, pretty_green);
    Sphere scene_sphere6 ( O6, 0.05, maroon);
    Sphere scene_sphere7 ( O7, 0.05, maroon);
    Sphere scene_sphere8 ( O8, 0.05, maroon);

    //Plane -1 because the plane it has to be located ubder the sphere with radius 1
    Plane scene_plane (Y,-1,gray);

    //add here all objects on the scene
    vector<Object*> scene_objects;
    scene_objects.push_back(dynamic_cast<Object*> (&scene_sphere));
    scene_objects.push_back(dynamic_cast<Object*> (&scene_sphere2));
    scene_objects.push_back(dynamic_cast<Object*> (&scene_sphere3));
    scene_objects.push_back(dynamic_cast<Object*> (&scene_sphere4));
    scene_objects.push_back(dynamic_cast<Object*> (&scene_sphere5));
    scene_objects.push_back(dynamic_cast<Object*> (&scene_sphere6));
    scene_objects.push_back(dynamic_cast<Object*> (&scene_sphere7));
    scene_objects.push_back(dynamic_cast<Object*> (&scene_sphere8));
    scene_objects.push_back(dynamic_cast<Object*>(&scene_plane));

    double xamnt, yamnt; 

    //for loop to get all pixels in image
    for (int x = 0; x < width; x++){
        for (int y = 0; y < height; y++){
            thisone = y*width +x;

            
            if (width > height) {
                // the image is wider than tall
                xamnt = ((x+0.5)/width) * aspectRatio - (((width-height)/ (double) height)/2);
                yamnt = ((height - y ) + 0.5)/ height;
            }

            else if (height > width){
                //image is taller than wider
                xamnt = (x+0.5)/width;
                yamnt= (((height - y) +0.5)/height)/aspectRatio - (((height-width)/(double) width)/2);
            }
            else {
                //the image is square
                xamnt= (x+0.5)/ width;
                yamnt = ((height-y) + 0.5)/height;
            }

            //creatin rays from origin
            Vect cam_ray_origin = scene_cam.getCameraPosition();
            Vect cam_ray_direction = camDir.vectAdd(camRight.vectMult(xamnt-0.5).vectAdd(camDown.vectMult(yamnt-0.5))).normalize();

            Ray cam_ray (cam_ray_origin,cam_ray_direction);

            //sending rays to the scene to look for intersections
            vector<double> intersections;

            //verify if each object on ths scene is intersect by rays
            for (int index = 0; index < scene_objects.size(); index++){
                intersections.push_back(scene_objects.at(index) ->findIntersection(cam_ray));
            }

            //verify wich object is closer to the camera
            int index_of_winning_object = winningObjectIndex(intersections);            

            // cout << index_of_winning_object;            
            //return a color
            //if index is negative, ray misses, and then it will be black
            if (index_of_winning_object == -1) {
                //set the background
                pixels[thisone].r = 0;
                pixels[thisone].g = 0;
                pixels[thisone].b = 0;
            } 
            else{
                //intersect an object

                //making a shadow

                if(intersections.at(index_of_winning_object) > accuracy){
                    //determine position and direction vector at the point of intersection

                    Vect intersection_position = cam_ray_origin.vectAdd(cam_ray_direction.vectMult(intersections.at(index_of_winning_object)));
                    Vect intersecting_ray_direction = cam_ray_direction;

                    Color intersection_color = getcolorAt(intersection_position, intersecting_ray_direction, scene_objects,index_of_winning_object, light_sources,accuracy, ambienteLight);
                    
                    pixels[thisone].r = intersection_color.getColorRed();
                    pixels[thisone].g = intersection_color.getColorGreen();
                    pixels[thisone].b = intersection_color.getColorBlue();
                }
            }
        }      
    }

    saveBMP("scene.bmp", width,height,dpi,pixels);

    return 0;
}
