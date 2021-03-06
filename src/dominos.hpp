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

#ifndef _DOMINOS_HPP_
#define _DOMINOS_HPP_

namespace cs251
{
  //! This is the class that sets up the Box2D simulation world
  //! Notice the public inheritance - why do we inherit the base_sim_t class?
  class dominos_t1 : public base_sim_t
  {
  public:
    
    dominos_t1();
    
    static base_sim_t* create()
    {
      return new dominos_t1;
    }
  };

  class dominos_t2 : public base_sim_t
  {
  public:
    
    dominos_t2();
    
    static base_sim_t* create()
    {
      return new dominos_t2;
    }
  };

  class dominos_t3 : public base_sim_t
  {
  public:
    
    dominos_t3();
    
    static base_sim_t* create()
    {
      return new dominos_t3;
    }
  };

  class dominos_t4 : public base_sim_t
  {
  public:
    
    dominos_t4();
    
    static base_sim_t* create()
    {
      return new dominos_t4;
    }
  };

  class dominos_t5 : public base_sim_t
  {
  public:
    
    dominos_t5();
    
    static base_sim_t* create()
    {
      return new dominos_t5;
    }
  };

  class dominos_t6 : public base_sim_t
  {
  public:
    
    dominos_t6();
    
    static base_sim_t* create()
    {
      return new dominos_t6;
    }
  };

  class dominos_t7 : public base_sim_t
  {
  public:
    
    dominos_t7();
    
    static base_sim_t* create()
    {
      return new dominos_t7;
    }
  };

  class dominos_t8 : public base_sim_t
  {
  public:
    
    dominos_t8();
    
    static base_sim_t* create()
    {
      return new dominos_t8;
    }
  };

  class dominos_t9 : public base_sim_t
  {
  public:
    
    dominos_t9();
    
    static base_sim_t* create()
    {
      return new dominos_t9;
    }
  };

  class dominos_t10 : public base_sim_t
  {
  public:
    
    dominos_t10();
    
    static base_sim_t* create()
    {
      return new dominos_t10;
    }
  };

}
  
#endif
