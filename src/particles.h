#ifndef PARTICLES_H_INCLUDED
#define PARTICLES_H_INCLUDED

#include "ofMain.h"

class Particle
{
    public:

        Particle(){};
        Particle(ofPoint l);

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

#endif // PARTICLES_H_INCLUDED
