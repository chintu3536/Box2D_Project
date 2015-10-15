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
        float32 rc=r*1.45f;
        float32 xc=r*-20.0f;
        float32 yc=r*7.5f;

        b2BodyDef cardf;
        cardf.type = b2_dynamicBody;
        cardf.position.Set(x+rc*xc, y+rc*yc);
        b2Body* car = m_world->CreateBody(&cardf);
        car->ApplyLinearImpulse(b2Vec2(10,0), car->GetPosition() ,true);
        b2FixtureDef cfd;
        cfd.density = 5.0f;
        cfd.friction = 0.0f;
        b2CircleShape circle;
        b2PolygonShape shape1;
        //windows
        shape1.SetAsBox(rc*1.0f, rc*1.0f, rc*b2Vec2(-1.8f,0.5f), 0);
        cfd.shape = &shape1;
        (car->CreateFixture(&cfd))->SetFcolor(0.5294*255,0.8078*255,0.9804*255,1.0);
        shape1.SetAsBox(rc*1.0f, rc*1.0f, rc*b2Vec2(1.8f,0.5f), 0);
        cfd.shape = &shape1;
        (car->CreateFixture(&cfd))->SetFcolor(0.5294*255,0.8078*255,0.9804*255,1.0);
        //body
        shape1.SetAsBox(rc*2.5f, rc*2.5f);
        cfd.shape = &shape1;      
        (car->CreateFixture(&cfd))->SetFcolor(255,0,0,1.0,0);
        shape1.SetAsBox(rc*6.25f, rc*1.25f, rc*b2Vec2(0.0f,-1.25f), 0);
        cfd.shape = &shape1;
        (car->CreateFixture(&cfd))->SetFcolor(255,0,0,1.0,0);
        shape1.SetAsBox(rc*7.5f, rc*1.0f, rc*b2Vec2(0.0f,-2.0f), 0);
        cfd.shape = &shape1;
        (car->CreateFixture(&cfd))->SetFcolor(255,0,0,1.0,0);
        //body curves
        circle.m_radius = rc*2.5f;
        circle.m_p=b2Vec2(rc*-2.5,0);      
        cfd.shape = &circle;
        (car->CreateFixture(&cfd))->SetFcolor(255,0,0,1.0);
        circle.m_p=b2Vec2(rc*2.5,0);      
        cfd.shape = &circle;
        (car->CreateFixture(&cfd))->SetFcolor(255,0,0,1.0);
        circle.m_radius = rc*1.25f;
        circle.m_p=b2Vec2(rc*-6.25,rc*-1.25);
        cfd.shape = &circle;
        (car->CreateFixture(&cfd))->SetFcolor(255,0,0,1.0);
        circle.m_p=b2Vec2(rc*6.25,rc*-1.25);
        cfd.shape = &circle;
        (car->CreateFixture(&cfd))->SetFcolor(255,0,0,1.0);    
        //wheels
        {
          b2Body* w1;
          b2Body* w2;
          b2CircleShape circle;
          circle.m_radius = r*1.25;
          b2FixtureDef ballfd;
          ballfd.shape = &circle;
          ballfd.density = 5.0f;
          ballfd.friction = 0.0f;
          ballfd.restitution = 0.0f;
          b2BodyDef ballbd;
          ballbd.type = b2_dynamicBody;       
          
          ballbd.position.Set(x+rc*(xc-4.75f), y+rc*(yc-4.0f));
          w1 = m_world->CreateBody(&ballbd); 
          (w1->CreateFixture(&ballfd))->SetFcolor(255,255,0,0.85);
          ballbd.position.Set(x+rc*(xc+4.75f), y+rc*(yc-4.0f)); 
          w2 = m_world->CreateBody(&ballbd);
          (w2->CreateFixture(&ballfd))->SetFcolor(255,255,0,0.85);
          //joints
          b2DistanceJointDef jointDef;
          jointDef.bodyA = w1;
          jointDef.bodyB = car;
          jointDef.localAnchorA.Set(0,0);
          jointDef.localAnchorB.Set(rc*-4.75f,rc*-3.0f);
          jointDef.length = rc*0.8f;
          jointDef.collideConnected = true;
          jointDef.frequencyHz = 0.0f;
          m_world->CreateJoint(&jointDef);

          jointDef.bodyA = w2;
          jointDef.localAnchorB.Set(rc*4.75f,rc*-3.0f);
          m_world->CreateJoint(&jointDef);
        }
    }
  }
}
