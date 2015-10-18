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
  dominos_t1::dominos_t1()
  {
  	float32 x=30.0f;
    float32 y=40.0f;
    float32 r=0.9f;//Not Working

    //Up
 	  {
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
        (body->CreateFixture(fd))->zsetcol(139,0,139,0.9);

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
  	    (bbody->CreateFixture(&fdb))->zsetcol(0,255,0,0.9);
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
        (sbody1->CreateFixture(&ballfd))->zsetcol(0,0,255,0.85);
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
        (sbody2->CreateFixture(&ballfd))->zsetcol(255,0,0,0.85);
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
  	    (ibody->CreateFixture(&fdb))->zsetcol(255,255,0,0.9);
      	
      	shape1.SetAsBox(r*1.0f, r*0.2f, r*(1/0.9)*b2Vec2(1.6f, 0.0f), 20*DEGTORAD);
  	    fdb.shape = &shape1;
  	    (ibody->CreateFixture(&fdb))->zsetcol(255,255,0,0.9);

  	    shape1.SetAsBox(r*0.2f, r*0.7f, r*(1/0.9)*b2Vec2(-0.6f, 1.1f), 0);
  	    fdb.shape = &shape1;
  	    (ibody->CreateFixture(&fdb))->zsetcol(255,255,0,0.9);
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
  	    (ibody->CreateFixture(&fdb))->zsetcol(255,255,0,0.9);
      	
      	shape1.SetAsBox(r*1.0f, r*0.2f, r*(1/0.9)*b2Vec2(-1.4f, 0.2f), -35*DEGTORAD);
  	    fdb.shape = &shape1;
  	    (ibody->CreateFixture(&fdb))->zsetcol(255,255,0,0.9);

  	    shape1.SetAsBox(r*0.2f, r*0.7f, r*(1/0.9)*b2Vec2(0.6f, 1.1f), 0);
  	    fdb.shape = &shape1;
  	    (ibody->CreateFixture(&fdb))->zsetcol(255,255,0,0.9);
      }

      //Horizontal shelf
      {
        b2PolygonShape shape;
        shape.SetAsBox(r*9.0f, r*0.25f, b2Vec2(0.0f,0.0f), 0.0f);
        b2BodyDef bd;
        bd.position.Set(x+r*16.0f, y+r*15.0f);
        b2Body* ground = m_world->CreateBody(&bd);
        (ground->CreateFixture(&shape, 0.0f))->zsetcol(0,0,178,0.9);
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
          (body->CreateFixture(&fd))->zsetcol(255,145,0,1);
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
        (sbody->CreateFixture(&ballfd))->zsetcol(0,0,255,0.85);
      }
    }
    //EndUp

    //StepSPhSys
    {
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
          (stbody->CreateFixture(&myfd))->zsetcol(255,0,0,0.9f);
        }
        eshape.Set(b2Vec2(0,r1*-len),b2Vec2(r1*2*len,r1*-len));
        myfd.shape = &eshape;
        (stbody->CreateFixture(&myfd))->zsetcol(255,0,0,0.9f);
        for(int i=0; i<5; i++)
        {
          eshape.Set(b2Vec2(r1*(-len-len*i-lenhx*(i+1)),r1*-len*i),b2Vec2(r1*(-len-len*i-lenhx*(i+1)),r1*(-len-len*i)));
          myfd.shape = &eshape;
          (stbody->CreateFixture(&myfd))->zsetcol(255,0,0,0.9f);
        }
        eshape.Set(b2Vec2(0,0),b2Vec2(0,r1*-len));
        myfd.shape = &eshape;
        (stbody->CreateFixture(&myfd))->zsetcol(255,0,0,0.9f);
        eshape.Set(b2Vec2(r1*2*len,0),b2Vec2(r1*2*len,r1*-len));
        myfd.shape = &eshape;
        (stbody->CreateFixture(&myfd))->zsetcol(255,0,0,0.9f);
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
          (sbody1->CreateFixture(&ballfd))->zsetcol(0,0,255,0.85);
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
          (sbody2->CreateFixture(&ballfd))->zsetcol(255,0,0,0.85);
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
    //End StepSphSys

    //In
    {
      float32 xin=x;
      float32 yin=y;
      float32 rin=r;

      {
        float32 len=rin*10.0f;
        b2Body* inbody;
        b2BodyDef ballbd;
        b2FixtureDef myfd;
        b2PolygonShape pshape; 
        ballbd.position.Set(xin+rin*-38.0f, yin+rin*-18.0f);
        inbody = m_world->CreateBody(&ballbd);
        pshape.SetAsBox(len, rin*0.3f, b2Vec2(-len, 0.0f), 0);
        myfd.shape = &pshape;
        (inbody->CreateFixture(&myfd))->zsetcol(0,0,255,0.9f);
        pshape.SetAsBox(len, rin*0.3f, b2Vec2(-len*3.828f/1.414f, len/1.414f), -b2_pi/4);
        myfd.shape = &pshape;
        (inbody->CreateFixture(&myfd))->zsetcol(0,0,255,0.9f);
      }

      //In Sphere
      {
        b2Body* sbody;
        b2CircleShape circle;
        circle.m_radius = rin*2.0f;
    
        b2FixtureDef ballfd;
        ballfd.shape = &circle;
        ballfd.density = 8.0f;
        ballfd.friction = 0.0f;
        ballfd.restitution = 0.0f;
        b2BodyDef ballbd;
        ballbd.type = b2_dynamicBody;
        ballbd.position.Set(xin+rin*-70, yin+rin*0.0f);
        sbody = m_world->CreateBody(&ballbd);
        (sbody->CreateFixture(&ballfd))->zsetcol(255,255,0,0.85);
      }

    }
    //End In

    //Gear
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
        (sbody->CreateFixture(&ballfd))->zsetcol(255,0,0,0.85);

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
          (sbody->CreateFixture(&fd3))->zsetcol(255,255,0,0.9);
        }
        ang=5*ang_inc/2;
        b2PolygonShape shape1;
        b2FixtureDef fd3;
        fd3.density = 0.0f;
        shape1.SetAsBox(rg*0.4f, rg*6.6f, 2.6*b2Vec2(c_rad*sinf(ang), -c_rad*cosf(ang)), ang);
        fd3.shape = &shape1;
        (sbody->CreateFixture(&fd3))->zsetcol(255,255,0,0.9);
        shape1.SetAsBox(rg*1.8f, rg*0.35f, 1.5*b2Vec2(c_rad*sinf(ang+ang_inc*0.4f), -c_rad*cosf(ang+ang_inc*0.4f)), ang);
        fd3.shape = &shape1;
        (sbody->CreateFixture(&fd3))->zsetcol(255,255,0,0.9);
        shape1.SetAsBox(rg*1.8f, rg*0.35f, 4.2*b2Vec2(c_rad*sinf(ang+ang_inc*0.2f), -c_rad*cosf(ang+ang_inc*0.2f)), ang);
        fd3.shape = &shape1;
        (sbody->CreateFixture(&fd3))->zsetcol(255,255,0,0.9);
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
        (sbody->CreateFixture(&ballfd))->zsetcol(255,0,0,0.85);

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
          (sbody->CreateFixture(&fd3))->zsetcol(255,255,0,0.9);
        }

        {
          b2PolygonShape shape1;
          shape1.SetAsBox(rg*0.3f, rg*7.5f, rg*b2Vec2(-3.0f, -13.0f), b2_pi/3);
          b2FixtureDef fdb;
          fdb.density = 65.0f;
          fdb.restitution = 0.4f;
          fdb.shape = &shape1;
          (sbody->CreateFixture(&fdb))->zsetcol(0,0,255,0.9);

          b2EdgeShape eshape; 
          eshape.Set(b2Vec2(0,0),b2Vec2(rg*-7.5f,rg*-10.5f));
          b2FixtureDef myfd;
          myfd.shape = &eshape;
          myfd.density = 0.0f;
          myfd.filter.maskBits = 0x0000;
          (sbody->CreateFixture(&myfd))->zsetcol(255,0,0,0.9f);
        }

      }
      //Cog3
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
        ballbd.position.Set(xg+rg*4.7f, yg+rg*20.0f);
        sbody = m_world->CreateBody(&ballbd);
        (sbody->CreateFixture(&ballfd))->zsetcol(255,0,0,0.85);

        b2BodyDef bd2;
        bd2.position.Set(xg+rg*4.7f, yg+rg*20.0f);
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
          shape1.SetAsBox(rg*0.6f, rg*0.8f, 1.1*b2Vec2(c_rad*sinf(ang), -c_rad*cosf(ang)), ang);
          b2FixtureDef fd3;
          fd3.density = 0.0f;
          fd3.shape = &shape1;
          (sbody->CreateFixture(&fd3))->zsetcol(255,255,0,0.9);
        }

        {
          b2PolygonShape shape1;
          shape1.SetAsBox(rg*0.3f, rg*8.0f, rg*b2Vec2(3.0f, -13.0f), -b2_pi/3);
          b2FixtureDef fdb;
          fdb.density = 70.0f;
          fdb.restitution = 0.4f;
          fdb.shape = &shape1;
          (sbody->CreateFixture(&fdb))->zsetcol(0,0,255,0.9);

          b2EdgeShape eshape; 
          eshape.Set(b2Vec2(0,0),b2Vec2(rg*7.5f,rg*-10.5f));
          b2FixtureDef myfd;
          myfd.shape = &eshape;
          myfd.density = 0.0f;
          myfd.filter.maskBits = 0x0000;
         (sbody->CreateFixture(&myfd))->zsetcol(255,0,0,0.9f);
        }
      }
    }
    //Endgear

    //D2
    {
      float32 xd=x;
      float32 yd=y+r*2.5f;
      float32 rd=r;

      //Horizontal shelf
      {
        b2PolygonShape shape;
        shape.SetAsBox(rd*35.0f, rd*0.30f);
        b2BodyDef bd;
        bd.position.Set(xd+rd*-34.0f, yd+rd*-50.0f);
        b2Body* ground = m_world->CreateBody(&bd);
        (ground->CreateFixture(&shape, 0.0f))->zsetcol(0,0,178,0.9);
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
          bd.position.Set(xd+rd*(-19.3f - 2.2f * i), yd+rd*(-43.0f-0.35f*i));
          b2Body* body = m_world->CreateBody(&bd);
          (body->CreateFixture(&fd))->zsetcol(255,145,0,1);
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
        (body->CreateFixture(fd))->zsetcol(139,0,139,0.9);

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
        (body->CreateFixture(fd))->zsetcol(139,0,139,0.9);
        shape.SetAsBox(rd*0.5f, rd*0.3f, rd*b2Vec2(0.5f, 8.75f), 0);
        fd->density = 0.0f;
        fd->shape = &shape;
        (body->CreateFixture(fd))->zsetcol(139,0,139,0.9);

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
        (sbody->CreateFixture(&ballfd))->zsetcol(0,255,0,0.85);
      }

      {
        b2Body* sbody;
        b2CircleShape circle;
        circle.m_radius = rd*2.0;
    
        b2FixtureDef ballfd;
        ballfd.shape = &circle;
        ballfd.density = 20.0f;
        ballfd.friction = 0.4f;
        ballfd.restitution = 0.2f;
        b2BodyDef ballbd;
        ballbd.type = b2_dynamicBody;
        ballbd.position.Set(xd+rd*-6.0f, yd+rd*-47.0f);
        sbody = m_world->CreateBody(&ballbd);
        (sbody->CreateFixture(&ballfd))->zsetcol(0,255,0,0.85);
      }
    }
    //End D2

    //Key
    {
      float32 xk=x;
      float32 yk=y;
      float32 rk=r;

      //ssbase
      {
        b2BodyDef bd;
        bd.position.Set(xk+rk*-39.0f, yk+rk*6.0f);
        b2Body* body = m_world->CreateBody(&bd);
        b2PolygonShape shape;
        shape.SetAsBox(rk*12.0f, rk*0.3f, rk*b2Vec2(-11.0f,0.0f), 0.0f);
        b2FixtureDef fdb;
        fdb.density = 0.5f;
        fdb.shape = &shape;
        (body->CreateFixture(&fdb))->zsetcol(255,255,0,0.9);
        shape.SetAsBox(rk*0.25f, rk*1.0f, rk*b2Vec2(1.0f,0.6f), 0.0f);
        fdb.shape = &shape;
        (body->CreateFixture(&fdb))->zsetcol(255,255,0,0.9);
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
        (body->CreateFixture(&fdb))->zsetcol(255,0,255,0.9);

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
        (sbody->CreateFixture(&ballfd))->zsetcol(0,255,0,0.85);
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
        (body->CreateFixture(fd))->zsetcol(139,0,139,0.9);
        shape.SetAsBox(rk*0.5f, rk*0.3f, rk*b2Vec2(-0.5f, 17.75f), 0);
        fd->density = 0.0f;
        fd->shape = &shape;
        (body->CreateFixture(fd))->zsetcol(139,0,139,0.9);

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
        (body->CreateFixture(fd))->zsetcol(139,0,139,0.9);
        
        b2BodyDef bd2;
        bd2.position.Set(xk+rk*-46.0f, yk+rk*7.5f);
        b2Body* body2 = m_world->CreateBody(&bd2);
        b2FixtureDef *fd2 = new b2FixtureDef;
        shape.SetAsBox(rk*0.2f, rk*1.5f); 
        fd2->shape = &shape;
        (body2->CreateFixture(fd2))->zsetcol(139,0,139,0.9);

        b2BodyDef bd3;
        bd3.type = b2_dynamicBody;
        bd3.position.Set(xk+rk*-56.0f, yk+rk*10.6f);
        b2Body* body3 = m_world->CreateBody(&bd3);
        shape.SetAsBox(rk*1.5f, rk*1.5f); 
        b2FixtureDef *fd3 = new b2FixtureDef;
        fd3->density = 7.0f;
        fd3->friction = 1.0f;
        fd3->shape = &shape;
        (body3->CreateFixture(fd3))->zsetcol(0,139,0,0.9);

        b2RevoluteJointDef jointDef;
        jointDef.bodyA = body;
        jointDef.bodyB = body2;
        jointDef.localAnchorA.Set(rk*4,0);
        jointDef.localAnchorB.Set(0,rk*1.5);
        jointDef.collideConnected = false;
        m_world->CreateJoint(&jointDef);
      }

    }
    //End Key
  }
}