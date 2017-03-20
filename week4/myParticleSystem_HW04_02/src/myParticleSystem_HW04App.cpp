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
    
   
    list<shared_ptr<ParticleSystem01>> ParticleSystems;
    bool isMouseDown;
    glm::vec2 lastPos;
    int mCurrentFrame;
    ci::Surface8u mSurface;

    int white = 0;
    int run = 0;
    bool go = true;
    float thisX;
    float thisY;
    float _thisX;
    float _thisY;
    glm::vec2 thisPos;
};

void myParticleSystem_HW04App::setup()
{
    ci::app::setWindowSize(1024.f, 1024.f);
    ci:app::setFrameRate(30.f);
    isMouseDown = false;
    mCurrentFrame = 0;
    gl::ScopedBlend(true);
    lastPos = glm::vec2(0, 0);
    
    try{
    mSurface = loadImage(ci::app::loadAsset("4.png"));
    }catch (exception& e) {
        ci::app::console() << e.what() << std::endl;
    }
    

}

void myParticleSystem_HW04App::mouseDown( MouseEvent event )
{
    

    
}

void myParticleSystem_HW04App::mouseUp( MouseEvent event ){
}

void myParticleSystem_HW04App::update()
{
    
    if (ParticleSystems.size() > 6){
        ParticleSystems.pop_front();
    }
}

void myParticleSystem_HW04App::draw()
{

    if (go == true){
    
        Area area( 0, 0, 1024.f, 1024.f );
    ci::Surface::Iter iter = mSurface.getIter(mSurface.getBounds());
    while(iter.line()){
        while(iter.pixel()){
                if (iter.r() != 255){
                white ++;
                thisX = lmap(iter.x(), 0, 4267, 0, 1024);
                _thisX = floor(thisX);
                thisY = lmap(iter.y(), 0, 4267, 0, 1024);
                _thisY = floor(thisY);
                thisPos = glm::vec2(_thisX, _thisY);
                    if(thisPos != lastPos){
                        shared_ptr<ParticleSystem01> newParticleSystem = make_shared<ParticleSystem01>( thisPos, lastPos);
                        ParticleSystems.push_back(newParticleSystem);
                    }
                lastPos = glm::vec2(_thisX, _thisY);
                
            }
        }
    }
        gl::clear( Color(0, 0, 0 ));

    for(list<shared_ptr<ParticleSystem01>>::iterator it = ParticleSystems.begin(); it != ParticleSystems.end(); it++){
        ci::gl::color(0.f, 0.f, 0.f, 0.5f);
        ci::gl::drawSolidRect(Rectf(vec2(0, 0), vec2(1024, 1024)));
        (*it)->run();
        
        
        writeImage( getHomeDirectory() / "cinder" / "saveImage_" / ( toString( run ) + ".png" ), copyWindowSurface() );
        run++;
    }
    }
    go = false;
}

CINDER_APP( myParticleSystem_HW04App, RendererGl )

