/**
 * @file gsprite.h
 * @author Luis Miguel Jiménez
 * @brief header file for the sprite class
 */
#ifndef _SPRITE_H_
#define _SPRITE_H_ 1

#include "platform.h"
#include "gtexture.h"
#include "math_lib/vector_2.h"
#include "color.h"
#include "entity.h"
#include "math_lib/matrix_3.h"

/**
 * @brief Class that represents a Sprite and its methods and attributes
 * 
 */
class Sprite : public Entity{
  //Attributes
  private:
  protected:
    Handle handle_;
  public:
    /**
     * @brief Constructs a Sprite from a specified region of a texture.
     *
     * This constructor creates a Sprite by extracting a sub-region from a given texture
     * based on the specified origin and size. The resulting sprite handle is assigned to
     * the `handle_` member variable.
     *
     * @param texture The texture from which to extract the sub-sprite.
     * @param origin The origin point (top-left) of the sub-sprite within the texture.
     * @param size The size (width and height) of the sub-sprite.
     */
    Sprite(Texture& texture, Vec2 origin, Vec2 size);

    /**
     * @brief Constructs a Sprite from a specified region of a texture.
     *
     * This constructor creates a Sprite by extracting a sub-region from a given texture
     * based on the specified position (x, y) and dimensions (width and height). The resulting
     * sprite handle is assigned to the `handle_` member variable.
     *
     * @param texture The texture from which to extract the sub-sprite.
     * @param x The x-coordinate of the top-left corner of the sub-sprite within the texture.
     * @param y The y-coordinate of the top-left corner of the sub-sprite within the texture.
     * @param w The width of the sub-sprite.
     * @param h The height of the sub-sprite.
     */
    Sprite(Texture& texture, int x, int y, int w, int h);

    /**
     * @brief Copy constructor for creating a Sprite from another Sprite.
     *
     * This constructor creates a new Sprite by copying the image data from another Sprite.
     * It uses the `sf::Image` representation of the other sprite and loads it into the
     * current sprite's handle, preserving the dimensions of the original image.
     *
     * @param other The source Sprite from which to copy the image data.
     */
    Sprite(const Sprite& other);

    /**
     * @brief Destructor for releasing resources associated with the Sprite.
     *
     * This destructor is responsible for releasing resources associated with the Sprite.
     * If the sprite handle is not nullptr, it calls the `release` function to release
     * any allocated resources.
     */
    virtual ~Sprite();

    /**
     * @brief Releases resources associated with the Sprite.
     *
     * This function is responsible for releasing resources associated with the Sprite.
     * If the sprite handle is not nullptr, it deletes the handle and sets it to nullptr.
     */
    void release();

    /**
     * @brief Gets the width of the Sprite.
     *
     * This function returns the width of the Sprite, which is determined by the
     * horizontal size of the underlying image or texture.
     *
     * @return The width of the Sprite.
     */
    int width() const;

    /**
     * @brief Gets the height of the Sprite.
     *
     * This function returns the height of the Sprite, which is determined by the
     * vertical size of the underlying image or texture.
     *
     * @return The height of the Sprite.
     */
    int height() const;

    // Color pixelColor(Vec2 position);

    /**
     * @brief Updates the sprite, including animation if applicable.
     *
     * This function updates the sprite, including any active animation, if the sprite is enabled.
     * If an animation instance is associated with the sprite, it is updated, and if it reaches the
     * end, the instance is deleted. This function is typically called during the game's update cycle.
     */
    void update() override;

    /**
     * @brief Draws the Sprite on the game window.
     *
     * This function draws the Sprite on the game window if it is enabled and has a valid handle.
     * It uses the transform information (position, rotation, and scale) of the Sprite to apply the
     * necessary transformations before rendering it on the window.
     */
    void draw() const override;
    
    /**
     * @brief Initializes the Sprite with a sub-sprite from a texture.
     *
     * This function initializes the Sprite by releasing any existing resources, creating
     * a new sf::Texture handle, and assigning it a sub-sprite from the specified texture
     * based on the provided coordinates and dimensions.
     *
     * @param texture The texture from which to extract the sub-sprite.
     * @param x The x-coordinate of the top-left corner of the sub-sprite within the texture.
     * @param y The y-coordinate of the top-left corner of the sub-sprite within the texture.
     * @param w The width of the sub-sprite.
     * @param h The height of the sub-sprite.
     */
    void init(Texture& texture, const int x, const int y, const int w, const int h);
};
 
#endif
 