#include "callbacks.hpp"

#ifndef __APPLE__
#include "GL/glui.h"
#else
#include "GL/glui.h"
#endif

namespace cs251{

	extern int32 step_count;
	extern int32 test_index;
  extern int32 test_selection;
  extern int32 test_count;
  extern cs251::sim_t* entry[10];
  extern cs251::base_sim_t* test[10];
  extern cs251::settings_t settings;
  extern const int32 frame_period;
  extern float settings_hz;
  extern int32 width;
  extern int32 height;
  extern int32 main_window;
  extern float32 view_zoom;

	void callbacks_t::display_cb(void)
  	{
    //if(step_count%4==0){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //}

    for(int z=0;z<test_count;z++)
    {
      if (test[z])
        {
          test[z]->set_text_line(30);
        }
    }

    b2Vec2 old_center = settings.view_center;
    settings.hz = settings_hz;
    
    for(int z=0;z<test_count;z++)
    {
      if (test[z])
      {
        test[z]->step(&settings);
      }
    }
    
    //====    settings.view_center.x+=0.1f;
    if (old_center.x != settings.view_center.x || old_center.y != settings.view_center.y)
    {
     resize_cb(width, height);
    }
    
    for(int z=0;z<test_count;z++)
    {
      if (test[z])
      {
        test[z]->draw_title(5, 15, entry[z]->name);
      }
    }
        
    //if(step_count%4==0){
    glutSwapBuffers();
    //}

    if (test_selection != test_index)
	  {
	    	test_index = test_selection;
	      for(int z=0;z<test_count;z++)
	      {
	        if(test[z]){
	          delete test[z];
	          entry[z] = cs251::sim[z];
	          test[z] = entry[z]->create_fcn();
	        }
	      }
	    	view_zoom = 1.0f;
	    	settings.view_center.Set(0.0f, 20.0f);
	  resize_cb(width, height);
	  }
      //step_count++;
    }
}