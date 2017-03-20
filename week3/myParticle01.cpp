//
//  myParticle01.cpp
//  myParticleSystem_HW04
//
//  Created by Kim Köhler on 22/02/17.
//
//

#include "myParticle01.h"


Particle01::Particle01(glm::vec2 startPos)
{
    lifetime = 255.f;
    Loc = startPos;
    Acc = glm::vec2(0.f, 0.5f);
    Vel =  glm::vec2(rand() % 2 -1, rand() % 2 - 2);
    
}

void Particle01::setup()
{
    
}


void Particle01::update()
{
    
    Vel += Acc;
    Loc += Vel;
    lifetime -= 1.0f;
   
    
}

void Particle01::display()
{
    
    float value = ci::length(abs(Vel)) * 100.f;
    glm::clamp(value, 0.f, 1.f);
    glm::clamp(lifetime, 0.f, 1.f);
    ci::gl::color(value, value, value, lifetime);
    // draw cricle
    ci::gl::drawSolidCircle(Loc, 2.f);
    
}

bool Particle01::isDead()
{
    
    if (lifetime < 0.0) {
        return true;
    } else {
        return false;
    }
}