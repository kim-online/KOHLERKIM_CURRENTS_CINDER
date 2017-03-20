#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

//At the time when I wrote this, I thought I was actually moving around logically on the GPU
//but I now actually believe the numbers put into an empty Texture are just dummy numbers and doesn't relate
//too the position on the GPU, not sure though. What do you think?

using namespace ci;
using namespace ci::app;
using namespace std;

class myHW2App : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    void line();
    
    
    gl::TextureRef mTexture;
    ci::Surface8u mSurface;
    int x;
    int y;
    int lineX;
    int lineY;
    
    
    
};

void myHW2App::setup()
{
    
    ci::app::setWindowSize(500, 500);
    x = 500/2;
    y = 500/2;
    lineX = getWindowWidth()/2;
    lineY = getWindowHeight()/2;
    try {
        //Create empty texture, or as I have done here, with dummy numbers, then it will pull what is left on that position in the GPU from earlier
        mTexture = gl::Texture::create(x, y);
    } catch(exception& e){
        ci::app::console() << e.what() << std::endl;
    }
    
}

void myHW2App::mouseDown( MouseEvent event )
{

}


void myHW2App::update()
{
    //move around randomly in the gpu memory
    x += rand() % 100+(-50);
    y += rand() % 100+(-50);
    
    //if going outside the screen go back
    if (x <= 0){
        x += 50;
    }
    if (x >= 1000){
        x -= 50;
    }
    if (y <= 0){
        y += 50;
    }
    if (y >= 1000){
        y -= 50;
    }
    
    ci::app::console() << "x:" << x << std::endl;
    ci::app::console() << "y:" << y << std::endl;
    //update texture with the new position every frame as they have been updated, to get another position on the GPU
    mTexture = gl::Texture::create(x, y);
    

}

void myHW2App::line(){
    
    //This line is supposed to articulate in a more graphical way how we are moving around on the GPU in relation to the screen size
    gl::lineWidth(0.9f);
    ci::gl::color(ci::Color(1.f, 0.f, 0.f));
    gl::drawLine(ci::vec2(lineX, lineY), ci::vec2(x, y));
    gl::drawLine(ci::vec2(lineX-1, lineY-1), ci::vec2(x-1, y-1));
    gl::drawLine(ci::vec2(lineX+1, lineY+1), ci::vec2(x+1, y+1));
}

void myHW2App::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    
    ci::gl::color(ci::Color(255.f, 255.f, 255.f));
    
    //draw the texture
    gl::draw(mTexture, Rectf(0, 0, 500, 500));
    myHW2App::line();

    //save last position to lineX & lineY
    lineX = x;
    lineY = y;
}

CINDER_APP( myHW2App, RendererGl )
