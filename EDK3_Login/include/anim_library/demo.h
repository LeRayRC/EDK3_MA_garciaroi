/**
 * @file demo.h
 * @author Carlos Garcia 
 * @brief 
 * 
 */
#ifndef _DEMO_H_
#define _DEMO_H_

#include "entity.h"
#include "gtexture.h"
#include <vector>
#include "animationinstance.h"

/**
 * @brief Class that represent the ET Demo and all its components
 * 
 */
class DemoET{
  private:
    float elapsed_time_;
    Entity* letters_intro_ = nullptr;
    Entity* letters_paragraph_1_ = nullptr;
    Entity* letters_paragraph_2_ = nullptr;
    Entity* letters_paragraph_3_ = nullptr;
    Entity* letters_paragraph_4_ = nullptr;
    Entity* letters_paragraph_5_ = nullptr;
    Entity* letters_main_title_ = nullptr;

    Entity* falcon_entity_ = nullptr;
    Entity* enterprise_entity_ = nullptr;
    Entity* xenomorph_entity_ = nullptr;
    Entity* unicorn_entity_ = nullptr;
    Entity* bike_entity_ = nullptr;
    Entity* et_entity_ = nullptr;
    Entity* confuse_entity_ = nullptr;

    std::vector<Entity*> stars_background_entity_;


    AnimationConfig anim_config_paragraphs_;
    AnimationConfig bike_anim_config_;
    AnimationConfig main_title_config_;
    AnimationConfig intro_config_;
    AnimationConfig falcon_anim_config_;
    AnimationConfig enterprise_anim_config_;
    AnimationConfig xenomorph_anim_config_;
    AnimationConfig unicorn_anim_config_;
    AnimationConfig et_anim_config_;
    AnimationConfig confuse_anim_config_;
    // AnimationConfig _anim_config_;

    Texture *bike_texture_;
    Texture* letters_texture_;
    Texture* falcon_texture_;
    Texture* enterprise_texture_;
    Texture* xenomorph_texture_;
    Texture* unicorn_texture_;
    Texture* et_texture_;
    Texture* confuse_texture_;

    bool textures_loaded_;
    bool bike_has_reverted_;
    int n_stars_;
    
  public:
    /**
    * @brief Constructor for the DemoET class.
    * Initializes member variables.
    */
    DemoET(/* args */);
    ~DemoET();

    /**
    * @brief Loads textures for the demo.
    *
    * Loads various textures required for the demo and adds them to the game's texture list.
    *
    * @return True if all textures are successfully loaded, false otherwise.
    */
    bool loadDemoTextures();

    /**
    * @brief Initializes demo entities.
    *
    * This method initializes various entities for the demo, such as stars, sprites, and their configurations.
    */
    void initDemoEntities();

    /**
    * @brief Initializes animation configurations for various entities in the demo.
    *
    * This function sets up animation configurations for different entities, including movement,
    * rotation, scaling, and other parameters.
    */
    void initDemoAnimationConfigs();

    /**
    * @brief Initiates and plays animations for various entities in the demo.
    *
    * This function triggers animations for different entities based on pre-configured animation
    * configurations. Entities include letters, paragraphs, a bike, falcon, enterprise, xenomorph,
    * ET, confused entity, and a unicorn.
    *
    */
    void animateDemoEntities();

    /**
    * @brief Runs the demo by initializing entities, animation configurations, and triggering animations.
    *
    * This function serves as the main entry point for running the demo. It initializes various entities,
    * loads demo textures, creates animation configurations, and triggers animations for different entities.
    * The entities include sprites representing letters, paragraphs, a bike, falcon, enterprise, xenomorph,
    * ET, confused entity, and a unicorn. Animations include movements, rotations, and scalings, each with
    * specific configurations.
    *
    */
    void runDemo();

    /**
    * @brief Updates the demo, including the background stars and specific entity animations.
    *
    * This function is responsible for updating the demo state over time. It calculates the elapsed time
    * based on the game's delta time (`dt`). If the elapsed time exceeds a certain threshold (90.0 seconds),
    * the demo is considered complete, and relevant cleanup operations are performed. Otherwise, the function
    * updates the background stars' positions and checks if the bike entity's animation needs to be reverted
    * to its initial state.
    *
    */
    void updateDemo();

    /**
    * @brief Draws the background stars in the demo.
    *
    * This function is responsible for rendering the background stars of the demo. It iterates through the
    * collection of background star entities and calls their respective draw functions to display them on
    * the screen.
    *
    */
    void drawDemo();

    /**
    * @brief Clears and resets the entities and animations used in the demo.
    *
    * This function is responsible for stopping and clearing any active animations and entities used in the demo.
    * It iterates through the list of game entities, stops their animations, and deletes them. Additionally, it
    * stops and deletes the animations and entities related to background stars. Finally, it clears the lists of
    * game entities and background stars, ensuring a clean state for the demo.
    *
    */
    void clearDemo();
};

#endif