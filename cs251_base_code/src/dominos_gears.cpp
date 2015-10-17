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

#include <stdlib.h>
#include <time.h>
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
  dominos_t3::dominos_t3()
  {
    float32 x=15.0f;
    float32 y=16.0f;
    float32 r=0.9f;

  	{
  		float32 cradius = r*4.0;
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = cradius;
  
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 20.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(x+r*-4.8f, y+r*20.0f);
      sbody = m_world->CreateBody(&ballbd);
      (sbody->CreateFixture(&ballfd))->zsetcol(255,0,0,0.85);

      b2BodyDef bd2;
      bd2.position.Set(x+r*-4.8f, y+r*20.0f);
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
	      shape1.SetAsBox(r*0.6f, r*0.8f, 1.1*b2Vec2(cradius*sinf(ang), -cradius*cosf(ang)), ang);
	      b2FixtureDef fd3;
	      fd3.density = 0.5f;
	      fd3.shape = &shape1;
	      (sbody->CreateFixture(&fd3))->zsetcol(255,255,0,0.9);
  		}
    }

    {
  		float32 cradius = r*4.0;
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = cradius;
  
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 20.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(x+r*4.8f, y+r*20.0f);
      sbody = m_world->CreateBody(&ballbd);
      (sbody->CreateFixture(&ballfd))->zsetcol(255,0,0,0.85);

      b2BodyDef bd2;
      bd2.position.Set(x+r*4.8f, y+r*20.0f);
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
      	b2PolygonShape shape1;
	      shape1.SetAsBox(r*0.6f, r*0.8f, 1.1*b2Vec2(cradius*sinf(ang), -cradius*cosf(-ang)), ang);
	      b2FixtureDef fd3;
	      fd3.density = 0.5f;
	      fd3.shape = &shape1;
	      (sbody->CreateFixture(&fd3))->zsetcol(255,255,0,0.9);
  		}

    }



  }

}