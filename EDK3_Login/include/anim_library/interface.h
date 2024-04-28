/**
 * @file interface.h
 * @author Carlos García
 * @brief header file that defines all the functions related to user interface
 */
#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "platform.h"

#include "math_lib/vector_2.h"
#include "gtexture.h"

/**
 * @struct BooleanWindowFlags
 * @brief A structure to manage boolean flags for window customization.
 *
 * This structure contains boolean flags that control various aspects of ImGui windows.
 */
struct BooleanWindowFlags{
  bool no_titlebar        = false;
  bool no_scrollbar       = false;
  bool no_menu            = false;
  bool no_move            = false;
  bool no_resize          = false;
  bool no_collapse        = false;
  bool no_close           = false;
  bool no_nav             = false;
  bool no_background      = false;
  bool no_bring_to_front  = false;
  bool unsaved_document   = false;
};

/**
 * @struct ImGuiWindow
 * @brief A custom structure for ImGui windows with flags.
 *
 * This structure defines custom ImGui windows with boolean flags
 * for window customization and a flag to determine if the window is open.
 */
struct ImGuiWindow{
  BooleanWindowFlags flags;
  ImGuiWindowFlags window_flags;
  bool popen;
};

/**
 * @brief Update the framerate window information.
 *
 * This function updates the framerate window information by calculating the frames per second (FPS).
 * It uses ImGui to obtain the current framerate and updates the game's framerate accordingly.
 * The update occurs at regular intervals specified by the refresh_fps_cooldown property in the Game instance.
 */
void UpdateFramerateWindow();

/**
 * @brief Display the Entities Manager window using ImGui.
 *
 * This function creates and displays the Entities Manager window using ImGui.
 * It allows the user to interact with entities, update their properties, and control animations.
 * The window includes options for updating entity names, positions, rotations, scales, and animations.
 */
void EntitiesManagerWindow();

/**
 * @brief Display the Animation Configs Manager window using ImGui.
 *
 * This function creates and displays the Animation Configs Manager window using ImGui.
 * It allows the user to manage animation configurations, including moving, rotating, and scaling properties.
 * The window includes options for updating configuration names, saving configurations, and more.
 */
void AnimationConfigsManagerWindow();

/**
 * @brief Initialize default ImGui window flags.
 *
 * This function initializes default ImGui window flags for the specified ImGuiWindow.
 *
 * @param window The ImGuiWindow for which to set the flags.
 * @param default_opened Whether the window is initially opened or closed.
 */
void InitDefaultWindowFlags(ImGuiWindow *window, bool default_opened=true);

/**
 * @brief Display the settings window using ImGui.
 *
 * This function creates and displays the settings window using ImGui.
 * It provides options to customize window settings, toggle visibility, and access additional menus.
 * The window also includes options to create new entities, animations, and to save all configurations.
 */
void WindowSettings(ImGuiWindow* window);

/**
 * @brief Control the display of various windows based on their open state.
 *
 * This function acts as a controller for managing the display of different windows
 * within the application based on their respective "popen" (open) states.
 * It calls functions to display specific windows when their corresponding "popen" state is true.
 */
void WindowsController();

/**
 * @brief Display a menu bar for customizing window options using ImGui.
 *
 * This function creates and displays a menu bar within an ImGui window, allowing users
 * to customize various options such as visibility, titlebar, resizing, moving, and background.
 *
 * @param window The ImGuiWindow for which the menu bar is created to customize options.
 */
void WindowMenu(ImGuiWindow* window);

/**
 * @brief Set ImGui window flags based on the provided configuration.
 *
 * This function sets ImGui window flags based on the specified configuration provided in the ImGuiWindow structure.
 * It checks various flag options such as no titlebar, no scrollbar, menu bar, no move, no resize, no collapse,
 * no navigation, no background, no bring to front on focus, and unsaved document.
 *
 * @param window The ImGuiWindow structure containing configuration options and window flags.
 */
void SetFlags(ImGuiWindow* window);

/**
 * @brief Display a window for creating a new path using ImGui.
 *
 * This function creates and displays a window using ImGui for creating a new path entity.
 * Users can specify whether the path should be a regular polygon, set the number of vertices,
 * provide position, rotation, and scale values, and define vertex positions for irregular paths.
 * The window includes a button to create the path entity based on the specified parameters.
 */
void NewPathWindow();

/**
 * @brief Display a window for creating a new animation configuration using ImGui.
 *
 * This function creates and displays a window using ImGui for creating a new animation configuration.
 * Users can specify whether the animation involves moving, rotating, and/or scaling, providing
 * details such as starting and ending values, durations, and a name for the configuration.
 * The window includes a button to create the new animation configuration based on user input.
 */
void NewAnimationConfigWindow();

/**
 * @brief Display a window for creating a new texture using ImGui.
 *
 * This function creates and displays a window using ImGui for creating a new texture.
 * Users can browse for an image file (PNG or JPG) and import it as a texture.
 * The window includes buttons for browsing, importing, and displays the selected file path.
 * If the import fails, an error message is displayed.
 */
void NewTextureWindow();

/**
 * @brief Display a window for creating a new sprite using ImGui.
 *
 * This function creates and displays a window using ImGui for creating a new sprite.
 * Users can select a texture from the available textures and set the position and size of the sprite.
 * The window includes a preview of the selected texture and options for specifying position and size.
 * If there are no imported textures, an error message is displayed.
 */
void NewSpriteWindow();

/**
 * @brief Display an image in an ImGui window from a texture handle.
 *
 * This function takes a texture handle and uses ImGui to display the corresponding image
 * in a window. The image is retrieved from the specified texture handle.
 *
 * @param handle The handle of the texture whose image will be displayed.
 */
void ImageFromTexture(Handle handle);

#endif
