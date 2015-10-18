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
  {//Maze
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
      }
      
}
