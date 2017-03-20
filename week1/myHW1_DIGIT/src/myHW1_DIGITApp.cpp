#include "cinder/app/App.h"
#include "cinder/app/MouseEvent.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;
int speed = 0;
bool press = false;

class myHW1_DIGITApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void myHW1_DIGITApp::setup()
{
    ci::app::setWindowSize(800, 400);
}

void myHW1_DIGITApp::mouseDown( MouseEvent event )
{
    //didnt get this to work
   // std::cout<<cinder::app::MouseEvent::isLeft();
        
    
}

void myHW1_DIGITApp::update()
{
    //this is for the acceleration stick, but as i didnt get mouse to work, this is useless
    if (press == true && speed <=4){
        speed ++;
        
    } else if(press == true && speed > 4) {
        speed = 4;
        
    } else if(press == false && speed <= 0){
        speed = 0;
    } else {
        speed --;
    }
    
}

void myHW1_DIGITApp::draw()
{
    gl::clear( ci::Color( 0, 0, 0 ) );
    ci::vec2 center = 0.5f * ci::vec2(ci::app::getWindowSize());
    
    for (int i = 0; i < 5; i++) {
        //acceleration marks
        gl::pushModelView();
        gl::translate(center);
        gl::rotate(i * glm::radians(45.f));
        gl::color(Color::white());
        gl::drawSolidRect(Rectf(-110, -3, -90, 3));
        //digit
        switch(i){
            case 0 : gl::pushModelView();
                gl::translate(ci::vec2(-110, -3));
                gl::drawSolidRect(Rectf(-30, -20, -25, -15));
                gl::translate(ci::vec2(-25, -20));
                gl::drawSolidTriangle(ci::vec2(0, 0), ci::vec2(5, 5), ci::vec2(0, 5));
                gl::translate(ci::vec2(-5, 0));
                gl::drawSolidTriangle(ci::vec2(0, 0), ci::vec2(-5, 5), ci::vec2(0, 5));
                gl::translate(ci::vec2(-2, -2));
                gl::drawSolidTriangle(ci::vec2(0, 0), ci::vec2(-5, 5), ci::vec2(-5, 0));
                gl::drawSolidRect(Rectf(0, 0, -5, -5));
                gl::translate(ci::vec2(0, -7));
                gl::drawSolidRect(Rectf(0, 0, -5, -5));
                gl::translate(ci::vec2(0, -5));
                gl::drawSolidTriangle(ci::vec2(0, 0), ci::vec2(-5, -5), ci::vec2(-5, 0));
                gl::translate(ci::vec2(2, -2));
                gl::drawSolidTriangle(ci::vec2(0, 0), ci::vec2(0, -5), ci::vec2(-5, -5));
                gl::drawSolidRect(Rectf(0, 0, 5, -5));
                gl::translate(ci::vec2(5, 0));
                gl::drawSolidTriangle(ci::vec2(0, 0), ci::vec2(0, -5), ci::vec2(5, -5));
                gl::translate(ci::vec2(2, 2));
                gl::drawSolidTriangle(ci::vec2(0, 0), ci::vec2(5, 0), ci::vec2(5, -5));
                gl::drawSolidRect(Rectf(0, 0, 5, 5));
                gl::translate(ci::vec2(0, 7));
                gl::drawSolidRect(Rectf(0, 0, 5, 5));
                gl::translate(ci::vec2(0, 5));
                gl::drawSolidTriangle(ci::vec2(0, 0), ci::vec2(5, 5), ci::vec2(5, 0));
                gl::popModelView();
        }
        
        gl::popModelView();
    }
    //acceleration stick
    gl::pushModelView();
    gl::translate( center );
    gl::rotate( speed * glm::radians( 180.0f/3600.0f) );
    gl::drawSolidRect( Rectf( -110, -3, 0, 3 ) );
    gl::popModelView();
}

CINDER_APP( myHW1_DIGITApp, RendererGl )
