

#pragma once
#include <memory>
#include <list>
#include "myParticle01.h"
#include "Particle02.h"
#include "myGalaxy.h"

using namespace std;

class ParticleSystem01
{
    
public:
    //Constructor
    ParticleSystem01(glm::vec2, glm::vec2);
    //Deconstructor
    ~ParticleSystem01();
    //Variables
    shared_ptr<glm::vec2> _emitter;
    shared_ptr<glm::vec2> _lastMousePos;
    glm::vec2 mouseVel;
    
    list<shared_ptr<Galaxy>> Galaxys;
    list<shared_ptr<Particle01>> Particles;
    //Methods
    void addParticle();
    
    void run();

private:
    
    
};