/**
 * @file gwindow.h
 * @author Carlos García
 * @brief header file that allocates the class related to graphic window renderer
 */
#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "platform.h"
#include "math_lib/vector_2.h"

/**
 * @brief Class that represents a window renderer and its methods and attributes
 * 
 */
class Window{
  public:
    WindowRenderer windowRenderer;
    /* data */
  public:
    Window(/* args */);
    ~Window();

    /**
    * @brief Initialize the window with the specified resolution.
    *
    * This function initializes the window with the specified resolution.
    *
    * @param resolution A Vec2 representing the resolution (width, height) of the window.
    */
    void windowInit(Vec2 resolution);

    /**
    * @brief Check if the window is currently open.
    *
    * @return true if the window is open, false otherwise.
    */
    bool isOpen();

    /**
    * @brief Begin drawing operations on the window.
    *
    * This function begins the drawing operations on the window and clears the screen.
    */
    void windowDrawBegin();

    /**
    * @brief End drawing operations on the window.
    *
    * This function ends the drawing operations on the window.
    */
    void windowDrawEnd();

    /**
    * @brief Closes the current render window.
    *
    * This function closes the current render window.
    */
    void windowClose();

    /**
    * @brief Render the current frame on the window.
    *
    * This function renders the current frame on the window.
    */
    void windowRenderFrame();

    /**
    * @brief Destroy the window.
    *
    * This function destroys the window and cleans up resources.
    */
    void windowDestroy();

  private:
    Window(Window& other);
};

#endif
