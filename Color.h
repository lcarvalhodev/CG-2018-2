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

#ifndef _COLOR_H
#define _COLOR_H

class Color {
    double red,green,blue, special;

    public:

    //general constructor
    Color ();

    //another instance
    Color (double,double,double,double);

    //method functions

    //Gets
    double getColorRed() {return red; }
    double getColorGreen() {return green; }
    double getColorBlue() {return blue; }
    double getColorSpecial() {return special; }

    // Setters functions
    double setColorRed(double redValue) {red = redValue; }
    double setColorGreen(double greenValue) {green = greenValue; }
    double serColorBlue(double blueValue) {blue = blueValue; }
    double setColorSpecial(double specialValue) {special = specialValue; }

    //bright (to set shadow)
    double brightness(){
        return (red+ green + blue)/3;
    }

    Color colorScalar(double scalar) {
        return Color (red*scalar, green*scalar, blue*scalar,special);
    }

    Color colorAdd(Color color){
        return Color (red+ color.getColorRed(), green + color.getColorGreen(), blue + color.getColorBlue(), special);
    }

    Color colorMult(Color color) {
        return Color (red*color.getColorRed(), green*color.getColorGreen(), blue*color.getColorBlue(), special);
    }

    Color colorAverage(Color color){
        return Color ((red + color.getColorRed())/2, (green+color.getColorGreen())/2, (blue+ color.getColorBlue())/2, special);
    }

    //function to make color of the light / shadow correct
    Color clip(){
        double all_light = red + green + blue;
        double excessLight = all_light - 3;
        if(excessLight > 0){
            red = red + excessLight*(red/all_light);
            green = green + excessLight*(green/all_light);
            blue = blue + excessLight*(blue/all_light);
        }

        //normalize colo in cases of exceed
        if( red > 1 ){ red = 1;}
        if( green > 1 ){ green = 1;}
        if( blue > 1 ){ blue = 1;}
        if( red < 0 ){ red = 0;}
        if( green < 0 ){ green = 0;}
        if( blue < 0 ){ blue = 0;}

        return Color (red,green,blue,special);
    }
};


//default color
Color::Color () {
    red=0.5;
    green=0.5;
    blue=0.5;
}

//color specified
Color::Color (double r, double g, double b, double s) {
    red=r;
    green=g;
    blue=b;
    special=s;
}

#endif