
#pragma once

#include <memory>
#include "cinder/Perlin.h"




using namespace ci;
using namespace ci::app;
using namespace std;


class Particle01
{
    
public:
    //Constructor
    Particle01(glm::vec2, glm::vec2, float n, float m);
    
    //Variables
    glm::vec2 Loc;
    glm::vec2 Vel;
    glm::vec2 Acc;
    glm::vec2 velOff;
    float lifetime;
    shared_ptr<glm::vec2> _mouseVel;
    shared_ptr<float> _m;
    shared_ptr<float> _n;
    Perlin mPerlin = Perlin();
    //Methods
    void setup();
    
    virtual void update();
    
    virtual void display();
    
    bool isDead();
    
    float map(float x, float in_min, float in_max, float out_min, float out_max);
    
private:
  
    

    
};