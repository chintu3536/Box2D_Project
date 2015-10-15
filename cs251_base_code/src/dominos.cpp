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
    float32 xg=x-r*20.0f;
        float32 yg=y-r*32.0f;
        float32 rg=r*0.8f;

        //Cog1
        {
          float32 c_rad = rg*4.0;
          b2Body* sbody;
          b2CircleShape circle;
          circle.m_radius = c_rad;
      
          b2FixtureDef ballfd;
          ballfd.shape = &circle;
          ballfd.density = 5.0f;
          ballfd.friction = 0.0f;
          ballfd.restitution = 0.0f;
          b2BodyDef ballbd;
          ballbd.type = b2_dynamicBody;
          ballbd.position.Set(xg+rg*4.7f*2.414f, yg+rg*(20.0f+4.7f*1.414f));
          sbody = m_world->CreateBody(&ballbd);
          (sbody->CreateFixture(&ballfd))->SetFcolor(255,0,0,0.85);

          b2BodyDef bd2;
          bd2.position.Set(xg+rg*4.7f*2.414f, yg+rg*(20.0f+4.7f*1.414f));
          b2Body* body2 = m_world->CreateBody(&bd2);

          b2RevoluteJointDef jointDef;
          jointDef.bodyA = sbody;
          jointDef.bodyB = body2;
          jointDef.localAnchorA.Set(0,0);
          jointDef.localAnchorB.Set(0,0);
          jointDef.collideConnected = false;
          m_world->CreateJoint(&jointDef);

          int32 n_b = 10;
          float32 ang_inc = 2.0f * b2_pi / n_b;
          float32 ang=ang_inc/2;

          for(int32 i=0;i<n_b;i++,ang+=ang_inc)
          {
            if(i==2)continue;
            b2PolygonShape shape1;
            shape1.SetAsBox(rg*0.6f, rg*0.8f, 1.1*b2Vec2(c_rad*sinf(ang), -c_rad*cosf(ang)), ang);
            b2FixtureDef fd3;
            fd3.density = 0.0f;
            fd3.shape = &shape1;
            (sbody->CreateFixture(&fd3))->SetFcolor(255,255,0,0.9);
          }
          ang=5*ang_inc/2;
          b2PolygonShape shape1;
          b2FixtureDef fd3;
          fd3.density = 0.0f;
          shape1.SetAsBox(rg*0.4f, rg*6.6f, 2.6*b2Vec2(c_rad*sinf(ang), -c_rad*cosf(ang)), ang);
          fd3.shape = &shape1;
          (sbody->CreateFixture(&fd3))->SetFcolor(255,255,0,0.9);
          shape1.SetAsBox(rg*1.8f, rg*0.35f, 1.5*b2Vec2(c_rad*sinf(ang+ang_inc*0.4f), -c_rad*cosf(ang+ang_inc*0.4f)), ang);
          fd3.shape = &shape1;
          (sbody->CreateFixture(&fd3))->SetFcolor(255,255,0,0.9);
          shape1.SetAsBox(rg*1.8f, rg*0.35f, 4.2*b2Vec2(c_rad*sinf(ang+ang_inc*0.22f), -c_rad*cosf(ang+ang_inc*0.15f)), ang);
          fd3.shape = &shape1;
          (sbody->CreateFixture(&fd3))->SetFcolor(255,255,0,0.9);
        }
        //Cog2
        {
          float32 c_rad = rg*4.0;
          b2Body* sbody;
          b2CircleShape circle;
          circle.m_radius = c_rad;
      
          b2FixtureDef ballfd;
          ballfd.shape = &circle;
          ballfd.density = 5.0f;
          ballfd.friction = 0.0f;
          ballfd.restitution = 0.0f;
          b2BodyDef ballbd;
          ballbd.type = b2_dynamicBody;
          ballbd.position.Set(xg+rg*-4.7f, yg+rg*20.0f);
          sbody = m_world->CreateBody(&ballbd);
          (sbody->CreateFixture(&ballfd))->SetFcolor(255,0,0,0.85);

          b2BodyDef bd2;
          bd2.position.Set(xg+rg*-4.7f, yg+rg*20.0f);
          b2Body* body2 = m_world->CreateBody(&bd2);

          b2RevoluteJointDef jointDef;
          jointDef.bodyA = sbody;
          jointDef.bodyB = body2;
          jointDef.localAnchorA.Set(0,0);
          jointDef.localAnchorB.Set(0,0);
          jointDef.collideConnected = false;
          m_world->CreateJoint(&jointDef);

          int32 n_b = 10;
          float32 ang_inc = 2.0f * b2_pi / n_b;
          float32 ang=0;

          for(int32 i=0;i<n_b;i++,ang+=ang_inc)
          {
            b2PolygonShape shape1;
            shape1.SetAsBox(rg*0.6f, rg*0.8f, 1.1*b2Vec2(c_rad*sinf(ang), -c_rad*cosf(ang)), ang);
            b2FixtureDef fd3;
            fd3.density = 0.0f;
            fd3.shape = &shape1;
            (sbody->CreateFixture(&fd3))->SetFcolor(255,255,0,0.9);
          }

          {
            b2PolygonShape shape1;
            shape1.SetAsBox(rg*0.3f, rg*7.5f, rg*b2Vec2(-3.0f, -13.0f), b2_pi/3);
            b2FixtureDef fdb;
            fdb.density = 65.0f;
            fdb.restitution = 0.4f;
            fdb.shape = &shape1;
            (sbody->CreateFixture(&fdb))->SetFcolor(0,0,255,0.9);

            b2EdgeShape eshape; 
            eshape.Set(b2Vec2(0,0),b2Vec2(rg*-7.5f,rg*-10.5f));
            b2FixtureDef myfd;
            myfd.shape = &eshape;
            myfd.density = 0.0f;
            myfd.filter.maskBits = 0x0000;
            (sbody->CreateFixture(&myfd))->SetFcolor(255,0,0,0.9f);
          }

        }
  }
}
