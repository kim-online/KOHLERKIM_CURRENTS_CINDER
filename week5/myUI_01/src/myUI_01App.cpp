#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Timeline.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class myUI_01App : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    float map(float x, float in_min, float in_max, float out_min, float out_max);
    
    ci::Anim<float>  angle = 0;
    ci::Anim<float> r1, r2;
    ci::Anim<float> col1;
    ci::vec2 startPos;
    
    
};

void myUI_01App::setup()
{
    startPos = ci::app::getWindowCenter();
    r1 = 200.f;
    r2 = 70.f;
    col1 = 0.00f;

    gl::clear( Color( 0, 0, 0 ) );
    
}

void myUI_01App::mouseDown( MouseEvent event )
{
    angle = 0;

}

void myUI_01App::update()
{
      timeline().apply( &angle, 1.0f, 0.2f, ci::EaseInSine()).finishFn([&](){
        angle = 0;
    });
    
    
}

void myUI_01App::draw()
{
    
	gl::clear( Color( 0, 0, 0 ) );
    
    gl::color(0.f, 0.5f, 1.0f, 0.1f);
    //Blue large circle
    gl::pushModelMatrix();
    ci::gl::translate(startPos);
    ci::gl::begin(GL_TRIANGLE_FAN);
    gl::vertex(0, 0);
    for(float i = 0; i < 360; i++){
        float x = cos(glm::radians(i*angle));
        float y = sin(glm::radians(i*angle));
        gl::vertex(x*r1, y*r1);
        col1 = map(i, 0, 360, 0.00f, 1.00f);
        gl::color(0.f, 0.5f, 1.0f, col1);
    }
    ci::gl::end();
    
    gl::popModelMatrix();
    
    gl::color(0.f, 0.f, 0.f, 1.0f);
    //Black small circle on top of the blue
    gl::pushModelMatrix();
    ci::gl::translate(startPos);
    ci::gl::begin(GL_TRIANGLE_FAN);
    gl::vertex(0, 0);
    for(float i = 0; i < 360; i++){
        float x = cos(glm::radians(i*angle));
        float y = sin(glm::radians(i*angle));
        gl::vertex(x*r2, y*r2);
       
    }
    ci::gl::end();
    gl::popModelMatrix();

    
}

float myUI_01App::map(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

CINDER_APP( myUI_01App, RendererGl )
