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
          b2BodyDef bd;
          bd.position.Set(xk+rk*-39.0f, yk+rk*6.0f);
          b2Body* body = m_world->CreateBody(&bd);
          b2PolygonShape shape;
          shape.SetAsBox(rk*12.0f, rk*0.3f, rk*b2Vec2(-11.0f,0.0f), 0.0f);
          b2FixtureDef fdb;
          fdb.density = 0.5f;
          fdb.shape = &shape;
          (body->CreateFixture(&fdb))->SetFcolor(255,255,0,0.9);
          shape.SetAsBox(rk*0.25f, rk*1.0f, rk*b2Vec2(1.0f,0.6f), 0.0f);
          fdb.shape = &shape;
          (body->CreateFixture(&fdb))->SetFcolor(255,255,0,0.9);
        }
        //sphbase
        {
          b2BodyDef bd;
          bd.position.Set(xk+rk*-37.0f, yk+rk*20.0f);
          b2Body* body = m_world->CreateBody(&bd);
          b2PolygonShape shape;
          shape.SetAsBox(rk*0.8f, rk*0.3f);
          b2FixtureDef fdb;
          fdb.density = 0.5f;
          fdb.shape = &shape;
          (body->CreateFixture(&fdb))->SetFcolor(255,0,255,0.9);

        }
        //sphere
        {
          b2Body* sbody;
          b2CircleShape circle;
          circle.m_radius = rk*1.5;
      
          b2FixtureDef ballfd;
          ballfd.shape = &circle;
          ballfd.density = 50.0f;
          ballfd.friction = 0.4f;
          ballfd.restitution = 0.0f;
          b2BodyDef ballbd;
          ballbd.type = b2_dynamicBody;
          ballbd.position.Set(xk+rk*-37.5f, yk+rk*22.0f);
          sbody = m_world->CreateBody(&ballbd);
          (sbody->CreateFixture(&ballfd))->SetFcolor(0,255,0,0.85);
        }

        //Revolving V platform
        {
          b2PolygonShape shape;
          shape.SetAsBox(rk*0.2f, rk*18.2f);    
          b2BodyDef bd;
          bd.position.Set(xk+rk*-35.0f, yk+rk*4.0f);
          bd.type = b2_dynamicBody;
          b2Body* body = m_world->CreateBody(&bd);
          b2FixtureDef *fd = new b2FixtureDef;
          fd->density = 1.0f;
          fd->shape = &shape;
          (body->CreateFixture(fd))->SetFcolor(139,0,139,0.9);
          shape.SetAsBox(rk*0.5f, rk*0.3f, rk*b2Vec2(-0.5f, 17.75f), 0);
          fd->density = 0.0f;
          fd->shape = &shape;
          (body->CreateFixture(fd))->SetFcolor(139,0,139,0.9);

          b2BodyDef bd2;
          bd2.position.Set(xk+rk*-35.0f, yk+rk*4.0f);
          b2Body* body2 = m_world->CreateBody(&bd2);

          b2RevoluteJointDef jointDef;
          jointDef.bodyA = body;
          jointDef.bodyB = body2;
          jointDef.localAnchorA.Set(0,0);
          jointDef.localAnchorB.Set(0,0);
          jointDef.collideConnected = false;
          m_world->CreateJoint(&jointDef);
        }
        //Seesaw
        {
          b2BodyDef bd;
          bd.position.Set(xk+rk*-50.0f, yk+rk*9.0f);
          bd.type = b2_dynamicBody;
          b2Body* body = m_world->CreateBody(&bd);
          b2PolygonShape shape;
          shape.SetAsBox(rk*10.0f, rk*0.2f); 
          b2FixtureDef *fd = new b2FixtureDef;
          fd->density = 1.0f;
          fd->shape = &shape;
          fd->friction = 1.0f;
          (body->CreateFixture(fd))->SetFcolor(139,0,139,0.9);
          
          b2BodyDef bd2;
          bd2.position.Set(xk+rk*-46.0f, yk+rk*7.5f);
          b2Body* body2 = m_world->CreateBody(&bd2);
          b2FixtureDef *fd2 = new b2FixtureDef;
          shape.SetAsBox(rk*0.2f, rk*1.5f); 
          fd2->shape = &shape;
          (body2->CreateFixture(fd2))->SetFcolor(139,0,139,0.9);

          b2BodyDef bd3;
          bd3.type = b2_dynamicBody;
          bd3.position.Set(xk+rk*-56.0f, yk+rk*10.6f);
          b2Body* body3 = m_world->CreateBody(&bd3);
          shape.SetAsBox(rk*1.5f, rk*1.5f); 
          b2FixtureDef *fd3 = new b2FixtureDef;
          fd3->density = 7.0f;
          fd3->friction = 1.0f;
          fd3->shape = &shape;
          (body3->CreateFixture(fd3))->SetFcolor(0,139,0,0.9);

          b2RevoluteJointDef jointDef;
          jointDef.bodyA = body;
          jointDef.bodyB = body2;
          jointDef.localAnchorA.Set(rk*4,0);
          jointDef.localAnchorB.Set(0,rk*1.5);
          jointDef.collideConnected = false;
          m_world->CreateJoint(&jointDef);
        }
      }
  }
      
}
