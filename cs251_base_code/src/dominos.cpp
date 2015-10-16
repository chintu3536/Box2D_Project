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
  {
    {
        b2Body* body3;
        //Revolving V platform
        {
          b2PolygonShape shape;
          shape.SetAsBox(r*0.4f, r*8.0f);    
          b2BodyDef bd;
          bd.position.Set(x+r*12.0f, y+r*22.0f);
          bd.type = b2_dynamicBody;
          b2Body* body = m_world->CreateBody(&bd);
          b2FixtureDef *fd = new b2FixtureDef;
          fd->density = 10.0f;
          fd->friction = 0.24f;
          fd->shape = &shape;
          (body->CreateFixture(fd))->SetFcolor(139,0,139,0.9);
               
          b2BodyDef bd2;
          bd2.position.Set(x+r*12.0f, y+r*22.0f);
          b2Body* bodyf = m_world->CreateBody(&bd2);

          b2RevoluteJointDef jointDef;
          jointDef.bodyA = body;
          jointDef.bodyB = bodyf;
          jointDef.localAnchorA.Set(0,0);
          jointDef.localAnchorB.Set(0,0);
          jointDef.collideConnected = false;
          m_world->CreateJoint(&jointDef);

          bd.position.Set(x+r*12.0f, y+r*30.0f);
          b2Body* body2 = m_world->CreateBody(&bd);
          shape.SetAsBox(r*0.4f, r*2.0f, r*b2Vec2(-1.4,-1.414), -b2_pi/4);
          fd->shape = &shape;
          (body2->CreateFixture(fd))->SetFcolor(139,0,139,0.9);

          jointDef.bodyA = body;
          jointDef.bodyB = body2;
          jointDef.localAnchorA.Set(0,r*8.0f);
          jointDef.localAnchorB.Set(0,r*0.0f);
          m_world->CreateJoint(&jointDef);

          bd.position.Set(x+r*(12.0f-2*1.404), y+r*(30.0f-2*1.404));
          body3 = m_world->CreateBody(&bd);
          shape.SetAsBox(r*4.0f, r*0.4f, r*b2Vec2(-4.0f,0.0f), 0);
          fd->shape = &shape;
          (body3->CreateFixture(fd))->SetFcolor(139,0,139,0.9);
          shape.SetAsBox(r*3.0f, r*2.0f, r*b2Vec2(-11.0f,0.0f), 0);
          fd->shape = &shape;
          (body3->CreateFixture(fd))->SetFcolor(139,0,139,1.0);

          b2RopeJointDef jointDef2;
          jointDef2.bodyA = body3;
          jointDef2.bodyB = body2;
          jointDef2.localAnchorA.Set(r*0.0f,r*0.0f);
          jointDef2.localAnchorB.Set(r*-2.83f,r*-2.75f);
          jointDef2.maxLength = r*0.05f;
          m_world->CreateJoint(&jointDef2);
        }
  }
}
