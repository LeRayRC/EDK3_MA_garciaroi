#ifndef _DEMO_MANAGER_H_
#define _DEMO_MANAGER_H_ 1

#include <stdlib.h>


#include "interface.h"
#include "EDK3/geometry.h"
#include "EDK3/camera.h"
#include "EDK3/drawable.h"
#include "EDK3/matdiffusetexture.h"
#include "EDK3/texture.h"
#include "EDK3/dev/gpumanager.h"

#include "ESAT_extra/imgui.h"
#include "EDK3/dev/opengl.h"

#include "camera_custom.h"

/**
 * @brief Class the represents the singleton that manages the game
 * 
 */
class DemoManager{
  //Attributes
  private:
    static DemoManager* instance;
  public:
    EDK3::ref_ptr<EDK3::CameraCustom> camera;
    EDK3::ref_ptr<EDK3::Node> root;


    float dt;
    ImGuiWindow settings_window;
    ImGuiWindow lights_window;
    ImGuiWindow performance_window;
    ImGuiWindow camera_window;

  //Methods
  private:
    // Constructor
    DemoManager();
    // Copy constructor
    DemoManager(DemoManager& other);


  public:

    static DemoManager* getInstance();


    void init();
};

#endif