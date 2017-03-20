
#include "cinder/Rand.h"
#include "myGalaxy.h"

using namespace ci;
using namespace ci::app;
using namespace std;

Galaxy::Galaxy(glm::vec2 _emitter, ci::vec2 _mouseVel, int _i)
{
    lifetime = 270.f;
    time = app::getElapsedFrames();
    mI = make_shared<int>(_i);
    Force = 0;
    Acc = glm::vec2(0, 0);
    Vel = glm::vec2(0, 0);
    mEmitter = make_shared<glm::vec2>(_emitter);
    Loc = *mEmitter;
    mMouseVel = make_shared<ci::vec2>(_mouseVel);
    r = glm::length(*mMouseVel);
    dir = ci::vec2(0, 0);
    normDir = ci::vec2(0, 0);
    offset = 0;
    
}

void Galaxy::update()
{
    angle = glm::radians(*mI * time);
    Vel += Acc;
    Loc += Vel;
    lifetime -= 4.f;
    offset += 0.1;
}

void Galaxy::display()
{
    float value = ci::length(abs(Loc));
    float red = map(value, 0.0f, 1000.0f, 0.3f, 1.0f);
    float green = map(Loc.x, 0.0f, 1024.0f, 0.0f, 1.0f);
    float blue = map(Loc.y, 0.0f, 1024.0f, 1.0f, 0.0f);
    float life = map(lifetime, 0.0f, 400.0f, 0.0f, 1.0f);

    ci::gl::color(red, green, blue, life);
    gl::vertex(Loc.x, Loc.y);
    
    Acc *= 0;
   
    
}

void Galaxy::applyForce()
{
    dir = glm::vec2(cos((angle)+offset), sin((angle)+offset))/r;
    Force = length(dir);
    if (Force > 0.0f){
        normDir = glm::normalize(dir);
        
    }
    
    Acc += normDir/Force;
    Acc *= 0.005;
    
    
    
}

bool Galaxy::isDead()
{
    if (lifetime < 0.0) {
        return true;
    } else {
        return false;
    }
}

float Galaxy::map(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}