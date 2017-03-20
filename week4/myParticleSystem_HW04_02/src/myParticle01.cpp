
#include "myParticle01.h"
#include "cinder/Perlin.h"
#include "cinder/Rand.h"


using namespace ci;
using namespace ci::app;
using namespace std;

Particle01::Particle01(glm::vec2 startPos, glm::vec2 mMouseVel, float n, float m)
{
    lifetime = Rand::randInt(300.f, 1000.f);
    Loc = startPos;
    _n = make_shared<float>(n);
    _m = make_shared<float>(m);
    _mouseVel = make_shared<glm::vec2>(mMouseVel);
    velOff = Rand::randVec2() * Rand::randFloat( 1.0f, 3.0f );
}

void Particle01::setup()
{
    
}


void Particle01::update()
{

    Vel = glm::vec2(*_n, *_m) + (*_mouseVel*0.25f) + velOff;
    if ((*_mouseVel).y < 0){
    (*_mouseVel).y += 5;
    }

    Acc.x += (mPerlin.fBm(Loc.x)*(sin((getElapsedSeconds()*2*3.14)*10)*25));
    Acc.y += (mPerlin.fBm(Loc.y)*(cos((getElapsedSeconds()*2*3.14)*10)*25));
    Vel.x += Acc.x;
    Vel.y += Acc.y;
    Loc.x += Vel.x;
    Loc.y += Vel.y;
    
    lifetime -= 3.0f;
    Acc *= 0;

    
}

void Particle01::display()
{
    
    float value = ci::length(abs(Loc));
    float red = map(value, 0.0f, 1000.0f, 0.3f, 1.0f);
    float green = map(Loc.x, 0.0f, 1024.0f, 0.0f, 1.0f);
    float blue = map(Loc.y, 0.0f, 1024.0f, 1.0f, 0.0f);
    float life = map(lifetime, 0.0f, 600.0f, 0.0f, 1.0f);
    ci::gl::color(red, green, blue, life);
    gl::vertex(Loc);
    
}

bool Particle01::isDead()
{
    if (lifetime < 0.0) {
        return true;
    } else {
        return false;
    }
}

//IS THERE SERIOUSLY NO MAP FUNCTION IN CINDER/C++??? I HAVE TO CREATE ONE MYSELF???? IS THIS 2017???
float Particle01::map(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}