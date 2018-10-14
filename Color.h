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