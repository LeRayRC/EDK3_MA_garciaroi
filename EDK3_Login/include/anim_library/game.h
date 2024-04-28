/**
 * @file game.h
 * @author Luis Miguel Jiménez
 * @brief header file for the game singleton that manages the game
 */

#ifndef _GAME_H_
#define _GAME_H_ 1

#include <stdlib.h>
#include <vector>

#include "platform.h"
#include "entity.h" 
#include "gwindow.h"
#include "interface.h"
#include "gtexture.h"
#include "database.h"
#include "animationinstance.h"
#include "demo.h"

/**
 * @brief Class the represents the singleton that manages the game
 * 
 */
class Game{
  //Attributes
  private:
    static Game* instance;
  public:
    std::vector<Entity*> entities_;
    std::vector<AnimationConfig> animation_configs_;
    std::vector<AnimationConfig> animation_configs_db_;
    std::vector<Texture*> textures_;
    Window window;
    float dt;

    //FPS
    float refresh_fps_cooldown;
    float fps_timer;
    float framerate;
    double current_time;
    double last_time;

    //Interface windows
    ImGuiWindow settings_window;
    ImGuiWindow entities_window;
    ImGuiWindow animationconfigs_window;
    ImGuiWindow newpath_window;
    ImGuiWindow newtexture_window;
    ImGuiWindow newanimationconfig_window;
    ImGuiWindow newsprite_window;


    //Path settings
    static const int kMaxPathVertexes = 20;
    static const int kMinPathVertexes = 3;
    static const int kMaxAnimationDuration = 120;

    //DB
    Database db_;

    //Sprites
    int temp_handle_index;
    Handle temp_handle;
    Handle temp_handle_2;

    //Demo
    DemoET demo_et_;
    bool demo_running_;

  //Methods
  private:
    // Constructor
    Game();
    // Copy constructor
    Game(const Game& other);


  public:
    /**
     * @brief Retrieves the singleton instance of the Game class.
     *
     * This function provides access to the singleton instance of the Game class.
     * If the instance does not exist, it creates a new instance and returns it.
     *
     * @return A pointer to the singleton instance of the Game class.
     */
    static Game* getInstance();

    /**
     * @brief Initializes the Game instance.
     *
     * This function initializes the Game instance by setting various initial values and flags.
     * It sets up default window flags for different windows in the game, connects to the
     * internal database, and runs a query to retrieve animation data. Additionally, it seeds
     * the random number generator with the current time.
     */
    void init();

    /**
     * @brief Main game loop handling updates, drawing, and user input.
     *
     * This function represents the main game loop, responsible for handling updates,
     * drawing, and user input. It utilizes the SFML library for window management and
     * ImGui for graphical user interface elements. The loop continues until the game window
     * is closed. During each iteration, it updates the delta time, processes events, updates
     * the game state, draws game entities, handles ImGui elements, and renders the frame.
     */
    void mainCicle();

    /**
     * @brief Updates the game state.
     *
     * This function updates the game state by calling the `update` function for each
     * entity in the game. It iterates through the list of entities and triggers their
     * update routines, allowing them to perform any necessary logic or transformations.
     */
    void update();

    /**
     * @brief Draws the game entities.
     *
     * This function draws the game entities by calling the `draw` function for each
     * entity in the game. It iterates through the list of entities and triggers their
     * draw routines, allowing them to render their visual representation.
     */
    void draw();

    /**
     * @brief Performs cleanup operations at the end of the game.
     *
     * This function is responsible for performing cleanup operations at the end of the game,
     * specifically shutting down ImGui to release any allocated resources.
     */
    void end();
};

#endif