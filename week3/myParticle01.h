//
//  myParticle01.hpp
//  myParticleSystem_HW04
//
//  Created by Kim Köhler on 22/02/17.
//
//

#pragma once

#include <memory>


class Particle01
{
    
public:
    //Constructor
    Particle01(glm::vec2);
    
    //Variables
    glm::vec2 Loc;
    glm::vec2 Vel;
    glm::vec2 Acc;
    float lifetime;
    
    //Methods
    void setup();
    
    void update();
    
    void display();
    
    bool isDead();
    
private:
    //Particle01();
    

    
};