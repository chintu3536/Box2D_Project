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
    //Ground
    /*! \var b1
     * \brief pointer to the body ground
     */
    b2Body* b1;
    {

      b2PolygonShape shape1,shape2;
      shape1.SetAsBox(40.0f, 0.25f);
      b2BodyDef bd;
      bd.position.Set(0.0f, 0.0f);
      b1= m_world->CreateBody(&bd);
      b1->CreateFixture(&shape1, 0.0f);
    }
        b2Body* rbody;
      {
      b2PolygonShape shape;
      b2Vec2 vertices[3];
      vertices[0].Set(20.0f, 12.0f);
      vertices[1].Set(20.0f, 0.0f);
      vertices[2].Set(0.0f, 0.0f);
      int32 count = 3;
      shape.Set(vertices, count);
      //shape.SetAsBox(20.0f,1.5f);
      b2BodyDef bd;
      //bd.type=b2_dynamicBody;
      //bd.position.Set(14.0f,5.0f);
      rbody= m_world->CreateBody(&bd);
      rbody->CreateFixture(&shape, 0.0f);
      }
      b2Body* sbody1;
      {
      b2CircleShape circle;
      circle.m_radius = 1.0;
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 50.0f;
      ballfd.friction = 0.5f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(-4.1f, 48.0f);
      sbody1 = m_world->CreateBody(&ballbd);
      sbody1->CreateFixture(&ballfd);
      }
      {
      b2Body *sbody2, *sbody3;
      {
      b2CircleShape circle;
      circle.m_radius = 5.0;
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 1.0f;
      ballfd.friction = 0.01f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.position.Set(-20.0f, 15.0f);
      ballbd.type=b2_dynamicBody;
      ballbd.fixedRotation=true;
      sbody2 = m_world->CreateBody(&ballbd);
      sbody2->CreateFixture(&ballfd);
      ballbd.position.Set(-10.0f, 15.0f);
      sbody3 = m_world->CreateBody(&ballbd);
      sbody3->CreateFixture(&ballfd);
      }

      b2Body *sbody4, *sbody5;
      {
      b2CircleShape circle;
      circle.m_radius = 0.5;
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 50.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.position.Set(-20.0f, 15.0f);
      //ballbd.type=b2_dynamicBody;
      ballbd.fixedRotation=true;
      sbody4 = m_world->CreateBody(&ballbd);
      sbody4->CreateFixture(&ballfd);
      ballbd.position.Set(-10.0f, 15.0f);
      sbody5 = m_world->CreateBody(&ballbd);
      sbody5->CreateFixture(&ballfd);
      }
      /*b2Body* rbody;
      {
      b2PolygonShape shape;
      shape.SetAsBox(5.0f, 0.25f);
      b2BodyDef bd;
      bd.type=b2_dynamicBody;
      bd.position.Set(0.0f,15.0f);
      rbody= m_world->CreateBody(&bd);
      rbody->CreateFixture(&shape, 0.0f);
      }*/
      b2RevoluteJointDef jointDef;
      jointDef.bodyA = sbody2;
      jointDef.bodyB = sbody4;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
      jointDef.bodyA = sbody3;
      jointDef.bodyB = sbody5;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
      /*distance_joint->bodyA = sbody3;
      distance_joint->bodyB = rbody;
      distance_joint->length=10.0f;
      distance_joint->frequencyHz = 0.0f;
      distance_joint->dampingRatio = 0.0f;
      m_world->CreateJoint(distance_joint);*/
      }
      {
      b2PolygonShape shape;
      shape.SetAsBox(2.2f, 0.2f);

      b2BodyDef bd;
      bd.position.Set(14.0f, 14.0f);
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
      bd2.position.Set(14.0f, 16.0f);
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
    float32 x=25.0f;
    float32 y=25.0f;
    float32 r=0.5f;
    {
      b2Body* rbody;
      b2PolygonShape shape;
      int xoff=0,yoff=0,k=4,l=0;
      for(l=1;l<9;l=l+2)
      {
      shape.SetAsBox(r, 0.125, b2Vec2(xoff,yoff), -11/(14.0));
      b2FixtureDef wedgefd;
      wedgefd.shape = &shape;
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 1.0f;
      b2BodyDef wedgebd;
      wedgebd.position.Set(x,y);
      rbody = m_world->CreateBody(&wedgebd);
      (rbody->CreateFixture(&wedgefd));

      shape.SetAsBox(r, 0.125, b2Vec2(xoff+l*r*k,yoff+l*r*k), -11/(14.0));
      wedgefd.shape = &shape;
      (rbody->CreateFixture(&wedgefd));

      shape.SetAsBox(r, 0.125, b2Vec2(xoff+l*r*k,yoff), 11/(14.0));
       wedgefd.shape = &shape;
      (rbody->CreateFixture(&wedgefd));

      shape.SetAsBox(r, 0.125, b2Vec2(xoff-r*k,yoff+l*r*k), 11/(14.0));
       wedgefd.shape = &shape;
      (rbody->CreateFixture(&wedgefd));

      xoff=xoff-r*k;
      yoff=yoff-r*k;
      }
    {
      b2Body* rbody;
      b2PolygonShape shape;
      shape.SetAsBox(r*2, 0.125, b2Vec2(x+r,y+5*r*k), -22/(21.0));
      b2FixtureDef wedgefd;
      wedgefd.shape = &shape;
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 3.0f;
      b2BodyDef wedgebd;
      rbody = m_world->CreateBody(&wedgebd);
      (rbody->CreateFixture(&wedgefd));
    }
    {
        b2Body *sp_gless;
        b2CircleShape circle;
        circle.m_radius = 0.5*r;
        b2FixtureDef sp_gless_fix;
        sp_gless_fix.shape=&circle;
        sp_gless_fix.density=10.0f;
        sp_gless_fix.friction = 0.0f;
        sp_gless_fix.restitution = 1.0f;
        b2BodyDef sp;
        sp.type=b2_dynamicBody;
        sp.position.Set(x+(l/2)*r*k, y);
        sp_gless=m_world->CreateBody(&sp);
        sp_gless->SetGravityScale(0);
        sp_gless->ApplyLinearImpulse( b2Vec2(0,-20), sp_gless->GetPosition(), true);
        (sp_gless->CreateFixture(&sp_gless_fix));

        /*circle.m_radius = r;
        sp_gless_fix.shape=&circle;
        sp.position.Set(x+(l/2)*r*k, y+2*r);
        sphere=m_world->CreateBody(&sp);
        (sphere->CreateFixture(&sp_gless_fix))->zsetcol(255,99,71,0.8);*/

    }
    }
}
  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
