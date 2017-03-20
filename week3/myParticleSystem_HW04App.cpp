#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "myParticle01.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <list>

using namespace ci;
using namespace ci::app;
using namespace std;

class myParticleSystem_HW04App : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
   
    //CREATE LIST OF VECTORS
    list<shared_ptr<Particle01>> Particles;
};

void myParticleSystem_HW04App::setup()
{
    ci::app::setWindowSize(1024.f, 1024.f);
    ci:app::setFrameRate(60.f);
    
    
    //Location, Velocity, Acceleration
    
  //  Particle01.setup(glm::vec2(1024.f/2, 1024.f/2), glm::vec2(rand() % 2 -1, rand() % 2 - 2), glm::vec2(0.001, 0.001));
}

void myParticleSystem_HW04App::mouseDown( MouseEvent event )
{
    //CREATE NEW PARTICLE WHEN MOUSE CLICKED
    shared_ptr<Particle01> newParticle(new Particle01(getMousePos()));
    Particles.push_back(newParticle);
    std::cout << "Mouse Pressed" << endl;
}

void myParticleSystem_HW04App::update()
{
    //Delete first particle when more than 5 particles exist
    if (Particles.size() > 5){
        Particles.pop_front();
    }
    //RUN UPDATE
    for(list<shared_ptr<Particle01>>::iterator it = Particles.begin(); it != Particles.end(); it++){
        
        it->update();
        
    }
}

void myParticleSystem_HW04App::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    //RUN DISPLAY
    for(list<shared_ptr<Particle01>>::iterator it = Particles.begin(); it != Particles.end(); it++){
        it->display();
    }
   
}

CINDER_APP( myParticleSystem_HW04App, RendererGl )

