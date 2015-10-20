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
  }
      
}
