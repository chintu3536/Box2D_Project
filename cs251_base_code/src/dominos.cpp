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
  /**  The is the constructor 
   * This is the documentation block for the constructor.
   */ 
  
  dominos_t::dominos_t()
  {
//maze
{
int x=-30;int y=20;int r=3;
//ground
    b2Body* g1;  
    {
      
      b2EdgeShape shape; 
      shape.Set(b2Vec2(-90.0f,y-3*r), b2Vec2(x+3*r,y-3*r));
      b2BodyDef bd; 
      g1 = m_world->CreateBody(&bd); 
      g1->CreateFixture(&shape, 0.0f);
    }
    b2Body* g2;  
    {
      
      b2EdgeShape shape; 
      shape.Set(b2Vec2(x+5*r,y-3*r), b2Vec2(x+6*r,y-3*r));
      b2BodyDef bd; 
      g2 = m_world->CreateBody(&bd); 
      g2->CreateFixture(&shape, 0.0f);
    }
      //the ball
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = r/2;
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
	 ballfd.friction = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(x-2.5*r, y+2.5*r);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    b2Body* b1;  
    {
      b2EdgeShape shape; 
      shape.Set(b2Vec2(x-3*r, y-3*r), b2Vec2(x+3*r,y-3*r));
      b2BodyDef bd; 
      b1 = m_world->CreateBody(&bd); 
      b1->CreateFixture(&shape, 0.0f);
    }
    b2Body* b2;  
    {
      b2EdgeShape shape; 
      shape.Set(b2Vec2(x-3*r, y-3*r), b2Vec2(x-3*r,y+2*r));
      b2BodyDef bd; 
      b2 = m_world->CreateBody(&bd); 
      b2->CreateFixture(&shape, 0.0f);
    }
    b2Body* b3;  
    {
      b2EdgeShape shape; 
      shape.Set(b2Vec2(x+3*r,y-2*r), b2Vec2(x+3*r,y+3*r));
      b2BodyDef bd; 
      b3 = m_world->CreateBody(&bd); 
      b3->CreateFixture(&shape, 0.0f);
    }
    b2Body* b4;  
    {
      b2EdgeShape shape; 
      shape.Set(b2Vec2(x-3*r, y+3*r), b2Vec2(x+3*r,y+3*r));
      b2BodyDef bd; 
      b4 = m_world->CreateBody(&bd); 
      b4->CreateFixture(&shape, 0.0f);
    }
    b2Body* b5;  
    {
      b2EdgeShape shape; 
      shape.Set(b2Vec2(x-3*r, y+2*r), b2Vec2(x-r,y+2*r));
      b2BodyDef bd; 
      b5 = m_world->CreateBody(&bd); 
      b5->CreateFixture(&shape, 0.0f);
    }
    b2Body* b6;  
    {
      b2EdgeShape shape; 
      shape.Set(b2Vec2(x+r, y+2*r), b2Vec2(x+2*r,y+2*r));
      b2BodyDef bd; 
      b6 = m_world->CreateBody(&bd); 
      b6->CreateFixture(&shape, 0.0f);
    }
    b2Body* b7;  
    {
      b2EdgeShape shape; 
      shape.Set(b2Vec2(x-2*r, y+r), b2Vec2(x+2*r,y+r));
      b2BodyDef bd; 
      b7 = m_world->CreateBody(&bd); 
      b7->CreateFixture(&shape, 0.0f);
    }
    b2Body* b8;  
    {
      b2EdgeShape shape; 
      shape.Set(b2Vec2(x+2*r, y+r), b2Vec2(x+2*r,y+2*r));
      b2BodyDef bd; 
      b8 = m_world->CreateBody(&bd); 
      b8->CreateFixture(&shape, 0.0f);
    }
    b2Body* b10;  
    {
      b2EdgeShape shape; 
      shape.Set(b2Vec2(x, y-r), b2Vec2(x+3*r,y-r));
      b2BodyDef bd; 
      b10 = m_world->CreateBody(&bd); 
      b10->CreateFixture(&shape, 0.0f);
    }
    b2Body* b11;  
    {
      b2EdgeShape shape; 
      shape.Set(b2Vec2(x-2*r, y-2*r), b2Vec2(x+2*r,y-2*r));
      b2BodyDef bd; 
      b11 = m_world->CreateBody(&bd); 
      b11->CreateFixture(&shape, 0.0f);
    }
    b2Body* b14;  
    {
      b2EdgeShape shape; 
      shape.Set(b2Vec2(x-2*r, y-r), b2Vec2(x-2*r,y-2*r));
      b2BodyDef bd; 
      b14 = m_world->CreateBody(&bd); 
      b14->CreateFixture(&shape, 0.0f);
    }
    b2Body* b15;  
    {
      b2EdgeShape shape; 
      shape.Set(b2Vec2(x-3*r, y), b2Vec2(x,y));
      b2BodyDef bd; 
      b15 = m_world->CreateBody(&bd); 
      b15->CreateFixture(&shape, 0.0f);
    }
    b2Body* b16;  
    {
      b2EdgeShape shape; 
      shape.Set(b2Vec2(x+r, y), b2Vec2(x+3*r,y));
      b2BodyDef bd; 
      b16 = m_world->CreateBody(&bd); 
      b16->CreateFixture(&shape, 0.0f);
    }
    b2Body* b17;  
    {
      b2EdgeShape shape; 
      shape.Set(b2Vec2(x+3*r, y-3*r), b2Vec2(x+5*r,y-4*r));
      b2BodyDef bd; 
      b17 = m_world->CreateBody(&bd); 
      b17->CreateFixture(&shape, 0.0f);
    }
    b2Body* b18;  
    {
      b2EdgeShape shape; 
      shape.Set(b2Vec2(x+3*r, y-2*r), b2Vec2(x+5*r,y-3*r));
      b2BodyDef bd; 
      b18 = m_world->CreateBody(&bd); 
      b18->CreateFixture(&shape, 0.0f);
    }

    b2Body* b19;  
    {
      b2EdgeShape shape; 
      shape.Set(b2Vec2(x+5*r, y-4*r), b2Vec2(x+19*r,y-4*r));
      b2BodyDef bd; 
      b19 = m_world->CreateBody(&bd); 
      b19->CreateFixture(&shape, 0.0f);
    }

//The pulley system
    {
      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
     // bd->position.Set(-10,15);
      bd->fixedRotation = true;
      //the ball
      b2Body* box1;
      b2CircleShape circle;
      circle.m_radius = r/2;
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballfd.density = 2.0f;
      ballbd.position.Set(x+16*r,y+3*r);
      box1 = m_world->CreateBody(&ballbd);
      box1->CreateFixture(&ballfd);
//gate
b2Body* gate;
    {
      b2PolygonShape shape;
      shape.SetAsBox(3*r, 3*r);
      b2BodyDef bd;
      bd.type = b2_dynamicBody;
      bd.position.Set(x+8*r, y);
      gate = m_world->CreateBody(&bd);
      gate->CreateFixture(&shape, 0.0f);
    }
      // The pulley joint
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorGround1(x+8*r,y+8*r); // Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(x+16*r,y+8*r); // Anchor point for ground 2 in world axis
      float32 ratio = 1.0f; // Define ratio
      myjoint->Initialize(gate, box1,worldAnchorGround1, worldAnchorGround2,b2Vec2(x+8*r,y+3*r) , box1->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);
    }
//all revolving platforms
{
      b2PolygonShape shape;
      shape.SetAsBox(0.2,3*r);
      b2BodyDef bd;
      bd.position.Set(x+16*r,y-0.5*r);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      bd2.position.Set(x+16*r,y-0.5*r);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }
{
      b2PolygonShape shape;
      shape.SetAsBox(1.5*r,0.2);
      b2BodyDef bd;
      bd.position.Set(x+15.5*r,y+2.6*r);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      bd2.position.Set(x+15.5*r,y+2.6*r);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }

    
}

  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
