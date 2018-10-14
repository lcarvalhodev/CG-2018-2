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

#ifndef _SOURCE_H
#define _SOURCE_H


class Source {

    public: 

    Source();

    virtual Vect getLightPosition() {return Vect (0,0,0);}
    virtual Color getColor(){ return Color (1,1,1,0); }

};

Source::Source() {}

#endif