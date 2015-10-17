#include "cs251_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"

namespace cs251
{ 
  dominos_t::dominos_t()
  {
    b2Body* b1;  
    {
      b2EdgeShape shape; 
      shape.Set(b2Vec2(-30.0f, 0.0f), b2Vec2(30.0f, 0.0f));
      b2BodyDef bd; 
      b1 = m_world->CreateBody(&bd); 
      b1->CreateFixture(&shape, 0.0f);
    }
         b2Body* b2;  
    {
      
      b2EdgeShape shape; 
      shape.Set(b2Vec2(-30.0f, 0.0f), b2Vec2(-30.0f, 30.0f));
      b2BodyDef bd; 
      b2 = m_world->CreateBody(&bd); 
      b2->CreateFixture(&shape, 0.0f);
    }
         b2Body* b3;  
    {
      
      b2EdgeShape shape; 
      shape.Set(b2Vec2(-30.0f, 30.0f), b2Vec2(30.0f, 30.0f));
      b2BodyDef bd; 
      b3 = m_world->CreateBody(&bd); 
      b3->CreateFixture(&shape, 0.0f);
    }
         b2Body* b4;  
    {
      
      b2EdgeShape shape; 
      shape.Set(b2Vec2(30.0f, 30.0f), b2Vec2(30.0f, 0.0f));
      b2BodyDef bd; 
      b4 = m_world->CreateBody(&bd); 
      b4->CreateFixture(&shape, 0.0f);
    }
    {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 0.5;
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 50.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 1.0f;
for(int i=0;i<600;i++)
{
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(i%30,2*i%30);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
}

    } 
      

  }
  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
