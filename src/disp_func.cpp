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
  extern float32 view_zoom;//0.02-20

  void pan_zoom();
   
 	void callbacks_t::display_cb(void)
  {
    b2Vec2 old_center = settings.view_center;
    settings.hz = settings_hz;

    if(!settings.pause)pan_zoom();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    for(int z=0;z<test_count;z++)
    {
      if (test[z])
      {
        test[z]->set_text_line(30);
      }
    }

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
        
    glutSwapBuffers();
    
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
    if(!settings.pause)step_count++;
  }

  void pan_zoom()
  {
    if(step_count==0)
    {
      settings.view_center.Set(-130.0f, 25.0f);
      view_zoom = 0.9;
      entry[0]->name="You are about to enter a restricted Area.";
    }
    if(step_count==264)entry[0]->name="You have entered a Restricted Area. The Security System has been Activated.";
    if(step_count>264&&step_count<474)
    {
      settings.view_center.x+=0.14f;
      settings.view_center.y+=0.08f;
    }
    if(step_count>=474&&step_count<704)
    {
      settings.view_center.x+=0.1f;
    }
    if(step_count>=704&&step_count<906)
    {
      settings.view_center.x+=0.4f;
      settings.view_center.y-=0.075f;
      view_zoom+=0.27/300;
    }
    if(step_count>=1176&&step_count<1263)
    {
      settings.view_center.x-=0.15f;
      settings.view_center.y+=0.24f;
      view_zoom-=1.0/300;
    }
    if(step_count>=1440&&step_count<1580)
    {
      settings.view_center.x+=0.16f;
      settings.view_center.y-=0.03f;
      view_zoom-=0.60/300;
    }
    if(step_count>=1780&&step_count<1930)
    {
      settings.view_center.x+=0.16f;
      settings.view_center.y-=0.015f;
      //view_zoom-=0.55/300;
    }
    if(step_count>=2250&&step_count<2400)
    {
      settings.view_center.x-=0.06f;
      settings.view_center.y-=0.1f;
      view_zoom+=0.1/300;
    }
    if(step_count>=2675&&step_count<2800)
    {
      settings.view_center.x-=0.1f;
      settings.view_center.y-=0.15f;
      view_zoom+=0.3/300;
    }
    if(step_count>=2875&&step_count<3050)
    {
      settings.view_center.x-=0.1f;
      settings.view_center.y-=0.03f;
      view_zoom+=0.16/300;
    }
    if(step_count==4229)entry[0]->name="Use your Mouse to solve the maze and push the blue button to turn off the security system";
    if(step_count>=4229&&step_count<4600)
    {
      settings.view_center.x+=0.24f;
      settings.view_center.y-=0.034f;
      view_zoom-=0.01/300;
    }
    if(step_count>=4600&&step_count<4670)
    {
      settings.view_center.y-=0.12f;
    }

    
  }
}

