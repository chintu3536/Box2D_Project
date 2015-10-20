/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

/* 
 * Base code for CS 251 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * 
 */


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
  {     {
        float32 x1=x+r*2.7f;
        float32 y1=y+r*3.0f;
        float32 r1=r*1.0f;

        float32 len = 3.2f;
        float32 lenhx = 1.0f;
        //Steps
        {
          b2BodyDef bd;
          bd.position.Set(x1+r1*(25.0f), y1+r1*7.0f);
          b2Body* stbody = m_world->CreateBody(&bd);

          b2EdgeShape eshape; 
          b2FixtureDef myfd;
          for(int i=0; i<6; i++)
          {
            eshape.Set(b2Vec2(r1*(-len*i-lenhx*i),r1*-len*i),b2Vec2(r1*(-len-len*i-lenhx*(i+1)),r1*-len*i));
            myfd.shape = &eshape;
            (stbody->CreateFixture(&myfd))->SetFcolor(255,0,0,0.9f);
          }
          eshape.Set(b2Vec2(0,r1*-len),b2Vec2(r1*2*len,r1*-len));
          myfd.shape = &eshape;
          (stbody->CreateFixture(&myfd))->SetFcolor(255,0,0,0.9f);
          for(int i=0; i<5; i++)
          {
            eshape.Set(b2Vec2(r1*(-len-len*i-lenhx*(i+1)),r1*-len*i),b2Vec2(r1*(-len-len*i-lenhx*(i+1)),r1*(-len-len*i)));
            myfd.shape = &eshape;
            (stbody->CreateFixture(&myfd))->SetFcolor(255,0,0,0.9f);
          }
          eshape.Set(b2Vec2(0,0),b2Vec2(0,r1*-len));
          myfd.shape = &eshape;
          (stbody->CreateFixture(&myfd))->SetFcolor(255,0,0,0.9f);
          eshape.Set(b2Vec2(r1*2*len,0),b2Vec2(r1*2*len,r1*-len));
          myfd.shape = &eshape;
          (stbody->CreateFixture(&myfd))->SetFcolor(255,0,0,0.9f);
        }

        {
          b2Body* sbody1;
          {
            b2CircleShape circle;
            circle.m_radius = r1*1.5f;      
            b2FixtureDef ballfd;
            ballfd.shape = &circle;
            ballfd.density = 25.0f;
            ballfd.friction = 0.0f;
            ballfd.restitution = 0.0f;
            b2BodyDef ballbd;
            ballbd.type = b2_dynamicBody;
            ballbd.position.Set(x1+r1*23.0f, y1+r1*9.0f);
            sbody1 = m_world->CreateBody(&ballbd);
            (sbody1->CreateFixture(&ballfd))->SetFcolor(0,0,255,0.85);
          }
          b2Body* sbody2;
          {          
            b2CircleShape circle;
            circle.m_radius = r1*1.5f;      
            b2FixtureDef ballfd;
            ballfd.shape = &circle;
            ballfd.density = 25.0f;
            ballfd.friction = 0.0f;
            ballfd.restitution = 0.0f;
            b2BodyDef ballbd;
            ballbd.type = b2_dynamicBody;
            ballbd.position.Set(x1+r1*(23.5f-len-lenhx), y1+r1*(9.0f-len));
            sbody2 = m_world->CreateBody(&ballbd);
            (sbody2->CreateFixture(&ballfd))->SetFcolor(255,0,0,0.85);
          }
          {
            b2RopeJointDef jointDef;
            jointDef.bodyA = sbody1;
            jointDef.bodyB = sbody2;
            jointDef.localAnchorA.Set(0,0);
            jointDef.localAnchorB.Set(0,0);
            jointDef.maxLength = r1*5.0f;
            jointDef.collideConnected = true;
            m_world->CreateJoint(&jointDef);
          } 
        }
      }
  }
      
}
