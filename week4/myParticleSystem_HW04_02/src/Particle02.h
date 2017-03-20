#pragma once

#include <stdio.h>
#include "myParticle01.h"


class Particle02 : public Particle01{
public:
    Particle02(glm::vec2, glm::vec2, float n, float m);
    

    
    virtual void update();
    virtual void display();
};