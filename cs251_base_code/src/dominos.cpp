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
        float32 xd=x;
        float32 yd=y+r*2.5f/0.9f;
        float32 rd=r;

        //Horizontal shelf
        {
          b2PolygonShape shape;
          shape.SetAsBox(rd*35.0f, rd*0.30f);
          b2BodyDef bd;
          bd.position.Set(xd+rd*-34.0f, yd+rd*-50.0f);
          b2Body* ground = m_world->CreateBody(&bd);
          (ground->CreateFixture(&shape, 0.0f))->SetFcolor(0,0,178,0.9);
          //Slope
          b2EdgeShape eshape;
          b2FixtureDef fd;
          fd.shape = &eshape;
          eshape.Set(b2Vec2(xd+rd*7.5f,yd+rd*-32.5f),b2Vec2(xd+rd*15.5f,yd+rd*-32.5f));      
          (ground->CreateFixture(&fd))->SetFcolor(0,0,178,0.9f);

        }

        //Dominos
        {
          b2PolygonShape shape;
          b2BodyDef bd;
          bd.type = b2_dynamicBody;    
          b2FixtureDef fd;
          fd.density = 35.0f;
          fd.friction = 0.3f;
        
          for (int i = 0; i < 10; ++i)
          {
            shape.SetAsBox(rd*0.35f, rd*(6.0f-0.4f*i));
            if(i==0)shape.SetAsBox(rd*0.45f, rd*(6.0f-0.4f*i));
            fd.shape = &shape;
            bd.position.Set(xd+rd*(-19.4f - 2.2f * i), yd+rd*(-43.0f-0.35f*i));
            b2Body* body = m_world->CreateBody(&bd);
            (body->CreateFixture(&fd))->SetFcolor(255,215,0,0.9);
          }
        }

        //Revolving H platform
        {
          b2PolygonShape shape;
          shape.SetAsBox(rd*2.0f, rd*0.2f);    
          b2BodyDef bd;
          bd.position.Set(xd+rd*-56, yd+rd*-35.0f);
          bd.type = b2_dynamicBody;
          b2Body* body = m_world->CreateBody(&bd);
          b2FixtureDef *fd = new b2FixtureDef;
          fd->density = 1.0f;
          fd->shape = &shape;
          (body->CreateFixture(fd))->SetFcolor(139,0,139,0.9);

          b2BodyDef bd2;
          bd2.position.Set(xd+rd*-56, yd+rd*-35.0f);
          b2Body* body2 = m_world->CreateBody(&bd2);

          b2RevoluteJointDef jointDef;
          jointDef.bodyA = body;
          jointDef.bodyB = body2;
          jointDef.localAnchorA.Set(0,0);
          jointDef.localAnchorB.Set(0,0);
          jointDef.collideConnected = false;
          m_world->CreateJoint(&jointDef);
        }

        //Revolving V platform
        {
          b2PolygonShape shape;
          shape.SetAsBox(rd*0.2f, rd*9.0f);    
          b2BodyDef bd;
          bd.position.Set(xd+rd*-60.5, yd+rd*-40.0f);
          bd.type = b2_dynamicBody;
          b2Body* body = m_world->CreateBody(&bd);
          b2FixtureDef *fd = new b2FixtureDef;
          fd->density = 1.0f;
          fd->shape = &shape;
          (body->CreateFixture(fd))->SetFcolor(139,0,139,0.9);
          shape.SetAsBox(rd*0.5f, rd*0.3f, rd*b2Vec2(0.5f, 8.75f), 0);
          fd->density = 0.0f;
          fd->shape = &shape;
          (body->CreateFixture(fd))->SetFcolor(139,0,139,0.9);

          b2BodyDef bd2;
          bd2.position.Set(xd+rd*-60.5, yd+rd*-40.0f);
          b2Body* body2 = m_world->CreateBody(&bd2);

          b2RevoluteJointDef jointDef;
          jointDef.bodyA = body;
          jointDef.bodyB = body2;
          jointDef.localAnchorA.Set(0,0);
          jointDef.localAnchorB.Set(0,0);
          jointDef.collideConnected = false;
          m_world->CreateJoint(&jointDef);
        }

        //The heavy sphere on the platform
        {
          b2Body* sbody;
          b2CircleShape circle;
          circle.m_radius = rd*3.0;
      
          b2FixtureDef ballfd;
          ballfd.shape = &circle;
          ballfd.density = 10.0f;
          ballfd.friction = 0.4f;
          ballfd.restitution = 0.2f;
          b2BodyDef ballbd;
          ballbd.type = b2_dynamicBody;
          ballbd.position.Set(xd+rd*-56, yd+rd*-31.0f);
          sbody = m_world->CreateBody(&ballbd);
          (sbody->CreateFixture(&ballfd))->SetFcolor(128,128,0,0.85);
        }
        //Into end sph
        {
          b2Body* sbody;
          b2CircleShape circle;
          circle.m_radius = rd*2.0;
      
          b2FixtureDef ballfd;
          ballfd.shape = &circle;
          ballfd.density = 10.0f;
          ballfd.friction = 0.2f;
          ballfd.restitution = 0.2f;
          b2BodyDef ballbd;
          ballbd.type = b2_dynamicBody;
          ballbd.position.Set(xd+rd*-6.3f, yd+rd*-47.0f);
          sbody = m_world->CreateBody(&ballbd);
          insphere = sbody;
          (sbody->CreateFixture(&ballfd))->SetFcolor(139,69,19,0.9);
        }
      }
  }
      
}
