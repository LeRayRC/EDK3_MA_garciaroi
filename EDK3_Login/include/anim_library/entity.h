/**
 * @file entity.h
 * @author Carlos García
 * @brief header file for entitiy class definition and every functionality related to it
 */
#ifndef _ENTITY_H_
#define _ENTITY_H_ 1

#include <stdlib.h>
#include <string>
#include "EDK3/drawable.h"
#include "material_custom.h"

class AnimationInstance;
struct AnimationConfig;

enum EntityType{
    EntityType_Path,
    EntityType_Sprite,
};

enum DrawableAttached {
    DrawableAttached_Cube,
    DrawableAttached_Quad,
    DrawableAttached_Sphere,
    DrawableAttached_Terrain,
    DrawableAttached_Donut,
    DrawableAttached_Tree,
    DrawableAttached_House,
    DrawableAttached_Boat,
    DrawableAttached_Water,
    DrawableAttached_Cube8v,
};

/**
 * @brief Class that represents an Entity and its attributes and methods
 * 
 */
class Entity{
  // Attributes
  public:
    int id_;
    bool attached_;
    bool enabled_;
    bool play_animation_;
    int drawableAttached_;
    EDK3::ref_ptr<EDK3::Drawable> drawable_;
    AnimationInstance* anim_instance_;
    static int next_entity_id;

    int animation_config_selected;

    char name_[16];
    char temp_name_[16];
    Vec3 position_;
    Vec3 rotation_;
    Vec3 scale_;
  // Methods
  public:
    // Constructors
    /**
     * @brief Default constructor for the Entity class.
     *
     * This constructor initializes an Entity object with default values. It sets the tag
     * to 0, enables the entity by default, assigns a default name ("EntityObj"), generates
     * a unique ID for the entity, sets the animation configuration selected to 0, and
     * initializes the animation instance pointer to nullptr.
     */
    Entity();
    
    /**
     * @brief Parameterized constructor for the Entity class.
     *
     * This constructor initializes an Entity object with specific values provided as parameters.
     * It allows setting the entity's tag, enabled status, and name. The entity ID is generated
     * uniquely for each entity, and the animation configuration selected is initialized to 0.
     *
     * @param tag The tag assigned to the entity.
     * @param enabled The initial enabled status of the entity.
     * @param name The name assigned to the entity.
     */
    Entity(bool enabled, char* name);
    
    /**
     * @brief Copy constructor for the Entity class.
     *
     * This constructor creates a new Entity object by copying the values from another
     * existing Entity object. It replicates the tag, enabled status, name, transform,
     * animation configuration selection, and generates a new unique ID for the copied entity.
     * The animation instance pointer is initialized to nullptr.
     *
     * @param other The Entity object to be copied.
     */
    Entity( const Entity& other);
    
    // Destructor
    virtual ~Entity();

    // Methods
    /**
     * @brief Sets the enabled status of the entity.
     *
     * This function sets the enabled status of the entity based on the provided parameter.
     * If the parameter is true, the entity is enabled; if false, the entity is disabled.
     *
     * @param enable The boolean value indicating whether to enable or disable the entity.
     * @return The updated enabled status of the entity.
     */
    bool enable(bool enable);

    /**
     * @brief Sets the name for the entity.
     *
     * This function sets the name for the entity to the specified new name.
     *
     * @param new_name The new name to be assigned to the entity.
     * @return The updated name of the entity.
     */
    std::string set_name(char* new_name);
    
    int set_play_animation(bool value);

    /**
     * @brief Plays an animation on the entity.
     *
     * This function initiates and plays the specified animation on the entity by creating
     * an instance of the AnimationInstance class. The AnimationInstance is associated with
     * the entity, initialized with the provided AnimationConfig, and assigned to the
     * `anim_instance_` member variable.
     *
     * @param anim_config The AnimationConfig specifying the parameters for the animation.
     */
    void playAnimation(const AnimationConfig& anim_config);

    /**
    * @brief Stop the current animation associated with the entity.
    *
    * This function stops the current animation associated with the entity by deleting the animation instance.
    * If no animation instance is currently assigned, this function has no effect.
    */
    void stopAnimation();

    virtual void update();

    void set_position(Vec3 pos);
    void set_rotation(Vec3 rot);
    void set_scale(Vec3 scale);

    Vec3 position() const;
    Vec3 rotation() const;
    Vec3 scale() const;

    void setupDrawable(EDK3::Geometry* geo,
        EDK3::MaterialCustom* mat,
        EDK3::MaterialSettings* mat_settings,
        Vec3 pos, Vec3 scale = Vec3( 1.0f, 1.0f, 1.0f ), Vec3 rot = Vec3(0.0f, 0.0f ,0.0f));

    void attachDrawable(DrawableAttached drawableAttached, EDK3::Node* root);
    void init();
};




#endif