#ifndef PARTICLES2_H_INCLUDED
#define PARTICLES2_H_INCLUDED

#include "ofMain.h"

class Particle2
{
    public:

        Particle2(){};
        Particle2(ofPoint l);

        void draw();
        void update();
        void setColor( int r, int g, int b);

        ofPoint loc, vel, acc;
        ofPoint *hist;
        int counter;

        int r;
        int g;
        int b;
};

#endif // PARTICLES2_H_INCLUDED
