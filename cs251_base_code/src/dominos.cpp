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
      ballbd.position.Set(14.0f, 48.0f);
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
      ballfd.friction = 0.1f;
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
      b2DistanceJointDef *distance_joint;
      distance_joint = new b2DistanceJointDef();
      distance_joint->bodyA = sbody2;
      distance_joint->bodyB = sbody4;
      distance_joint->length=0.0f;
      distance_joint->frequencyHz = 0.0f;
      distance_joint->dampingRatio = 0.0f;
      m_world->CreateJoint(distance_joint);
      distance_joint->bodyA = sbody3;
      distance_joint->bodyB = sbody5;
      distance_joint->length=0.0f;
      distance_joint->frequencyHz = 0.0f;
      distance_joint->dampingRatio = 1.0f;
      m_world->CreateJoint(distance_joint);
      distance_joint->bodyA = sbody3;
      distance_joint->bodyB = rbody;
      distance_joint->length=10.0f;
      distance_joint->frequencyHz = 0.0f;
      distance_joint->dampingRatio = 0.0f;
      m_world->CreateJoint(distance_joint);
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
  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
