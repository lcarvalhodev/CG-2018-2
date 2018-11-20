/*
Graphics Computer 2018.2
Federal University of Ceará

Team: Leandro Almeida de Carvalho (Leader)
      Letícia Fernandes
      Levi Tavares
      Karen Raiany
      Kayron Melo

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

#include <FreeImage.h>


#include "Vect.h"
#include "Ray.h"
#include "Camera.h"
#include "Color.h"
#include "Light.h"
#include "Sphere.h" 
#include "Object.h"
#include "Source.h"
#include "Plane.h" 
#include "Triangle.h"      


using namespace std;

//struct to RGB (colors)
struct RGBType {
    double r;
    double g;
    double b;
};
 FIBITMAP *img;

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
// winning is the closest object from the point of view the ray
int closestObjectIndex(vector<double> object_on_scene){
    int min_index;

    //prevent unnecessary calculation
    
    if (object_on_scene.size() == 0 ) {
        //if there are no intersections (ray does not intersect any object on the scene)
        return -1;
    }
    else if ( object_on_scene.size() == 1 ){
        
        if (object_on_scene.at(0) > 0 ) {
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
        for(int i=0; i< object_on_scene.size(); i++){
            if(max < object_on_scene.at(i)){
                max = object_on_scene.at(i);
            }
        }

        //find the minimum using the max     
        if (max > 0) {
            //only positives
            for (int index = 0; index < object_on_scene.size(); index++){
                
                if (object_on_scene.at(index) >0 && object_on_scene.at(index) <= max ) {
                    max = object_on_scene.at(index);
                    min_index = index;
                }
            }
            return min_index;
        }
        else{
            //all intersections are negative
            return -1;
        }
    }
}

Color getcolorAt(Vect intersection_position, Vect intersecting_ray_direction, vector<Object*> scene_objects, int index_of_closest_object, vector<Source*> light_sources, double accuracy, double ambienteLight){

    Color closest_object_color = scene_objects.at(index_of_closest_object)->getColor();
    Vect closest_object_normal = scene_objects.at(index_of_closest_object)->getNormalAt(intersection_position);

    if(closest_object_color.getColorSpecial() == 2){
        
        int square = (int) floor(intersection_position.getCoordinateX()) + (int)floor(intersection_position.getCoordinateZ());

        if((square%2 == 0)){
            closest_object_color.setColorRed(0);
            closest_object_color.setColorGreen(0);
            closest_object_color.setColorBlue(0);
        }
        else {
            closest_object_color.setColorRed(1);
            closest_object_color.setColorGreen(1);
            closest_object_color.setColorBlue(1);
        }  
    }

    Color final_color = closest_object_color.colorScalar(ambienteLight);

    //Reflections
    if(closest_object_color.getColorSpecial() > 0 && closest_object_color.getColorSpecial() <=1 ){
        // reflect objects with special value
        double dot1 = closest_object_normal.dotProduct(intersecting_ray_direction.negative());
        Vect scalar1 = closest_object_normal.vectMult(dot1);
        Vect add1 = scalar1.vectAdd(intersecting_ray_direction);
        Vect scalar2 = add1.vectMult(2);
        Vect add2 = intersecting_ray_direction.negative().vectAdd(scalar2);
        Vect reflection_direction = add2.normalize();

        Ray reflection_ray (intersection_position,reflection_direction);

        //determine the ray first intersection
        vector<double> reflection_intersections;

        for(int reflection_index = 0; reflection_index < scene_objects.size(); reflection_index ++ ){
            reflection_intersections.push_back(scene_objects.at(reflection_index)->findIntersection(reflection_ray));
        }

        int index_of_closest_object_with_reflections = closestObjectIndex(reflection_intersections);

        if(index_of_closest_object_with_reflections != -1){
            //reflection ray misses eveything
            if(reflection_intersections.at(index_of_closest_object_with_reflections) > accuracy){
                //determine position and direction at the point of intersection
                Vect reflect_intersection_position = intersection_position.vectAdd(reflection_direction.vectMult(reflection_intersections.at(index_of_closest_object_with_reflections)));
                Vect reflect_intersection_ray_direction = reflection_direction;

                Color reflect_intersection_color = getcolorAt(reflect_intersection_position,reflect_intersection_ray_direction,scene_objects,index_of_closest_object_with_reflections, light_sources, accuracy, ambienteLight);
            
                final_color = final_color.colorAdd(reflect_intersection_color.colorScalar(closest_object_color.getColorSpecial()));
            }
        }
    }

    for(int light_index = 0; light_index < light_sources.size(); light_index ++){
        Vect light_direction = light_sources.at(light_index)->getLightPosition().vectAdd(intersection_position.negative()).normalize();

        float cosine_angle = closest_object_normal.dotProduct(light_direction);

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

            //loop foo secondary_intersections
            for(int c=0; c<secondary_intersections.size(); c++){
                if(secondary_intersections.at(c) > accuracy){
                    if(secondary_intersections.at(c) <= distance_to_light_magnitude ){
                        shadowed=true;
                    }
                    break;
                }
            }

            if(shadowed == false){
                final_color = final_color.colorAdd(closest_object_color.colorMult(light_sources.at(light_index)->getLightColor()).colorScalar(cosine_angle));

                if(closest_object_color.getColorSpecial() > 0 && closest_object_color.getColorSpecial() <=1){
                    //special 0-1
                    double dot1 = closest_object_normal.dotProduct(intersecting_ray_direction.negative());
                    Vect scalar1 = closest_object_normal.vectMult(dot1);
                    Vect add1 = scalar1.vectAdd(intersecting_ray_direction);
                    Vect scalar2 = add1.vectMult(2);
                    Vect add2 = intersecting_ray_direction.negative().vectAdd(scalar2);
                    Vect reflection_direction = add2.normalize();

                    double specular = reflection_direction.dotProduct(light_direction);
                    if(specular > 0){
                        specular = pow(specular,10);
                        final_color = final_color.colorAdd(light_sources.at(light_index)->getLightColor().colorScalar(specular*closest_object_color.getColorSpecial()));
                    }
                }

            }
        }
    }
    return final_color.clip();
}

//global variable to index actual pixel
int thisone;
vector<Object*> scene_objects;
//make cube
void makeCube(Vect corner1, Vect corner2, Color color ){

    //corner1
    double c1x = corner1.getCoordinateX();
    double c1y = corner1.getCoordinateY();
    double c1z = corner1.getCoordinateZ();

    //corner2
    double c2x = corner2.getCoordinateX();
    double c2y = corner2.getCoordinateY();
    double c2z = corner2.getCoordinateZ();

    Vect A (c2x, c1y, c1z);
    Vect B (c2x, c1y, c2z);
    Vect C (c1x, c1y, c2z);

    Vect D (c2x, c2y, c1z);
    Vect E (c1x, c2y, c1z);
    Vect F (c1x, c2y, c2z);

    //left side
    scene_objects.push_back(new Triangle(D,A,corner1,color));
    scene_objects.push_back(new Triangle(corner1,E,D,color));

    //far side
    scene_objects.push_back(new Triangle(corner2,B,A,color));
    scene_objects.push_back(new Triangle(A,D,corner2,color));

    //right side
    scene_objects.push_back(new Triangle(F,C,B,color));
    scene_objects.push_back(new Triangle(B,corner2,F,color));

    //front side
    scene_objects.push_back(new Triangle(E,corner1,C,color));
    scene_objects.push_back(new Triangle(C,F,E,color));

    //top
    scene_objects.push_back(new Triangle(D,E,F,color));
    scene_objects.push_back(new Triangle(F,corner2,D,color));

    //bottom
    scene_objects.push_back(new Triangle(corner1,A,B,color));
    scene_objects.push_back(new Triangle(B,C,corner1,color));

}

int main(int argc, char const *argv[])
{
    // testing freeimage
    FreeImage_Initialise();
    // // cout << FreeImage_GetVersion() << endl;
    // cout << "Rendering snowman ... " << endl;

    // FreeImage_Load(FIF_PNG, "aurora.png", );

    //GET BG IMAGE STUFF
	FreeImage_Initialise ();
	FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename("aurora.png");
	img = FreeImage_Load(fif, "aurora.png");
	RGBQUAD color;
	// if(FreeImage_GetPixelColor(img, 128, 128, &color))
    //     std::cout << (float) color.rgbRed << "_" << (float) color.rgbGreen << "_" << (float) color.rgbBlue << "\n";

    //dpi
    int dpi = 80;
    
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

    int aadepth = 1;
    double aatreshold = 0.1;

    // Directions X,Y,Z
    Vect X (1,0,0);
    Vect Y (0,1,0);
    Vect Z (0,0,1);

    //all coordinates from spheres in scene
    Vect O (0,0,0); //body
    Vect O2 (0,1.5,0); // head
    Vect O3 (O.getCoordinateX(),O.getCoordinateY(),O.getCoordinateZ()-0.97);
    Vect O4 (O.getCoordinateX(),O.getCoordinateY() +0.25,O.getCoordinateZ()-0.97);
    Vect O5 (O.getCoordinateX(),O.getCoordinateY() +0.5,O.getCoordinateZ()-0.94);
    Vect O6 (O2.getCoordinateX() + 0.2 ,O2.getCoordinateY()+ 0.05,O.getCoordinateZ()-0.55);
    Vect O7 (O2.getCoordinateX() - 0.2 ,O2.getCoordinateY() + 0.05,O.getCoordinateZ()-0.55);
    Vect O8 (O2.getCoordinateX() ,O2.getCoordinateY() - 0.15 ,O.getCoordinateZ()-0.55);

    //Camera position
    //first parameter aproxximately of camera - second parameter view of height - third parameter is the rotation
    Vect camPos (0,1,-6);
    // Vect camPos (3,1.5,-4);

    //Camera first parameter is right and left, second up and down , third depth
    //not show yet (adjust later)
    Vect cam_look (0,0,0);

    // Vect diff between is the difference between camPos and the coordinates of Vect cam_look
    Vect diff_pos_look(camPos.getCoordinateX() - cam_look.getCoordinateX(), camPos.getCoordinateY() - cam_look.getCoordinateY(), camPos.getCoordinateZ() - cam_look.getCoordinateZ() );

    //Getting the opposite direction
    Vect camDir = diff_pos_look.negative().normalize(); 

    Vect camRight = Y.crossProduct(camDir).normalize();

    Vect camDown = camRight.crossProduct(camDir);

    //Instance of camera
    Camera scene_cam (camPos, camDir, camRight, camDown);

    //Colors lights
    Color white_light (1.0,1.0,1.0,0);
    Color pretty_green(0.5,1.0,0.5,0.3);
    Color maroon (0.5,0.25,0.25,2);
    Color maroon2 (0.5,0.25,0.25,0);
    Color gray(0.5,0.5,0.5,0);
    Color orange (0.94, 0.75, 0.31, 0);
    Color black(0.0,0.0,0.0,0.0);

    //light position firstparameter represents x (right and left), second paramter represents y
    Vect light_position (0,10,-12);
    // Vect light_position (-7,10,-10);

    Light scene_light (light_position, white_light);

    //multiples lights
    vector<Source*> light_sources;
    light_sources.push_back(dynamic_cast<Source*>(&scene_light));

    //Scene objects
    //Sphere instance to test snowman
    //The snowman is made by two white spheres and spheres to eyes and buttons

    Sphere scene_sphere (O ,1,white_light);
    Sphere scene_sphere2 ( O2, 0.6, white_light);
    Sphere scene_sphere3 ( O3, scene_sphere.getSphereRadius()/12, pretty_green);
    Sphere scene_sphere4 ( O4, scene_sphere.getSphereRadius()/12, pretty_green);
    Sphere scene_sphere5 ( O5, scene_sphere.getSphereRadius()/12, pretty_green);
    Sphere scene_sphere6 ( O6, 0.05, maroon2);
    Sphere scene_sphere7 ( O7, 0.05, maroon2);
    Sphere scene_sphere8 ( O8, 0.05, maroon2);

    //Triangles
    Triangle scene_Triangle( Vect (3,0,0), Vect (0,3,0) , Vect (0,0,3), orange);

    //Plane -1 because the plane it has to be located under the sphere with radius 1
    // Plane scene_plane (Y,-1,maroon2);

    //add here all objects on the scene
    
    scene_objects.push_back(dynamic_cast<Object*> (&scene_sphere));
    scene_objects.push_back(dynamic_cast<Object*> (&scene_sphere2));
    scene_objects.push_back(dynamic_cast<Object*> (&scene_sphere3));
    scene_objects.push_back(dynamic_cast<Object*> (&scene_sphere4));
    scene_objects.push_back(dynamic_cast<Object*> (&scene_sphere5));
    scene_objects.push_back(dynamic_cast<Object*> (&scene_sphere6));
    scene_objects.push_back(dynamic_cast<Object*> (&scene_sphere7));
    scene_objects.push_back(dynamic_cast<Object*> (&scene_sphere8));
    scene_objects.push_back(dynamic_cast<Object*> (&scene_Triangle));
    makeCube(Vect(1,1,1), Vect(-1,-1,-1), orange);
    // scene_objects.push_back(dynamic_cast<Object*>(&scene_plane));

    int thisone,aa_index;
    double xamnt, yamnt; 
    double tempRed, tempGreen, tempBlue;

    //for loop to get all pixels in image
    for (int x = 0; x < width; x++){
        for (int y = 0; y < height; y++){
            thisone = y*width +x;

            //start with an blank pixel
            double tempRed[aadepth*aadepth];
            double tempGreen[aadepth*aadepth];
            double tempBlue[aadepth*aadepth];
            
            for(int aax =0; aax < aadepth; aax++){
                for(int aay =0; aay < aadepth; aay++){

                    aa_index = aay*aadepth + aax;
                    srand(time(0));

                    //create the ray from the camera to this pixel
                    if(aadepth == 1){
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
                    }

                    else{
                        //anti-aliasing
                        if (width > height) {
                            // the image is wider than tall
                            xamnt = ((x+(double)aax / ((double)aadepth - 1))/width) * aspectRatio - (((width-height)/ (double) height)/2);
                            yamnt = ((height - y ) + (double)aax / ((double)aadepth - 1))/ height;
                        }

                        else if (height > width){
                            //image is taller than wider
                            xamnt = (x+(double)aax / ((double)aadepth - 1))/width;
                            yamnt= (((height - y) +(double)aax / ((double)aadepth - 1))/height)/aspectRatio - (((height-width)/(double) width)/2);
                        }
                        else {
                            //the image is square
                            xamnt= (x+(double)aax / ((double)aadepth - 1))/ width;
                            yamnt = ((height-y) + (double)aax / ((double)aadepth - 1))/height;
                        }
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
                    int index_of_closest_object = closestObjectIndex(intersections);            
           
                    //return a color
                    //if index is negative, ray misses, and then it will be black
                    if (index_of_closest_object == -1) {
                        //set the background
                        if(FreeImage_GetPixelColor(img, x, y, &color)){
                            tempRed[aa_index] = (float) (color.rgbRed)/255;
                            tempGreen[aa_index] = (float) (color.rgbGreen)/255;
                            tempBlue[aa_index] = (float) (color.rgbBlue)/255; 
                        }
                            // std::cout << (float) color.rgbRed << "_" << (float) color.rgbGreen << "_" << (float) color.rgbBlue << "\n";
                        // cout <<  (float) color.rgbRed/100 << endl;
                       
                    } 
                    else{
                        //intersect an object
                        //making a shadow

                        if(intersections.at(index_of_closest_object) > accuracy){
                            //determine position and direction vector at the point of intersection

                            Vect intersection_position = cam_ray_origin.vectAdd(cam_ray_direction.vectMult(intersections.at(index_of_closest_object)));
                            Vect intersecting_ray_direction = cam_ray_direction;

                            Color intersection_color = getcolorAt(intersection_position, intersecting_ray_direction, scene_objects,index_of_closest_object, light_sources,accuracy, ambienteLight);
                            
                            tempRed[aa_index] = intersection_color.getColorRed();
                            tempGreen[aa_index] = intersection_color.getColorGreen();
                            tempBlue[aa_index] = intersection_color.getColorBlue();
                        }
                    }
                }      
            }

            //average the pixel color
            double totalRed = 0;
            double totalGreen = 0;
            double totalBlue = 0;

            for(int iRed=0; iRed< aadepth*aadepth; iRed++){
                totalRed=totalRed+tempRed[iRed];
            }
            for(int iGreen=0; iGreen< aadepth*aadepth; iGreen++){
                totalGreen=totalGreen+tempGreen[iGreen];
            }
            for(int iBlue=0; iBlue< aadepth*aadepth; iBlue++){
                totalBlue=totalBlue+tempBlue[iBlue];
            }

            double avgRed = totalRed / (aadepth*aadepth);
            double avgGreen = totalGreen / (aadepth*aadepth);
            double avgBlue = totalBlue / (aadepth*aadepth);

            pixels[thisone].r = avgRed;
            pixels[thisone].g = avgGreen;
            pixels[thisone].b = avgBlue;
        }
    }

    saveBMP("scene_snowman.bmp", width,height,dpi,pixels);

    delete pixels,tempRed, tempGreen, tempBlue;

    FreeImage_DeInitialise();

    return 0;
}
