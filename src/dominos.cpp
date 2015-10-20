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
  /**  The is the constructor 
   * This is the documentation block for the constructor.
   */ 
  //Extern Vars
   b2Body* bsensor;
	 b2Body* insphere;
	 b2Body* cannonbutton;
	 b2Body* stopbutton;
   b2Body* mazesphere;
   b2Body* rplatform;
	 b2Body* cannonball1;
	 b2Body* cannonball2;
	 b2Body* cannonball3;
	 b2Body* car2;
   
  dominos_t1::dominos_t1()
  {
  	 
  	/**
  	* Ground: shape is a variable of type b2PolygonShape which defines the shape of the body ground in the simulation.
    * bd is of type b2BodyDef which contains all the information needed to create a body.
  	* 
  	* Car: It contains 10 fixtures out of which 4 are circles and 6 are rectangles.The wheels are attached to the body
  	* using distance joints.jointdef is of type b2DistanceJointDef which defines the joint between the wheels and body.
    * anchor is of type b2Vec2 which is a vector containg the position of pendulum joint.
    * jd is initialized between the pendulum and the horizontal shelf.
		*
  	* The Revolving Vertical platform: shape is a variable of type b2PolygonShape which defines the shape of the pendulum body.
    * This variable defines a rectangle of size 4.4X0.3 m^2.bd is of type b2BodyDef and defines revolving horizontal platform
    * and the position is set to (14,14).Type of bd is set to b2_dynamicBody.fd is of type b2FixtureDef which defines 
    * the physical properties of revolving horizontal platform. Density, friction are set to 1,0.
    * shape2 and bd2 are b2PolygonShape and b2BodyDef and they define a body with no fixtures to which the joint is connected.
    * shape2 defines a rectangle of size 0.2X2 m^2.
    * jointDef is of type b2RevoluteJointDef and defines joint between the 2 bodies mentioned above.
  	*	Another body is attached at the end of this body using b2RevoluteJoint which inturn is attached to
  	* one of the pistons.
  	*
  	* Pistons: They are connected using b2PulleyJoints.shape is a variable of type b2PolygonShape which defines the shape of the
  	* pendulum body.This variable defines a rectangle of size 0.4X8 m^2.The two objects are connected using pulleyjoints 
  	* to act as pistons.  	
		*
		*	Box connected to Wheels: 2 Circles are connected above the box to act as wheels for the box.The wheels are connected using 
		* DIstanceJoints and the wheels are connected to boxes using Rope Joint.sbody is of type b2Body* and circle is of type
		* b2CircleShape.The radius of circle is set to 1.6.ballfd is of type b2FixtureDef which defines the properties of 
    * the heavy sphere and the density, restitution, friction are set to 50, 0, 1 respectively.
    * Type of ballfd is set to b2_dynamicBody and position is set to (14,18).
		*
		* The revolving horizontal platform: shape is a variable of type b2PolygonShape which defines the shape of platform.
    * This variable defines a rectangle of size 4.0X0.2 m^2.bd is of type b2BodyDef and defines revolving horizontal platform
    * and the position is set to (14,14).Type of bd is set to b2_dynamicBody.fd is of type b2FixtureDef which defines 
    * the physical properties of revolving horizontal platform. Density, friction are set to 1,0.
    * shape2 and bd2 are b2PolygonShape and b2BodyDef and they define a body with no fixtures to which the joint is connected.
    * shape2 defines a rectangle of size 0.2X2 m^2 and position is set to (14,16).
    * jointDef is of type b2RevoluteJointDef and defines joint between the 2 bodies mentioned above.
 		*
    * Horizontal Shelf: shape is a variable of type b2PolygonShape which defines the shape of the top horizontal shelf.
    * This variable defines a rectangle of size 12X0.5 m^2.
    * The position of the body is set to (-31,30).
    *
    * Dominos: shape is a variable of type b2PolygonShape which defines the shape of the dominos blocks.
    * This variable defines a rectangle of size 2X0.2 m^2.
    * fd is of type b2FixtureDef which defines the physical properties of dominos.
    * The density and friction are set to 20 and 0.1 respectively.
    * The type of the variable bd is set to b2_dynamicBody.
    * The position of i-th block is (-35.5+i,31.25).
    * 
		* 2 spheres connected by a rope: sbody1,sbody2 are of type b2Body* and circle is of type b2CircleShape.
    * The radius of circle is set to 0.5. ballfd is of type b2FixtureDef which defines the properties of 
    * the spheres and the density, restitution, friction are set to 5, 0, 0 respectively.
    * The 2 spheres are connected using b2RopeJoints.
    *
		* Small platforms for Spheres: shape is a variable of type b2PolygonShape which defines the shape of the platforms.
    * This variable defines a rectangle of size 2.0X0.4 m^2.
    *  
  	* Steps: eshape is a variable of type b2EdgeShape and stbody is a variable of type b2Body* which points to the body
  	* steps.
  	* Another 2 spheres connected by a rope: sbody1,sbody2 are of type b2Body* and circle is of type b2CircleShape.
    * The radius of circle is set to 0.5. ballfd is of type b2FixtureDef which defines the properties of 
    * the spheres and the density, restitution, friction are set to 5, 0, 0 respectively.
    * The 2 spheres are connected using b2RopeJoints.
  	* 
  	* Sphere entering the gear system: sbody is of type b2Body* and circle is of type b2CircleShape.
    * The radius of circle is set to 1.6.ballfd is of type b2FixtureDef which defines the properties of 
    * the heavy sphere and the density, restitution, friction are set to 50, 0, 1 respectively.
    * Type of ballfd is set to b2_dynamicBody and position is set to (20,-12).
  	*
  	*	Another set of Dominos with varying heights: shape is a variable of type b2PolygonShape which defines the shape of 
  	* the dominos blocks.This variable defines a rectangle of size (4-0.2*i)X0.25 m^2 where i corresponds to i-th block.
    * fd is of type b2FixtureDef which defines the physical properties of dominos.
    * The density and friction are set to 120 and 0.1 respectively.
    * The type of the variable bd is set to b2_dynamicBody.
    * The position of i-th block is (-3+1.2*i,2.0).
  	*
  	* Another revolving horizontal platform: shape is a variable of type b2PolygonShape which defines the shape of the pendulum body.
    * This variable defines a rectangle of size 4.4X0.4 m^2.bd is of type b2BodyDef and defines revolving horizontal platform
    * and the position is set to (6.5,16).Type of bd is set to b2_dynamicBody.fd is of type b2FixtureDef which defines 
    * the physical properties of revolving horizontal platform. Density, friction are set to 1,0.
    * shape2 and bd2 are b2PolygonShape and b2BodyDef and they define a body with no fixtures to which the joint is connected.
    * shape2 defines a rectangle of size 0.2X2 m^2 and position is set to (6.5,16).
    * jointDef is of type b2RevoluteJointDef and defines joint between the 2 bodies mentioned above.
    *
    * Another Vertical Platform: 
  	* shape is a variable of type b2PolygonShape which defines the shape of the pendulum body.
    * This variable defines a rectangle of size 0.6X8.0 m^2.bd is of type b2BodyDef and defines revolving horizontal platform
    * and the position is set to (6.5,16).Type of bd is set to b2_dynamicBody.fd is of type b2FixtureDef which defines 
    * the physical properties of revolving horizontal platform. Density, friction are set to 10,0.
    * shape2 and bd2 are b2PolygonShape and b2BodyDef and they define a body with no fixtures to which the joint is connected.
    * shape2 defines a rectangle of size 0.2X2 m^2 and position is set to (2.5,-20).
    * jointDef is of type b2RevoluteJointDef and defines joint between the 2 bodies mentioned above.
    *
    * The see-saw system: (1)The triangular wedge: sbody is of type b2Body* and poly is of type b2PolygonShape.
    * vertices[3] is an array of type b2Vec2 which stores the coordinates of the vertices of the triangular wedge.
    * wedgefd is of type b2FixtureDef and the density, restitution, friction of the wedge are set to 10,0,0.
    * position of the wedge is set to (30,0). (2)Plank on top the wedge: shape is a variable of type b2PolygonShape 
    * which defines the shape of the plank. This variable defines a rectangle of size 30X0.4 m^2.
    * bd2 is of type b2BodyDef and position of the body is set to (30,0.6).jointDef is of type b2RevoluteJointDef
    * and defines the joint between wedge and plank at (30,0.6). (3)The light box on the see-saw:
    * shape2 is a variable of type b2PolygonShape which defines the shape of the lightbox.
    * bd2 is of type b2BodyDef and position of the body is set to (40,2). fd3 is of type b2FixtureDef which defines the properties of 
    * light box and density is set to 0.01.
    * body3 is of type b2Body*.
    *
    * The Gear System: This consists of three cogs placed side by side. 2 of these form a container to hold a body
    * while the third helps in opening it when weights are added to it.
    * sbody is of type b2Body* and circle is of type b2CircleShape.
    * The radius of circle is set to 0.9.ballfd is of type b2FixtureDef which defines the properties of 
    * the heavy sphere and the density, restitution, friction are set to 5, 0, 0 respectively.
    * Type of ballfd is set to b2_dynamicBody and position is set to (-44,2).
    * 
    * Ground: shape is a variable of type b2EdgeShape which defines the shape of the body ground in the simulation.
    * The start and end coordinates of this shape are set to (-60,0),(70,0).
    * bd is of type b2BodyDef which contains all the information needed to create a body.
    *
    * It also contains another copy of the car described above.
    *
    * Maze:shape is a variable of type b2EdgeShape which defines the shape of the edges in the maze.Two boolean arrays
    * are used to know if an edge exists at a given location.
    * bd is of type b2BodyDef which contains all the information needed to create a body.
    * Solve the maze using the mouse and push the blue button at the end to stop firing the cannon.
    *
    * Sphere in the maze:This sphere has the ability to form a mousejoint.Move this sphere and solve the maze
    * to escape from the cannon fire.
    *
    * Cannon:Cannon is made using circles and various polygons.fd is of type b2FixtureDef which defines the physical 
    * properties of cannon.The density and friction are set to 20 and 0.1 respectively.
    * The type of the variable bd is set to b2_dynamicBody.
		*
    *	Cannonballs:sbody is of type b2Body* and circle is of type b2CircleShape.
    * The radius of circle is set to 1.0.ballfd is of type b2FixtureDef which defines the properties of 
    * the heavy sphere and the density, restitution, friction are set to 50, 0, 1 respectively.
    * Type of ballfd is set to b2_dynamicBody.
    *
    *	Buttons And Sensor:
    * The Red button is used to fire the cannon and Blue is used to stop the sphere from pressing the red button.
  	*/

 		//d begin
	  {
	  	float32 x=-120.0f;
	    float32 y=7.0f;
	    float32 r=1.0f;

	    //Ground
	    {
	      b2BodyDef bd;
	      bd.position.Set(x+r*0.0f, y+r*0.0f);
	      b2Body* gbody = m_world->CreateBody(&bd);
	      b2PolygonShape shape1;
	      shape1.SetAsBox(r*40.0f, r*8.0f, r*b2Vec2(-23.0f, -4.0f), 0);
	      b2FixtureDef fdb;
	      fdb.shape = &shape1;
	      (gbody->CreateFixture(&fdb))->SetFcolor(124,255,0,0.9,1);
	      
	      shape1.SetAsBox(r*20.0f, r*6.0f, r*b2Vec2(32.6f, -9.7f), -24*DEGTORAD);
	      fdb.shape = &shape1;
	      (gbody->CreateFixture(&fdb))->SetFcolor(124,255,0,0.9,1);
	    }

	    //Car
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

	    //Pistons
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
	      //Stat
	      {
	        float32 yr=y+r*(30-2*1.404);
	        //up piston
	        b2PolygonShape shape;
	        shape.SetAsBox(r*4.0f, r*1.5f);    
	        b2BodyDef bd2;
	        bd2.position.Set(x+r*-1.0f, yr+r*7.5f);
	        bd2.type = b2_dynamicBody;
	        b2Body* body4 = m_world->CreateBody(&bd2);
	        b2FixtureDef *fd = new b2FixtureDef;
	        fd->density = 10.0f;
	        fd->friction = 0.2f;
	        fd->shape = &shape;
	        (body4->CreateFixture(fd))->SetFcolor(139,0,139,1.0);

	        fd->density = 0.0f;
	        fd->friction = 0.0f;
	        shape.SetAsBox(r*5.0f, r*0.32f, b2Vec2(r*8.0f,0.0f), 0);        
	        (body4->CreateFixture(fd))->SetFcolor(139,0,139,1.0);
	        shape.SetAsBox(r*2.0f, r*1.5f, b2Vec2(r*15.0f,0.0f), 0);
	        (body4->CreateFixture(fd))->SetFcolor(139,0,139,1.0);
	        //end up
	        b2BodyDef bd;
	        b2Body* bbody = m_world->CreateBody(&bd);
	        b2EdgeShape eshape; 
	        b2FixtureDef myfd;
	        myfd.shape = &eshape;
	        myfd.density = 0.0f;

	        //Joint
	        b2PulleyJointDef* myjoint = new b2PulleyJointDef();
	        myjoint->Initialize(body3, body4, b2Vec2(x+r*-16.0f,yr+r*0.0f), b2Vec2(x+r*-16.0f,yr+r*7.5f), 
	        body3->GetWorldCenter()+b2Vec2(r*-4.5f,0.0f), body4->GetWorldCenter()+b2Vec2(r*-4.0f,0.0f), 1.0f);
	        m_world->CreateJoint(myjoint);

	        eshape.Set(b2Vec2(x+r*2.0f,yr-r*2.0f),b2Vec2(x+r*-18.0f,yr-r*2.0f));      
	        (bbody->CreateFixture(&myfd))->SetFcolor(255,0,0,0.9f);
	        eshape.Set(b2Vec2(x+r*2.0f,yr+r*2.04f),b2Vec2(x+r*-14.0f,yr+r*2.04f));      
	        (bbody->CreateFixture(&myfd))->SetFcolor(255,0,0,0.9f);
	        eshape.Set(b2Vec2(x+r*-18.0f,yr-r*2.0f),b2Vec2(x+r*-18.0f,yr+r*9.0f));      
	        (bbody->CreateFixture(&myfd))->SetFcolor(255,0,0,0.9f);
	        eshape.Set(b2Vec2(x+r*-14.0f,yr+r*2.0f),b2Vec2(x+r*-14.0f,yr+r*6.0f));      
	        (bbody->CreateFixture(&myfd))->SetFcolor(255,0,0,0.9f);
	        eshape.Set(b2Vec2(x+r*-18.0f,yr+r*9.0f),b2Vec2(x+r*9.0f,yr+r*9.0f));      
	        (bbody->CreateFixture(&myfd))->SetFcolor(255,0,0,0.9f);
	        eshape.Set(b2Vec2(x+r*-14.0f,yr+r*6.0f),b2Vec2(x+r*9.0f,yr+r*6.0f));      
	        (bbody->CreateFixture(&myfd))->SetFcolor(255,0,0,0.9f);
	        
	        //Water  57,88,121 ; 64,164,223
	        myfd.shape = &shape;
	        myfd.filter.maskBits = 0x0000;
	        shape.SetAsBox(r*2.0f, r*5.52f, b2Vec2(x+r*-16.0f,yr+r*3.52f), 0);
	        (bbody->CreateFixture(&myfd))->SetFcolor(0,0,255,1.0f,0);
	        shape.SetAsBox(r*5.1f, r*2.04f, b2Vec2(x+r*-8.9f,yr+r*0.0f), 0);
	        (bbody->CreateFixture(&myfd))->SetFcolor(0,0,255,1.0f,0);
	        shape.SetAsBox(r*8.3f, r*1.5f, b2Vec2(x+r*-8.4f,yr+r*7.5f), 0);
	        (bbody->CreateFixture(&myfd))->SetFcolor(0,0,255,1.0f,0);
	      }
	    }

	    //Con1-2
	    {
	      float32 yr=y+r*(30-2*1.404);

	      b2BodyDef bd;
	      b2Body* bbody = m_world->CreateBody(&bd);
	      b2EdgeShape eshape; 
	      b2FixtureDef myfd;
	      myfd.shape = &eshape;
	      myfd.friction = 0.2f;
	      eshape.Set(b2Vec2(x+r*11.0f,yr+r*6.0f),b2Vec2(x+r*+26.0f,yr+r*6.0f));      
	      (bbody->CreateFixture(&myfd))->SetFcolor(255,0,0,0.9f);
	      eshape.Set(b2Vec2(x+r*26.0f,yr+r*6.0f),b2Vec2(x+r*+35.0f,yr+r*1.0f));      
	      (bbody->CreateFixture(&myfd))->SetFcolor(255,0,0,0.9f);
	      eshape.Set(b2Vec2(x+r*+35.0f,yr+r*1.0f),b2Vec2(x+r*+50.0f,yr+r*1.0f));      
	      (bbody->CreateFixture(&myfd))->SetFcolor(255,0,0,0.9f);
	      eshape.Set(b2Vec2(x+r*+50.0f,yr+r*1.0f),b2Vec2(x+r*+59.0f,yr+r*-4.0f));      
	      (bbody->CreateFixture(&myfd))->SetFcolor(255,0,0,0.9f);
	      eshape.Set(b2Vec2(x+r*+59.0f,yr+r*-4.0f),b2Vec2(x+r*+74.0f,yr+r*-4.0f));      
	      (bbody->CreateFixture(&myfd))->SetFcolor(255,0,0,0.9f);
	      eshape.Set(b2Vec2(x+r*+74.0f,yr+r*-4.0f),b2Vec2(x+r*+83.0f,yr+r*1.0f));      
	      (bbody->CreateFixture(&myfd))->SetFcolor(255,0,0,0.9f);


	      //Spheres,Box
	      {
	        b2Body* sbody1;
	        b2CircleShape circle;
	        circle.m_radius = r*1.4f;    
	        b2FixtureDef ballfd;
	        ballfd.shape = &circle;
	        ballfd.density = 4.0f;
	        ballfd.friction = 0.0f;
	        ballfd.restitution = 0.0f;
	        b2BodyDef ballbd;
	        ballbd.type = b2_dynamicBody;
	        ballbd.position.Set(x+r*19.0, yr+r*7.5f);
	        sbody1 = m_world->CreateBody(&ballbd);
	        (sbody1->CreateFixture(&ballfd))->SetFcolor(0,0,255,0.85);
	      
	        b2Body* sbody2;      
	        ballbd.position.Set(x+r*24.0f, yr+r*7.5f);
	        sbody2 = m_world->CreateBody(&ballbd);
	        (sbody2->CreateFixture(&ballfd))->SetFcolor(255,0,0,0.85);

	        b2DistanceJointDef jointDef;
	        jointDef.length = r*5.0f;
	        jointDef.collideConnected = true;
	        jointDef.bodyA = sbody1;
	        jointDef.bodyB = sbody2;
	        jointDef.localAnchorA.Set(0,0);
	        jointDef.localAnchorB.Set(0,0);
	        m_world->CreateJoint(&jointDef);

	        b2PolygonShape shape;
	        shape.SetAsBox(r*4.0f, r*2.0f);    
	        b2BodyDef bd2;
	        bd2.position.Set(x+r*21.5f, yr+r*2.0f);
	        bd2.type = b2_dynamicBody;
	        b2Body* bodyb = m_world->CreateBody(&bd2);
	        b2FixtureDef *fd = new b2FixtureDef;
	        fd->density = 2.0f;
	        fd->shape = &shape;
	        (bodyb->CreateFixture(fd))->SetFcolor(255,135,0,1.0);

	        b2RopeJointDef jointDef2;
	        jointDef2.bodyA = bodyb;
	        jointDef2.bodyB = sbody1;
	        jointDef2.localAnchorA.Set(r*-2.5f,r*0.0f);
	        jointDef2.localAnchorB.Set(0,0);
	        jointDef2.maxLength = r*5.0f;
	        m_world->CreateJoint(&jointDef2);
	        jointDef2.bodyB = sbody2;
	        jointDef2.localAnchorA.Set(r*2.5f,r*0.0f);
	        m_world->CreateJoint(&jointDef2);
	      }

	    }
  	}

  	//d middle
  	{
	  	float32 x=25.0f;
	    float32 y=27.0f;
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
	          (stbody->CreateFixture(&myfd))->SetFcolor(255,0,0,0.9f);
	        }
	        eshape.Set(b2Vec2(0,r1*-len),b2Vec2(r1*2*len,r1*-len));
	        myfd.shape = &eshape;
	        (stbody->CreateFixture(&myfd))->SetFcolor(255,0,0,0.9f);
	        for(int i=0; i<5; i++)
	        {
	          eshape.Set(b2Vec2(r1*(-len-len*i-lenhx*(i+1)),r1*-len*i),b2Vec2(r1*(-len-len*i-lenhx*(i+1)),r1*(-len-len*i)));
	          myfd.shape = &eshape;
	          (stbody->CreateFixture(&myfd))->SetFcolor(255,0,0,0.9f);
	        }
	        eshape.Set(b2Vec2(0,0),b2Vec2(0,r1*-len));
	        myfd.shape = &eshape;
	        (stbody->CreateFixture(&myfd))->SetFcolor(255,0,0,0.9f);
	        eshape.Set(b2Vec2(r1*2*len,0),b2Vec2(r1*2*len,r1*-len));
	        myfd.shape = &eshape;
	        (stbody->CreateFixture(&myfd))->SetFcolor(255,0,0,0.9f);
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
	          (sbody1->CreateFixture(&ballfd))->SetFcolor(0,0,255,0.85);
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
	          (sbody2->CreateFixture(&ballfd))->SetFcolor(255,0,0,0.85);
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
	        myfd.shape = &pshape;
	        ballbd.position.Set(xin+rin*-38.0f, yin+rin*-18.0f);
	        inbody = m_world->CreateBody(&ballbd);
	        pshape.SetAsBox(len, rin*0.3f, b2Vec2(-len, 0.0f), 0);
	        (inbody->CreateFixture(&myfd))->SetFcolor(0,0,255,0.9f);
	        pshape.SetAsBox(len, rin*0.3f, b2Vec2(-len*3.828f/1.414f, len/1.414f), -b2_pi/4);
	        (inbody->CreateFixture(&myfd))->SetFcolor(0,0,255,0.9f);
	        pshape.SetAsBox(len, rin*0.3f, b2Vec2(-len*4.414f, len*1.414f), 0);
	        (inbody->CreateFixture(&myfd))->SetFcolor(0,0,255,0.9f);
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
	        ballbd.position.Set(xin+rin*-80, yin+rin*0.0f);
	        sbody = m_world->CreateBody(&ballbd);
	        (sbody->CreateFixture(&ballfd))->SetFcolor(255,255,0,0.85);
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
	        (sbody->CreateFixture(&ballfd))->SetFcolor(255,0,0,0.85);

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
	          (sbody->CreateFixture(&fd3))->SetFcolor(255,255,0,0.9);
	        }

	        {
	          b2PolygonShape shape1;
	          shape1.SetAsBox(rg*0.3f, rg*8.0f, rg*b2Vec2(3.0f, -13.0f), -b2_pi/3);
	          b2FixtureDef fdb;
	          fdb.density = 70.0f;
	          fdb.restitution = 0.4f;
	          fdb.shape = &shape1;
	          (sbody->CreateFixture(&fdb))->SetFcolor(0,0,255,0.9);

	          b2EdgeShape eshape; 
	          eshape.Set(b2Vec2(0,0),b2Vec2(rg*7.5f,rg*-10.5f));
	          b2FixtureDef myfd;
	          myfd.shape = &eshape;
	          myfd.density = 0.0f;
	          myfd.filter.maskBits = 0x0000;
	         (sbody->CreateFixture(&myfd))->SetFcolor(255,0,0,0.9f);
	        }
	      }
	    }
	    //Endgear

	    //D2
	    {
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
    	//End Key
  	}

  	//d end
	  {
	  	float32 x=95.0f;
	    float32 y=-35.0f;
	    float32 r=0.8f;

	    //Ground
	    {
	      b2BodyDef bd;
	      bd.position.Set(x+r*0.0f, y+r*0.0f);
	      b2Body* gbody = m_world->CreateBody(&bd);
	      b2PolygonShape shape1;
	      shape1.SetAsBox(r*80.0f, r*5.0f, r*b2Vec2(-10.0f, -8.0f), 0);
	      b2FixtureDef fdb;
	      fdb.shape = &shape1;
	      (gbody->CreateFixture(&fdb))->SetFcolor(124,255,0,0.9,1);
	    }

	   //Car
	    {
			  float32 rc=r*1.2f;
			  float32 xc=r*-86.0f;
			  float32 yc=r*3.5f;

			  b2BodyDef cardf;
			  cardf.type = b2_dynamicBody;
			  cardf.position.Set(x+rc*xc, y+rc*yc);
			  b2Body* car = m_world->CreateBody(&cardf);
			  car2 = car;
			  //car->ApplyLinearImpulse(b2Vec2(10,0), car->GetPosition() ,true);
			  b2FixtureDef cfd;
			  cfd.density = 0.1f;
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
			    ballfd.density = 0.1f;
			    ballfd.friction = 0.0f;
			    ballfd.restitution = 0.1f;
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

	   	//Maze
	   	{
	   		float32 xm=x+r*-45.0f;
		    float32 ym=y+r*42.0f;
		    float32 rm=r*1.0f;
		    float32 csize=rm*4.7f;

		    bool R[6][10]={
		    	{1,1,1,1,1,1,1,1,1,1},{0,1,0,0,1,0,0,1,1,0},{0,1,1,1,0,1,0,0,0,1},
		    	{1,0,0,1,0,0,1,1,0,0},{0,1,1,0,0,1,1,0,1,1},{1,1,1,1,1,1,1,1,1,1}
		    };
		  	bool C[5][11]={
		  		{0,0,0,1,0,0,1,0,0,0,1},{1,1,0,1,0,1,0,1,1,0,1},{1,0,1,0,1,0,1,0,1,1,1},
		  		{1,0,0,1,0,1,0,1,0,0,1},{1,0,0,0,1,0,1,0,0,0,1}
		  	};

	  	  b2BodyDef bd;
	      b2Body* bbody = m_world->CreateBody(&bd);
	      b2EdgeShape eshape; 
	      b2FixtureDef myfd;
	      myfd.shape = &eshape;

	      for(int i=0;i<6;i++){
	      	for(int j=0;j<10;j++){
	      		if(!R[i][j])continue;
			      eshape.Set(b2Vec2(xm+csize*j,ym+csize*-i),b2Vec2(xm+csize*(j+1),ym+csize*-i));      
			      (bbody->CreateFixture(&myfd))->SetFcolor(255,255,0,1.0f);
		    	}
	  	  }
	  	  for(int i=0;i<5;i++){
	      	for(int j=0;j<11;j++){
	      		if(!C[i][j])continue;
			      eshape.Set(b2Vec2(xm+csize*j,ym+csize*-i),b2Vec2(xm+csize*j,ym+csize*(-i-1)));      
			      (bbody->CreateFixture(&myfd))->SetFcolor(255,200,0,1.0f);
		    	}
	  	  }
	  	  eshape.Set(b2Vec2(xm+csize*0,ym+csize*0),b2Vec2(xm+csize*-1,ym+csize*0));      
			  (bbody->CreateFixture(&myfd))->SetFcolor(255,255,0,1.0f);
			  eshape.Set(b2Vec2(xm+csize*0,ym+csize*-1),b2Vec2(xm+csize*-1,ym+csize*-1));      
			  (bbody->CreateFixture(&myfd))->SetFcolor(255,255,0,1.0f);
			  eshape.Set(b2Vec2(xm+csize*-1,ym+csize*0),b2Vec2(xm+csize*-1,ym+csize*-1));      
			  (bbody->CreateFixture(&myfd))->SetFcolor(255,200,0,1.0f);

			  //Sphere
			  {
			  	b2Body* sbody;			  	
	        b2CircleShape circle;
	        circle.m_radius = 0.92*csize/2;    
	        b2FixtureDef ballfd;
	        ballfd.shape = &circle;
	        ballfd.density = 0.05f;
	        ballfd.friction = 0.0f;
	        ballfd.restitution = 0.0f;
	        b2BodyDef ballbd;
	        ballbd.type = b2_dynamicBody;
	        ballbd.position.Set(xm+rm*-csize/2.0f, ym+rm*-csize/2.0f);
	        sbody = m_world->CreateBody(&ballbd);
          sbody->setmousejoint();
	        mazesphere = sbody;
	        (sbody->CreateFixture(&ballfd))->SetFcolor(255,0,0,0.85);
			  }

	   	}

	   	//Base,Cannon
	   	{
	   		float32 xc=x+r*20.0f;
			  float32 yc=y+r*19.0f;
			  
	   		b2BodyDef bd;
	      b2Body* bbody = m_world->CreateBody(&bd);
	      b2EdgeShape eshape; 
	      b2FixtureDef myfd;
	      myfd.shape = &eshape;
	      eshape.Set(b2Vec2(xc+r*-95.0f,yc+r*-7.0f),b2Vec2(xc+r*0.0f,yc+r*-7.0f));      
			  (bbody->CreateFixture(&myfd))->SetFcolor(255,0,0,1.0f);
			  eshape.Set(b2Vec2(xc+r*0.0f,yc+r*-7.0f),b2Vec2(xc+r*0.0f,yc+r*0.0f));      
			  (bbody->CreateFixture(&myfd))->SetFcolor(0,0,0,1.0f);
			  eshape.Set(b2Vec2(xc+r*0.0f,yc+r*0.0f),b2Vec2(xc+r*40.0f,yc+r*0.0f));      
			  (bbody->CreateFixture(&myfd))->SetFcolor(255,0,0,1.0f);

				float32 rc=r*1;
			  //Cannon
			  {
			  	float32 ang = 12.0f;
	        float32 t_ang = 8.0f;
			  	
			  	b2BodyDef bd;
	        bd.position.Set(xc+rc*15.0f, yc+rc*-8.0f);
	        b2Body* body = m_world->CreateBody(&bd);
	        b2FixtureDef *fd = new b2FixtureDef;
	        b2PolygonShape pshape;        
	        b2CircleShape circle;        

	        //Body
	        fd->shape = &circle; 
	        fd->filter.maskBits = 0x0000;
	        circle.m_radius = rc*3.5f;           
	        (body->CreateFixture(fd))->SetFcolor(50,30,255,0.9);
	        circle.m_radius = rc*1.2f;           
	        (body->CreateFixture(fd))->SetFcolor(255,0,0,1.0);

	        
	        fd->shape = &pshape;
	        pshape.SetAsBox(rc*4.2f, rc*1.75f, b2Vec2(rc*-4.55*cosf((22.6166-ang-t_ang)*DEGTORAD),
	        	rc*4.55*sinf((22.6166-ang-t_ang)*DEGTORAD)),(ang+t_ang)*DEGTORAD);     
	        (body->CreateFixture(fd))->SetFcolor(0,30,255,0.9,0);
	        pshape.SetAsBox(rc*4.2f, rc*1.75f, b2Vec2(rc*-4.55*cosf((22.6166-ang+t_ang)*DEGTORAD),
	        	rc*-4.55*sinf((22.6166-ang+t_ang)*DEGTORAD)),-(ang-t_ang)*DEGTORAD);   
	        (body->CreateFixture(fd))->SetFcolor(0,30,255,0.9,0);
	        pshape.SetAsBox(rc*3.0f, rc*1.50f, b2Vec2(rc*-5.6*cosf(t_ang*DEGTORAD),
	        	rc*-5.6*sinf(t_ang*DEGTORAD)),t_ang*DEGTORAD);   
	        (body->CreateFixture(fd))->SetFcolor(255,0,0,1.0);

	        //Base        
	        pshape.SetAsBox(rc*6.0f, rc*0.5f, b2Vec2(rc*0.0f,rc*7.5f), 0);     
	        (body->CreateFixture(fd))->SetFcolor(139,0,139,0.9);
	        pshape.SetAsBox(rc*4.0f, rc*0.5f, b2Vec2(rc*0.0f,rc*6.5f), 0);     
	        (body->CreateFixture(fd))->SetFcolor(0,30,255,0.9);
	        pshape.SetAsBox(rc*0.6f, rc*3.0f, b2Vec2(rc*0.0f,rc*3.0f), 0);     
	        (body->CreateFixture(fd))->SetFcolor(0,30,255,0.9);  

	        {
				  	//Cannon Balls
				  	b2CircleShape circle;
		        circle.m_radius = rc*1.0f;    
		        b2FixtureDef ballfd;
		        ballfd.shape = &circle;
		        ballfd.density = 50.0f;
		        ballfd.friction = 0.0f;
		        ballfd.restitution = 0.2f;
		        b2BodyDef ballbd;
		        ballbd.type = b2_dynamicBody;

		        float32 xrr=xc+rc*15.0f;
		        float32 yrr=yc+rc*-8.0f;
		        ballbd.position.Set(xrr+rc*-2.1*cosf(t_ang*DEGTORAD),yrr+rc*-2.1*sinf(t_ang*DEGTORAD));
		        cannonball1 = m_world->CreateBody(&ballbd);
		        cannonball1->SetAwake(false);
		        (cannonball1->CreateFixture(&ballfd))->SetFcolor(0,0,0,1.0);

		        ballbd.position.Set(xrr+rc*-5.1*cosf(t_ang*DEGTORAD),yrr+rc*-5.1*sinf(t_ang*DEGTORAD));
		        cannonball2 = m_world->CreateBody(&ballbd);
		        cannonball2->SetAwake(false);
		        (cannonball2->CreateFixture(&ballfd))->SetFcolor(0,0,0,1.0);

		        ballbd.position.Set(xrr+rc*-8.1*cosf(t_ang*DEGTORAD),yrr+rc*-8.1*sinf(t_ang*DEGTORAD));
		        cannonball3 = m_world->CreateBody(&ballbd);
		        cannonball3->SetAwake(false);
		        (cannonball3->CreateFixture(&ballfd))->SetFcolor(0,0,0,1.0);
	      	}
			  }
			}

			//To Stop the sphere
			{
				b2PolygonShape shape;
	      shape.SetAsBox(r*3.0f, r*0.3f);    
	      b2BodyDef bd;
	      bd.position.Set(x+r*12.0f, y+r*30.0f);
	      bd.type = b2_dynamicBody;
	      b2Body* body = m_world->CreateBody(&bd);
	      rplatform = body;
	      b2FixtureDef *fd = new b2FixtureDef;
	      fd->density = 5.0f;
	      fd->friction = 0.0f;
	      fd->shape = &shape;
	      (body->CreateFixture(fd))->SetFcolor(139,0,139,0.9);
	           
	      b2BodyDef bd2;
	      bd2.position.Set(x+r*12.0f, y+r*30.0f);
	      b2Body* bodyf = m_world->CreateBody(&bd2);

	      b2RevoluteJointDef jointDef;
	      jointDef.bodyA = body;
	      jointDef.bodyB = bodyf;
	      jointDef.localAnchorA.Set(0,0);
	      jointDef.localAnchorB.Set(0,0);
	      jointDef.collideConnected = false;
	      m_world->CreateJoint(&jointDef);

	      //Heavy Box
	      bd.position.Set(x+r*12.0f, y+r*32.5f);
	      b2Body* hbody = m_world->CreateBody(&bd);
	      fd->density = 30.0f;
	      fd->friction = 0.6f;
	      shape.SetAsBox(r*2.0f, r*2.0f);
	      (hbody->CreateFixture(fd))->SetFcolor(139,139,0,0.9);
			}

	   	//Buttons,Sensors
		  {
		  	//sensor
		  	b2BodyDef bd;
	      bd.position.Set(x+r*0.5f, y+r*15.25f);
	      b2Body* s1 = m_world->CreateBody(&bd);
	      bsensor = s1;
	      b2FixtureDef *fd = new b2FixtureDef;
	      b2PolygonShape pshape; 
	      pshape.SetAsBox(r*1.6f, r*2.9f);  
	      fd->shape = &pshape;
	      b2Fixture* fx=s1->CreateFixture(fd);
	      fx->SetFcolor(255,255,0,0.9,0);
	      fx->SetSensor(true);

	      //Support
	      {
	      	b2BodyDef bd;
	        b2Body* bbody = m_world->CreateBody(&bd);
	        b2EdgeShape eshape; 
	        b2FixtureDef myfd;
	        myfd.shape = &eshape;
	        myfd.density = 0.0f;

	        eshape.Set(b2Vec2(x+r*19.95f,y+r*15.31f),b2Vec2(x+r*18.75f,y+r*15.31f));      
	        (bbody->CreateFixture(&myfd))->SetFcolor(170,170,170,1.0f);
	        eshape.Set(b2Vec2(x+r*19.95f,y+r*13.29f),b2Vec2(x+r*18.75f,y+r*13.29f));      
	        (bbody->CreateFixture(&myfd))->SetFcolor(170,170,170,1.0f);

	        eshape.Set(b2Vec2(x+r*1.9f,y+r*21.81f),b2Vec2(x+r*0.7f,y+r*21.81f));      
	        (bbody->CreateFixture(&myfd))->SetFcolor(170,170,170,1.0f);
	        eshape.Set(b2Vec2(x+r*1.9f,y+r*19.79f),b2Vec2(x+r*0.7f,y+r*19.79f));      
	        (bbody->CreateFixture(&myfd))->SetFcolor(170,170,170,1.0f);
	      }

	      //cannon button
	      b2BodyDef bd2;
	      b2FixtureDef *fd2 = new b2FixtureDef;
	      fd2->shape = &pshape;
	      fd2->filter.maskBits = 0x0000;
	      bd2.position.Set(x+r*19.95f, y+r*14.3f);
	      b2Body* cannonbase = m_world->CreateBody(&bd2);
	      pshape.SetAsBox(r*0.65f, r*2.0f, b2Vec2(r*-0.63f,r*0.0f), 0);   
	      (cannonbase->CreateFixture(fd2))->SetFcolor(170,170,170,1.0); 

	      fd2->filter.maskBits = 0xFFFF;
	      bd2.type = b2_dynamicBody;
	      bd2.position.Set(x+r*18.85f, y+r*14.3f);
	      cannonbutton = m_world->CreateBody(&bd2); 
	      pshape.SetAsBox(r*0.5f, r*1.0f, b2Vec2(r*-0.5f,r*0.0f), 0);   
	      (cannonbutton->CreateFixture(fd2))->SetFcolor(255,0,0,1.0,0);
	      b2CircleShape circle;
	      fd2->shape = &circle;
	      circle.m_radius = r*1.0f;
	      circle.m_p = r*b2Vec2(-1.0f,0.0f);
	      (cannonbutton->CreateFixture(fd2))->SetFcolor(255,0,0,1.0,0);

	      //stop button
	      b2BodyDef bd3;
	      b2FixtureDef *fd3 = new b2FixtureDef;
	      fd3->filter.maskBits = 0x0000;
	      fd3->shape = &pshape;
	      bd3.position.Set(x+r*1.9f, y+r*20.8f);
	      b2Body* stopbase = m_world->CreateBody(&bd3);
	      pshape.SetAsBox(r*0.65f, r*2.0f, b2Vec2(r*-0.63f,r*0.0f), 0);   
	      (stopbase->CreateFixture(fd3))->SetFcolor(170,170,170,1.0);  

	      fd3->filter.maskBits = 0xFFFF;
	      bd3.type = b2_dynamicBody;
	      bd3.position.Set(x+r*0.8f, y+r*20.8f);
	      pshape.SetAsBox(r*0.5f, r*1.0f, b2Vec2(r*-0.5f,r*0.0f), 0); 
	      stopbutton = m_world->CreateBody(&bd3);   
	      (stopbutton->CreateFixture(fd3))->SetFcolor(0,0,255,1.0,0);
	      fd3->shape = &circle;
	      (stopbutton->CreateFixture(fd3))->SetFcolor(0,0,255,1.0,0);
		    {//Joints
		      b2RopeJointDef jointDef;
		      jointDef.bodyA = cannonbase;
		      jointDef.bodyB = cannonbutton;
		      jointDef.localAnchorA.Set(r*-0.1f,r*1.0f);
		      jointDef.localAnchorB.Set(r*0.2f,r*1.0f);
		      jointDef.maxLength = r*0.8f;
		      m_world->CreateJoint(&jointDef);
		      jointDef.localAnchorA.Set(r*-0.1f,r*-1.0f);
		      jointDef.localAnchorB.Set(r*0.2f,r*-1.0f);
		      m_world->CreateJoint(&jointDef);

		      jointDef.bodyA = stopbase;
		      jointDef.bodyB = stopbutton;
		      jointDef.localAnchorA.Set(r*-0.1f,r*1.0f);
		      jointDef.localAnchorB.Set(r*0.2f,r*1.0f);
		      m_world->CreateJoint(&jointDef);
		      jointDef.localAnchorA.Set(r*-0.1f,r*-1.0f);
		      jointDef.localAnchorB.Set(r*0.2f,r*-1.0f);
		      m_world->CreateJoint(&jointDef);

		      b2DistanceJointDef jointDef2;
		      jointDef2.length = r*0.8f;
		      jointDef2.frequencyHz = 12.0f;
		      jointDef2.bodyA = cannonbase;
		      jointDef2.bodyB = cannonbutton;
		      jointDef2.localAnchorA.Set(r*-0.1f,r*1.0f);
		      jointDef2.localAnchorB.Set(r*0.2f,r*1.0f);
		      m_world->CreateJoint(&jointDef2);
		      jointDef2.localAnchorA.Set(r*-0.1f,r*-1.0f);
		      jointDef2.localAnchorB.Set(r*0.2f,r*-1.0f);
		      m_world->CreateJoint(&jointDef2);

		      jointDef2.bodyA = stopbase;
		      jointDef2.bodyB = stopbutton;
		      jointDef2.frequencyHz = 3.0f;
		      jointDef2.localAnchorA.Set(r*-0.1f,r*1.0f);
		      jointDef2.localAnchorB.Set(r*0.2f,r*1.0f);
		      m_world->CreateJoint(&jointDef2);
		      jointDef2.localAnchorA.Set(r*-0.1f,r*-1.0f);
		      jointDef2.localAnchorB.Set(r*0.2f,r*-1.0f);
		      m_world->CreateJoint(&jointDef2);
		    }
	    }
	  }	 

  	

	}

}