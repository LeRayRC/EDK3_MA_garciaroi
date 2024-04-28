/**
 * @file transform.h
 * @author Luis Miguel Jiménez
 * @brief Header file that represents the Transform2D class
 *
 */

#ifndef _TRANSFORM2D_H_
#define _TRANSFORM2D_H_ 1

#include <stdlib.h>
#include <vector>

#include "math_lib/vector_2.h"
#include "math_lib/matrix_3.h"

/**
 * @brief This class represents a Transform2D with all its methods and attributes
 * 
 */
class Transform2D{
  public:
    Mat3 matrix_;
    Vec2 position_;
    float rotation_;
    Vec2 scale_;
    Vec2 origin_;
    

  public:
    // Constructors

    /**
    * @brief Default constructor for Transform2D.
    *
    * Initializes the transformation with default values:
    *   - Position: (0.0f, 0.0f)
    *   - Rotation: 0.0f
    *   - Scale: (1.0f, 1.0f)
    *
    * This constructor sets the initial state of the 2D transformation.
    */
    Transform2D();

    /**
    * @brief Constructor for Transform2D with specified parameters.
    *
    * Initializes the transformation with the provided values for position, rotation, and scale.
    *
    * @param position The position vector.
    * @param rotation The rotation angle in radians.
    * @param scale The scale vector.
    *
    * This constructor allows creating a 2D transformation with custom parameters.
    */
    Transform2D(Vec2 position, float rotation, Vec2 scale);
    // Destructor
    ~Transform2D();
    
    // Operators

    /**
    * @brief Assignment operator for Transform2D.
    *
    * Assigns the values of another Transform2D object to this one.
    *
    * @param other The Transform2D object to copy values from.
    *
    * This operator allows assigning the values of one Transform2D object to another.
    */
    void operator=(const Transform2D& other);

    // Setters
    void set_position(Vec2 position);
    void set_rotation(float rotation);
    void set_scale(Vec2 sacale);
    void set_origin(Vec2 origin);

    // Methods

    /**
    * @brief Calculate the transformation matrix for the Transform2D object.
    *
    * Calculates and returns the transformation matrix for the current state
    * of the Transform2D object.
    *
    * @return The transformation matrix represented by a Mat3 object.
    *
    * This function computes the transformation matrix based on the current
    * position, rotation, scale, and origin of the Transform2D object.
    * The order of transformations is translation, scaling, rotation, and then
    * translation based on the origin.
    */
    Mat3 calculateMatrix() const;

    /**
    * @brief Transform a vector of 2D points using the transformation matrix.
    *
    * Transforms a vector of 2D points using the transformation matrix
    * of the current state of the Transform2D object and stores the result
    * in the specified output vector.
    *
    * @param[in] in The vector of 2D points to be transformed.
    * @param[out] out The vector to store the transformed points.
    *
    * This function transforms each point in the input vector `in` by applying
    * the transformation matrix of the Transform2D object. The resulting
    * transformed points are stored in the output vector `out`.
    */
    void transformPoints(const std::vector<Vec2>& in, std::vector<Vec2>& out) const;

    // Debug
    void print();
};

#endif


