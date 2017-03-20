
#include "myParticle01.h"
#include "cinder/Perlin.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

Particle01::Particle01(glm::vec2 startPos, glm::vec2 mMouseVel, float n, float m)
{

    //how long before particle is deleted
    lifetime = Rand::randInt(300.f, 1000.f);
    //emitter position
    Loc = startPos;
    _n = make_shared<float>(n);
    _m = make_shared<float>(m);
    _mouseVel = make_shared<glm::vec2>(mMouseVel);
    velOff = Rand::randVec2() * Rand::randFloat( 1.0f, 3.0f );
    
    //THINGS THAT DIDNT WORK OUT
    //Vel = glm::vec2(*_n, *_m) + (mMouseVel*0.25f);
    //console() << mMouseVel << endl;
    //_n = make_shared<int>(n);
    //_m = make_shared<int>(m);
   // typedef boost::numeric::converter<int,double> Double2Int;
   // _n = Double2Int::convert(n);
   // _m = Double2Int()(n);
    //Acc.x = mPerlin.fBm(n, sin(app::getElapsedSeconds()) )*0.1;
    //Acc.y = mPerlin.fBm(m, cos(app::getElapsedSeconds()) )*0.1;
    //set velocity
    //Vel.x = mPerlin.fBm(n)*1.5;
    //Vel.y = mPerlin.fBm(m)*1.5;
   // _Velx = mPerlin.fBm(_n);
   // _Vely = mPerlin.fBm(_m);
   // _Velx = Vel.x;
   // _Vely = Vel.y;
    //typedef boost::numeric::converter<int,float> Float2Int;
    //_x = Float2Int::convert(_Velx);
    //_y = Float2Int()(_Velx);
    //static_cast<Derived*>(a);
   // static_cast <int> (std::floor(_y));
    //static_cast<int>(floor(_Vely)) << endl;
}

void Particle01::setup()
{
    
}


void Particle01::update()
{
    
    //get the velocity of mouse to give particles a push
    Vel = glm::vec2(*_n, *_m) + (*_mouseVel*0.25f) + velOff;
    //decrease the push until its almost 0
    if ((*_mouseVel).y < 0){
    (*_mouseVel).y += 5;
    }
    
    //adding the forces to the particles
    Acc.x += (mPerlin.fBm(Loc.x)*(sin((getElapsedSeconds()*2*3.14)*10)*25));
    Acc.y += (mPerlin.fBm(Loc.y)*(cos((getElapsedSeconds()*2*3.14)*10)*25));
    Vel.x += Acc.x;
    Vel.y += Acc.y;
    Loc.x += Vel.x;
    Loc.y += Vel.y;
    
    //decrease lifetime
    lifetime -= 3.0f;
    //reset acc so it doesnt build up
    Acc *= 0;

    
}

void Particle01::display()
{
    
    //Color of particle depends on position distance
    //opacity depends on lifetime
    
    float value = ci::length(abs(Loc));
    float red = map(value, 0.0f, 1000.0f, 0.3f, 1.0f);
    float green = map(Loc.x, 0.0f, 1024.0f, 0.0f, 1.0f);
    float blue = map(Loc.y, 0.0f, 1024.0f, 1.0f, 0.0f);
    float life = map(lifetime, 0.0f, 600.0f, 0.0f, 1.0f);
    ci::gl::color(red, green, blue, life);
    // draw particle
    gl::vertex(Loc);
    
}

bool Particle01::isDead()
{
    //check if dead or not
    if (lifetime < 0.0) {
        return true;
    } else {
        return false;
    }
}

//IS THERE SERIOUSLY NO MAP FUNCTION IN CINDER/C++??? I HAVE TO CREATE ONE MYSELF???? IS THIS 2017???
float Particle01::map(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}