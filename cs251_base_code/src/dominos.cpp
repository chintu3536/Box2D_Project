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
  {{
        {
          b2PolygonShape shape;
          shape.SetAsBox(r*1.8f, r*0.3f);
      
          b2BodyDef bd;
          bd.position.Set(x+r*-35.0f, y+r*30.0f);
          bd.type = b2_dynamicBody;
          b2Body* body = m_world->CreateBody(&bd);
          b2FixtureDef *fd = new b2FixtureDef;
          fd->density = 1.0f;
          fd->shape = &shape;
          (body->CreateFixture(fd))->SetFcolor(139,0,139,0.9);

          b2PolygonShape shape2;
          shape2.SetAsBox(0.2f, 0.2f);
          b2BodyDef bd2;
          bd2.position.Set(x+r*-35.0f, y+r*30.0f);
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
          b2BodyDef bd;
          bd.position.Set(x+r*-32.4f, y+r*31.0f);
          b2Body* bbody = m_world->CreateBody(&bd);
          b2PolygonShape shape1;
          shape1.SetAsBox(r*0.2f, r*0.8f);
          b2FixtureDef fdb;
          fdb.density = 0.0f;
          fdb.shape = &shape1;
          (bbody->CreateFixture(&fdb))->SetFcolor(0,255,0,0.9);
        }

        b2Body* sbody1;
        {
          b2CircleShape circle;
          circle.m_radius = r*1.0f;
      
          b2FixtureDef ballfd;
          ballfd.shape = &circle;
          ballfd.density = 20.0f;
          ballfd.friction = 0.0f;
          ballfd.restitution = 0.0f;
          b2BodyDef ballbd;
          ballbd.type = b2_dynamicBody;
          ballbd.position.Set(x+r*-35.0f, y+r*31.5f);
          sbody1 = m_world->CreateBody(&ballbd);
          (sbody1->CreateFixture(&ballfd))->SetFcolor(255,124,0,0.9);
        }

        b2Body* sbody2;
        {
          
          b2CircleShape circle;
          circle.m_radius = r*1.0f;
      
          b2FixtureDef ballfd;
          ballfd.shape = &circle;
          ballfd.density = 20.0f;
          ballfd.friction = 0.0f;
          ballfd.restitution = 0.0f;
          b2BodyDef ballbd;
          ballbd.type = b2_dynamicBody;
          ballbd.position.Set(x+r*-24.0f, y+r*25.5f);
          sbody2 = m_world->CreateBody(&ballbd);
          (sbody2->CreateFixture(&ballfd))->SetFcolor(128,0,128,0.9);
        }

        {
          b2RopeJointDef jointDef;
          jointDef.bodyA = sbody1;
          jointDef.bodyB = sbody2;
          jointDef.localAnchorA.Set(0,0);
          jointDef.localAnchorB.Set(0,0);
          jointDef.maxLength = r*13.2f;
          m_world->CreateJoint(&jointDef);
        }

        {
          b2BodyDef bd2;
          bd2.position.Set(x+r*-24.5f, y+r*24.0f);
          b2Body* ibody = m_world->CreateBody(&bd2);
          b2PolygonShape shape1;
          shape1.SetAsBox(r*0.2f, r*0.8f, b2Vec2(0.0f, 0.0f), b2_pi/3);
          b2FixtureDef fdb;
          fdb.density = 0.0f;
          fdb.restitution = 0.4f;
          fdb.shape = &shape1;
          (ibody->CreateFixture(&fdb))->SetFcolor(255,255,0,0.9);
          
          shape1.SetAsBox(r*1.0f, r*0.2f, r*b2Vec2(1.6f, 0.0f), 20*DEGTORAD);
          fdb.shape = &shape1;
          (ibody->CreateFixture(&fdb))->SetFcolor(255,255,0,0.9);

          shape1.SetAsBox(r*0.2f, r*0.7f, r*b2Vec2(-0.6f, 1.1f), 0);
          fdb.shape = &shape1;
          (ibody->CreateFixture(&fdb))->SetFcolor(255,255,0,0.9);
        }

        {
          b2BodyDef bd2;
          bd2.position.Set(x+r*-6.0f, y+r*19.0f);
          b2Body* ibody = m_world->CreateBody(&bd2);
          b2PolygonShape shape1;
          shape1.SetAsBox(r*0.2f, r*0.8f, b2Vec2(0.0f, 0.0f), -b2_pi/3);
          b2FixtureDef fdb;
          fdb.density = 0.0f;
          fdb.restitution = 0.4f;
          fdb.shape = &shape1;
          (ibody->CreateFixture(&fdb))->SetFcolor(255,255,0,0.9);
          
          shape1.SetAsBox(r*1.0f, r*0.2f, r*b2Vec2(-1.4f, 0.2f), -35*DEGTORAD);
          fdb.shape = &shape1;
          (ibody->CreateFixture(&fdb))->SetFcolor(255,255,0,0.9);

          shape1.SetAsBox(r*0.2f, r*0.7f, r*b2Vec2(0.6f, 1.1f), 0);
          fdb.shape = &shape1;
          (ibody->CreateFixture(&fdb))->SetFcolor(255,255,0,0.9);
        }

        //Horizontal shelf
        {
          b2PolygonShape shape;
          shape.SetAsBox(r*9.0f, r*0.25f, b2Vec2(0.0f,0.0f), 0.0f);
          b2BodyDef bd;
          bd.position.Set(x+r*16.0f, y+r*15.0f);
          b2Body* ground = m_world->CreateBody(&bd);
          (ground->CreateFixture(&shape, 0.0f))->SetFcolor(0,0,178,0.9);
        }

        //Dominos
        {
          b2PolygonShape shape;
          shape.SetAsBox(r*0.25f, r*2.0f);
      
          b2FixtureDef fd;
          fd.shape = &shape;
          fd.density = 10.0f;
          fd.friction = 0.3f;
        
          for (int i = 0; i < 8; ++i)
          {
            b2BodyDef bd;
            bd.type = b2_dynamicBody;
            bd.position.Set(x+r*(7.7f + 1.5f * i), y+r*17.0f);
            b2Body* body = m_world->CreateBody(&bd);
            (body->CreateFixture(&fd))->SetFcolor(255,145,0,1);
          }
        }

        //Sphere 
        {
          b2Body* sbody;
          b2CircleShape circle;
          circle.m_radius = r*1.5;
      
          b2FixtureDef ballfd;
          ballfd.shape = &circle;
          ballfd.density = 30.0f;
          ballfd.friction = 0.0f;
          ballfd.restitution = 0.3f;
          b2BodyDef ballbd;
          ballbd.type = b2_dynamicBody;
          ballbd.position.Set(x+r*22.5f, y+r*17.0f);
          sbody = m_world->CreateBody(&ballbd);
          (sbody->CreateFixture(&ballfd))->SetFcolor(255,215,0,0.95);
        }
      }
  }
      
}
