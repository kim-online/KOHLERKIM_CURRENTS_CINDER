#include "Particle02.h"


Particle02::Particle02( glm::vec2 startPos, glm::vec2 mMouseVel, float n, float m) : Particle01( startPos, mMouseVel, n, m ) {
    
}

void Particle02::update()
{

    //get the velocity of mouse to give particles a push
    Vel = glm::vec2(*_n, *_m) + (*_mouseVel*0.25f) + velOff;
    //decrease the push until its almost 0
    if ((*_mouseVel).y < 0){
        (*_mouseVel).y += 1;
    }
    
    Acc.x += sin((getElapsedSeconds()*2*3.14)*10)*25;
    Acc.y += cos((getElapsedSeconds()*2*3.14)*10)*25;
    Vel.x += Acc.x;
    Vel.y += Acc.y;
    Loc.x += Vel.x;
    Loc.y += Vel.y;
    
    lifetime -= 3.0f;
    
    Acc *= 0;
}

void Particle02::display()
{
    //Color of particle depends on position distance
    //opacity depends on lifetime
    float value = ci::length(abs(Loc));
    float red = map(value, 0.0f, 1000.0f, 0.3f, 1.0f);
    float green = map(Loc.x, 0.0f, 1024.0f, 0.0f, 1.0f);
    float blue = map(Loc.y, 0.0f, 1024.0f, 1.0f, 0.0f);
    float life = map(lifetime, 0.0f, 600.0f, 0.0f, 1.0f);
    ci::gl::color(red, green, blue, life);
    // draw particle
    gl::vertex(Loc);
}