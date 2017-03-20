
#include <glm/gtc/constants.hpp>
#include "myParticleSystem01.h"
#include "cinder/Rand.h"

ParticleSystem01::ParticleSystem01(glm::vec2 emitter, glm::vec2 lastMousePos)
{
    _emitter = make_shared<glm::vec2>(emitter);
    _lastMousePos = make_shared<glm::vec2>(lastMousePos);
    mouseVel = *_emitter - *_lastMousePos;
    addParticle();
}

ParticleSystem01::~ParticleSystem01()
{
    
}

void ParticleSystem01::addParticle()
{
    for (int i = 0; i < 2000; i+= 100){
        float r = Rand::randFloat();
        if (r < 0.7) {
            shared_ptr<Particle01> newParticle = make_shared<Particle01>(*_emitter, mouseVel, sin(i*2*3.14), cos(i*2*3.14));
            Particles.push_back(newParticle);
        } else {
            
            shared_ptr<Particle02> newParticle = make_shared<Particle02>(*_emitter, mouseVel, sin(i*2*3.14), cos(i*2*3.14));
            Particles.push_back(newParticle);
            

        }
    }
    for (int i = 0; i/360 <= 1; i++){
    shared_ptr<Galaxy> newGalaxy = make_shared<Galaxy>(*_emitter, mouseVel, i);
    Galaxys.push_back(newGalaxy);
        
    }

}

void ParticleSystem01::run()
{
    ci::gl::enableAdditiveBlending();
    ci::gl::begin(GL_POINTS);
        for(list<shared_ptr<Particle01>>::iterator it = Particles.begin(); it != Particles.end(); it++){
        
        (*it)->update();
        (*it)->display();

        if((*it)->isDead() == true){
            it = Particles.erase(it);
        }
        
    }
    ci::gl::end();
    ci::gl::begin(GL_POINTS);
    for(list<shared_ptr<Galaxy>>::iterator it = Galaxys.begin(); it != Galaxys.end(); it++){
        (*it)->applyForce();
        (*it)->update();
        (*it)->display();
        
        
        if((*it)->isDead() == true){
            it = Galaxys.erase(it);
        }
    }
    ci::gl::end();
}