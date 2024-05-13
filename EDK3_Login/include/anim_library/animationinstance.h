/**
 * @file animationinstance.h
 * @author Luis Miguel Jiménez
 * @brief File header for the class dedicated to animations given to entities during runtime.
 */

#ifndef _ANIMATION_INSTANCE_H_
#define _ANIMATION_INSTANCE_H_ 1

#include "entity.h"
#include "../math_library/vector_2.h"
#include "../math_library/vector_3.h"
#include "interpolate.h"

struct AnimationConfig{
  int id = 0;
  char name[16] = {"\0"};
  char temp_name[16] = { "\0" };
  // Flags
  bool is_moving = false;
  bool is_rotating = false;
  bool is_scaling = false;
  // Move
  Vec3 move_from = {0.0f,0.0f,0.0f};
  Vec3 move_to = { 0.0f,0.0f,0.0f };
  float move_duration = 0.0f;
  // Rotation --> radians
  Vec3 rotate_from = { 0.0f,0.0f,0.0f };
  Vec3 rotate_to = { 0.0f,0.0f,0.0f };
  float rotate_duration = 0.0f;
  // Scale
  Vec3 scale_from = { 1.0f,1.0f,1.0f };
  Vec3 scale_to = { 1.0f,1.0f,1.0f };
  float scale_duration = 0.0f;

  InterpolationType type_ = InterpolationType::InterpolationType_Linear;
  float total_delay=0.0f;
  float current_delay=0.0f;
};

struct AnimationStatus{
  bool ended_;
  float percent_;
  float elapsed_time_;
};

void ResetAnimationConfig(AnimationConfig& config);

void UpdateAnimationConfigsString();

enum AnimationStatusOption{
  AnimationStatusOption_Rotation,
  AnimationStatusOption_Position,
  AnimationStatusOption_Scale,
};

/**
 * @brief This class represents an AnimationInstance with its methods and attributes
 * 
 */
class AnimationInstance{
  //Attributes
  private:
    Entity* entity_;

    // Easing

    AnimationStatus position_status_;
    AnimationStatus rotation_status_;
    AnimationStatus scale_status_;
  public:
    AnimationConfig config_;
  
  //Methods
  public:
    bool revert_;
    AnimationInstance();
    // AnimationInstance(AnimationConfig config, Entity* ent);
    ~AnimationInstance();

    //Methods
    /**
     * @brief Updates the animation state based on the elapsed time.
     *
     * This function updates the animation state, including position, rotation, and scale,
     * based on the elapsed time since the animation started. It takes into account the
     * animation configuration and gradually modifies the entity's transform accordingly.
     */
    void update();
    // bool done();
    void progress();
    /**
     * @brief Initializes an AnimationInstance with the given configuration and entity.
     *
     * This function initializes an AnimationInstance with the provided AnimationConfig
     * and associates it with a given Entity. It sets up the animation parameters such as
     * position, rotation, and scale based on the provided configuration.
     *
     * @param config The AnimationConfig specifying the animation parameters.
     * @param ent A pointer to the Entity associated with the animation.
     */
    void init(AnimationConfig config, Entity *ent);
    /**
     * @brief Initializes an AnimationInstance with the given configuration.
     *
     * This function initializes an AnimationInstance with the provided AnimationConfig.
     * It sets up the animation parameters such as position, rotation, and scale based on
     * the provided configuration. This version of the function does not require an entity
     * association.
     *
     * @param config The AnimationConfig specifying the animation parameters.
     */
    void init(AnimationConfig config);
    /**
     * @brief Checks if the animation has ended for position, rotation, and scale.
     *
     * This function evaluates whether the animation has ended for position, rotation,
     * and scale based on their respective status and configuration flags. The animation
     * is considered ended when the specified conditions for each type of animation are met.
     *
     * @return True if the animation has ended for position, rotation, and scale; otherwise, false.
     */
    bool isEnded();
    // void moveTowards();
    /**
     * @brief Sets the associated entity for the AnimationInstance.
     *
     * This function sets the Entity pointer for the AnimationInstance, allowing it to
     * be associated with a specific entity in the scene.
     *
     * @param ent A pointer to the Entity to be associated with the AnimationInstance.
     */
    void set_entity(Entity *ent);

    /**
    * @brief Get the progress of a specific animation status.
    *
    * This function returns the progress (as a percentage) of a specific animation status.
    *
    * @param status The animation status code.
    *               - 0 for position status.
    *               - 1 for rotation status.
    *               - 2 for scale status.
    *               - Any other value will return 0.
    * 
    * @return The progress percentage of the specified animation status.
    */
    float get_progress(int status);

    void set_revert(bool revert);

    /**
    * @brief Set the elapsed time for a specific animation status.
    *
    * This function sets the elapsed time for a specific animation status. The elapsed time
    * is used to determine the progress of the animation for the specified status.
    *
    * @param status The animation status code.
    *               - 0 for position status.
    *               - 1 for rotation status.
    *               - 2 for scale status.
    *               - Any other value is ignored.
    * @param time The elapsed time to set for the specified animation status.
    */
    void set_elapsed_time(int status, float time);

    /**
    * @brief Set the animation status for a specific animation option.
    *
    * This function sets the animation status for a specific animation option.
    *
    * @param option The animation status option:
    *               - AnimationStatusOption_Position for position status.
    *               - AnimationStatusOption_Rotation for rotation status.
    *               - AnimationStatusOption_Scale for scale status.
    *               - Other options are ignored.
    * @param status The status to set for the specified animation option.
    */
    void set_animation_status(const AnimationStatusOption option, bool status);

    /**
    * @brief Get the duration for a specific animation status.
    *
    * This function returns the duration of a specific animation status based on the animation configuration.
    *
    * @param status The animation status code.
    *               - 0 for position status.
    *               - 1 for rotation status.
    *               - 2 for scale status.
    *               - Any other value will return 0.
    * 
    * @return The duration of the specified animation status.
    */
    float get_duration(int status);
    
}; 

#endif