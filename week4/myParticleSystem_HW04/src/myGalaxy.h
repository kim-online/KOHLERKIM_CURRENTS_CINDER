#pragma once
#include <stdio.h>
#include <memory>

using namespace ci;
using namespace ci::app;
using namespace std;

class Galaxy
{
public:
    //Constructor
    Galaxy(glm::vec2, ci::vec2, int _i);
    //variables
    glm::vec2 Acc;
    glm::vec2 Vel;
    glm::vec2 Loc;
    float Force;
    ci::vec2 dir;
    ci::vec2 normDir;
    
    shared_ptr<ci::vec2> mMouseVel;
    shared_ptr<glm::vec2> mEmitter;
    shared_ptr<int> mI;
    float r;
    float time;
    float angle;
    float lifetime;
    float offset;
    //methods
    void update();
    void display();
    void applyForce();
    bool isDead();
    float map(float x, float in_min, float in_max, float out_min, float out_max);
    
};