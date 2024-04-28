/**
 * @file gtexture.h
 * @author Carlos García
 * @brief header file that represents the Texture class and all its functionalities
 */
#ifndef _TEXTURE_H_
#define _TEXTURE_H_ 1

#include "platform.h"

#include <stdlib.h>
#include <string>

/**
 * @brief Class that represents a Texture and its methods and attributes
 * 
 */
class Texture {
  //Attributes
  public: 
    std::string path_;
    Handle handle_;
    static int num_textures;
    static int kMaxTextures;

  //Methods
  public:
    // Destructor
    ~Texture();

    /**
     * @brief Initializes the Texture with an image file.
     *
     * This function initializes the Texture with the image file specified by the provided path.
     * If the texture handle is not nullptr, it loads the image from the file into the handle
     * and updates the path associated with the texture.
     *
     * @param path The file path of the image to initialize the Texture with.
     */
    void init(const char* name);
    /**
     * @brief Initializes the Texture with raw image data.
     *
     * This function initializes the Texture with raw image data of the specified width and height.
     * If the texture handle is not nullptr, it loads the image from the provided data into the handle.
     *
     * @param width The width of the image data.
     * @param height The height of the image data.
     * @param data A pointer to the raw image data.
     */
    void init(int width, int height, unsigned char* data);

    /**
     * @brief Initializes the Texture with raw image data.
     *
     * This function initializes the Texture with raw image data of the specified width and height.
     * If the texture handle is not nullptr, it loads the image from the provided data into the handle.
     *
     * @param width The width of the image data.
     * @param height The height of the image data.
     * @param data A pointer to the raw image data.
     */
    int width() const;

    /**
     * @brief Gets the height of the Texture.
     *
     * This function returns the height of the Texture, which is determined by the vertical size
     * of the underlying image. If the texture handle is not nullptr, it retrieves the height;
     * otherwise, it returns 0.
     *
     * @return The height of the Texture or 0 if the texture handle is nullptr.
     */
    int height() const;

    /**
     * @brief Creates a sub-sprite from the Texture.
     *
     * This function creates a sub-sprite from the Texture based on the specified coordinates
     * and dimensions. It returns a handle to the newly created sub-sprite as a separate Texture.
     * If the texture handle is not nullptr, it extracts the sub-sprite; otherwise, it returns nullptr.
     *
     * @param x The x-coordinate of the top-left corner of the sub-sprite within the Texture.
     * @param y The y-coordinate of the top-left corner of the sub-sprite within the Texture.
     * @param w The width of the sub-sprite.
     * @param h The height of the sub-sprite.
     * @return A handle to the newly created sub-sprite or nullptr if the texture handle is nullptr.
     */
    Handle getSubSprite(int x, int y, int w, int h);

    /**
     * @brief Releases the allocated resources of the Texture.
     *
     * This function releases the allocated resources of the Texture by deleting the handle.
     * If the texture handle is not nullptr, it deletes the handle and sets it to nullptr.
     */
    void release();

    /**
     * @brief Creates a new Texture instance.
     *
     * This function creates a new Texture instance if the maximum allowable number
     * of textures has not been reached. The function increments the total number of
     * textures and returns a pointer to the created Texture, or nullptr if the limit
     * has been reached.
     *
     * @return A pointer to the created Texture instance, or nullptr if the limit is reached.
     */
    static Texture* CreateTexture();

    /**
     * @brief Creates a new Texture instance and initializes it with a specified image file.
     *
     * This function creates a new Texture instance if the maximum allowable number
     * of textures has not been reached. It initializes the created Texture instance with
     * the image file specified by the provided name. The function increments the total
     * number of textures and returns a pointer to the created Texture, or nullptr if the
     * limit has been reached.
     *
     * @param name The name of the image file to initialize the Texture with.
     * @return A pointer to the created Texture instance, or nullptr if the limit is reached.
     */
    static Texture* CreateTexture(const char* name);

    /**
     * @brief Releases the allocated resources associated with a Texture handle.
     *
     * This function releases the allocated resources associated with a Texture handle by
     * using the appropriate library function to release the handle. If the handle is not nullptr,
     * it invokes the corresponding release function, such as `esat::SpriteRelease`.
     *
     * @param handle The handle to a Texture or sprite to release.
     */
    static void ReleaseHandle(Handle handle);
  private:
    Texture(const Texture& other);
    Texture();

};

#endif


