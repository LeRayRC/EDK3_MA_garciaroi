/**
 * @file path.h
 * @author Carlos García
 * @brief Header file that represents the path class
 */
#ifndef _PATH_H_
#define _PATH_H_ 1

#include "platform.h"

#include <stdlib.h>
#include <vector>

#include "entity.h"
#include "color.h"

/**
 * @brief Class that represents a Path polygon with all its methods and attributes
 * 
 */
class Path : public Entity{
  //Attributes
  public:
    Color border_color_;
    Color fill_color_;
    bool solid_;
    // float* vertex_;
  public:
    std::vector<Vec2> vertexes_;
    std::vector<Vec2> vertexes_transformed_;

  //Methods
  public:

    /**
    * @brief Default constructor for the Path class.
    *
    * This constructor initializes a Path object with default values.
    * It sets the type of the entity to EntityType_Path and assigns a default
    * border color of white (255, 255, 255).
    */
    Path();

    /**
    * @brief Constructor for the Path class with parameters.
    *
    * This constructor initializes a Path object with specified parameters.
    *
    * @param border The border color of the path.
    * @param fill The fill color of the path.
    * @param solid A boolean indicating whether the path is solid or not.
    * @param vertexes An array of Vec2 representing the vertex positions of the path.
    * @param n_vertexes The number of vertices in the path.
    */
    Path(const Color border, const Color fill, const bool solid, const Vec2* vertexes, const int n_vertexes);

    // Destructor 
    virtual ~Path();

    // Setters
    void set_border_color(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a=255);
    void set_fill_color(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a=255);
    void set_solid(const bool solid);
    void set_vertex(const Vec2& vertexes, const int position);

    // Methods
    void draw() const override;

    /**
    * @brief Update the path's state.
    *
    * This function updates the path's state, including any ongoing animation.
    * If animations are enabled and a valid animation instance is attached, it is updated.
    * After updating the state, the transformed vertex positions are updated based on the path's current transformation.
    *
    * @note This function should be called periodically to keep the path's state up-to-date.
    */
    void update() override;
    int getSize() const;

    /**
    * @brief Add a vertex to the path.
    *
    * This function adds a new vertex to the path, extending its shape.
    *
    * @param new_vertex The new vertex to be added to the path.
    */
    void addVertex(const Vec2 new_vertex);

    void print();

    /**
    * @brief Initialize a regular polygon path.
    *
    * This function initializes the path as a regular polygon with the specified number of vertices.
    * The vertices are evenly distributed on the circumference of a circle.
    *
    * @param vertexes The number of vertices for the regular polygon.
    */
    void InitRegularPolygon(const int vertexes);
};

#endif