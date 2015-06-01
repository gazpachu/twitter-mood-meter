#include "particles.h"

Particle::Particle(ofPoint l)
{
    counter = 0;
    float randmin = -HALF_PI;
    float randmax = 0;

    float r = ofRandom(0, TWO_PI);
    float x = cos(r);
    float y = sin(r);
    acc = ofPoint(x / 100, y / 100);

    float q = ofRandom(0, 1);
    r = ofRandom(randmin, randmax);
    x = cos(r) * q;
    y = sin(r) * q;
    vel = ofPoint(x, y);
    loc = l;
    hist = new ofPoint[1000];
}

void Particle::update()
{
    vel += acc;
    loc += vel;

    if(ofGetFrameNum() % 10 == 0 && counter < 1000){
        hist[counter].x = loc.x;
        hist[counter].y = loc.y;
        counter++;
    }
}

void Particle::draw()
{
    ofNoFill();
    ofSetColor(r, g, b);

    ofBeginShape();
    for(int i = 0; i < counter; i++)
    {
        ofVertex(hist[i].x, hist[i].y);
    }
    if(counter > 0) ofVertex(loc.x, loc.y);
    ofEndShape(false);
}

void Particle::setColor( int _r, int _g, int _b)
{
    r=_r;
    g=_g;
    b=_b;
}
