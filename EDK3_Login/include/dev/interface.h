#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "../math_library/vector_2.h"
#include "../math_library/vector_3.h"
#include "ESAT_extra/imgui.h"
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
  bool no_bring_to_front  = false;
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

//enum LightType {
//	Directional,
//	Point,
//	Spot,
//};
//
//const char* GetLightTypeName(LightType type);

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
void LightsWindow();
void PerformanceWindow(double dt);
void CameraWindow();
void EntitiesManagerWindow();
void ControlWindow();
#endif
