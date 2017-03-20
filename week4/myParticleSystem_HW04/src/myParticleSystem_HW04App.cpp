#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Perlin.h"
#include "cinder/ImageIo.h"
#include "cinder/Utilities.h"
#include "cinder/gl/scoped.h"

#include "myParticle01.h"
#include "myParticleSystem01.h"
#include "myGalaxy.h"
#include "Particle02.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <list>
#include <memory>

using namespace ci;
using namespace ci::app;
using namespace std;

class myParticleSystem_HW04App : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
    void mouseUp( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
   
    //CREATE LIST OF VECTORS
    list<shared_ptr<ParticleSystem01>> ParticleSystems;
    
    bool isMouseDown;
    glm::vec2 lastMousePos;
    int mCurrentFrame;
};

void myParticleSystem_HW04App::setup()
{
    ci::app::setWindowSize(1024.f, 1024.f);
    ci:app::setFrameRate(60.f);
    isMouseDown = false;
    mCurrentFrame = 0;
    gl::ScopedBlend(true);
    gl::clear( Color(0, 0, 0 ));
    
}

void myParticleSystem_HW04App::mouseDown( MouseEvent event )
{
    
    isMouseDown = true;

    
}

void myParticleSystem_HW04App::mouseUp( MouseEvent event ){
    isMouseDown = false;
}

void myParticleSystem_HW04App::update()
{
    
    if (isMouseDown == true){
        //CREATE NEW PARTICLESYSTEM WHEN MOUSE CLICKED
        //This is better than:
        // shared_ptr<Particle01> newParticle(new Particle01(getMousePos()));
        //Less operations(faster) and no risk of creating an object without a pointer, if the pointer would fail because of memory leak etc(safer)
        shared_ptr<ParticleSystem01> newParticleSystem = make_shared<ParticleSystem01>( getMousePos(), lastMousePos);
        ParticleSystems.push_back(newParticleSystem);
    }
    //Delete first system when more than X systems exist
    if (ParticleSystems.size() > 6){
        ParticleSystems.pop_front();
    }
    lastMousePos = getMousePos();
}

void myParticleSystem_HW04App::draw()
{
    //Draw rect with opacity to give motion blur
    ci::gl::color(0.f, 0.f, 0.f, 0.3f);
    ci::gl::drawSolidRect(Rectf(vec2(0, 0), vec2(1024, 1024)));
    //RUN
    for(list<shared_ptr<ParticleSystem01>>::iterator it = ParticleSystems.begin(); it != ParticleSystems.end(); it++){
        
        (*it)->run();
        
    }
}

CINDER_APP( myParticleSystem_HW04App, RendererGl )

