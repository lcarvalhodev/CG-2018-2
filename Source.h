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

#ifndef _SOURCE_H
#define _SOURCE_H


class Source {

    public: 

    Source();

    //Getters
    virtual Vect getLightPosition() {
        return Vect (0,0,0);
    }

    virtual Color getLightColor(){ 
        return Color (1,1,1,0); 
    }

};

Source::Source() {}

#endif